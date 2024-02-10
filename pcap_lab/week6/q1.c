#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<string.h>

#define MAX_SOURCE_SIZE (0x100000)

int main() {
    char inputStr[] = "Hello";
    int len=strlen(inputStr);
    int n = 5;
    
    // Load the kernel source code into a string
    FILE *kernelFile = fopen("q1.cl", "r");
    if (!kernelFile) {
        printf("Failed to load kernel.\n");
        exit(1);
    }
    char *sourceCode = (char *)malloc(MAX_SOURCE_SIZE);
    size_t sourceLength = fread(sourceCode, 1, MAX_SOURCE_SIZE, kernelFile);
    fclose(kernelFile);
    
    // Get platform and device information
    cl_platform_id platformID = NULL;
    cl_device_id deviceID = NULL;
    cl_uint numPlatforms, numDevices;
    cl_int ret = clGetPlatformIDs(1, &platformID, &numPlatforms);
    ret = clGetDeviceIDs(platformID, CL_DEVICE_TYPE_GPU, 1, &deviceID, &numDevices);
    
    // Create an OpenCL context
    cl_context context = clCreateContext(NULL, 1, &deviceID, NULL, NULL, &ret);
    
    // Create a command queue
    cl_command_queue commandQueue = clCreateCommandQueue(context, deviceID, 0, &ret);
    
    // Create memory buffers on the device
    cl_mem inputStrBuf = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(char) * strlen(inputStr), NULL, &ret);
    cl_mem outputStrBuf = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(char) * strlen(inputStr) * n, NULL, &ret);
    
    // Copy input data to the memory buffers
    ret = clEnqueueWriteBuffer(commandQueue, inputStrBuf, CL_TRUE, 0, sizeof(char) * strlen(inputStr), inputStr, 0, NULL, NULL);

    // Create a program from the kernel source code
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&sourceCode, (const size_t *)&sourceLength, &ret);
    
    // Build the program
    ret = clBuildProgram(program, 1, &deviceID, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "str_repeat", &ret);
    
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&inputStrBuf);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&outputStrBuf);
    ret = clSetKernelArg(kernel, 2, sizeof(int), (void *)&len);
    
    // Define work items and work group sizes
    size_t globalSize = strlen(inputStr);
    
    // Execute the OpenCL kernel
    cl_event event;
    ret = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, &event);
    
    // Read the output data from the device
    char *outputStr = (char *)malloc(sizeof(char) * strlen(inputStr) * n);
    ret = clEnqueueReadBuffer(commandQueue, outputStrBuf, CL_TRUE, 0, sizeof(char) * strlen(inputStr) * n, outputStr, 0, NULL, NULL);
    
    // Calculate the execution time
    cl_ulong startTime, endTime;
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &startTime, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &endTime, NULL);
    double executionTime = (endTime - startTime) * 1.0e-6; // in milliseconds
    
    // Print the output string and execution time
    printf("Output String: %s", outputStr);
    printf("Execution Time: %.2f ms", executionTime);
    
    // Clean up
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(inputStrBuf);
    ret = clReleaseMemObject(outputStrBuf);
    ret = clReleaseCommandQueue(commandQueue);
    ret = clReleaseContext(context);
    
    free(outputStr);
    free(sourceCode);
    
    return 0;
}
