#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<string.h>
#define MAX_SOURCE_SIZE (0x100000)

int main() {
    // Create the input string
    const char* inputString = "Hello World in openncl programmm ";
    int numWords = 5;

    // Create the OpenCL context
    cl_context context;
    cl_device_id device_id;
    cl_command_queue command_queue;
    cl_mem inputMemObj, outputMemObj, wordLengthsMemObj;
    cl_program program;
    cl_kernel kernel;
    cl_platform_id platform_id;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;

    // Get the platform and device information
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

    // Create an OpenCL context
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory objects for input, output, and word lengths
    inputMemObj = clCreateBuffer(context, CL_MEM_READ_ONLY, strlen(inputString) * sizeof(char), NULL, &ret);
    outputMemObj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, strlen(inputString) * sizeof(char), NULL, &ret);
    wordLengthsMemObj = clCreateBuffer(context, CL_MEM_READ_ONLY, numWords * sizeof(int), NULL, &ret);

    // Store the input string and word lengths in memory
    ret = clEnqueueWriteBuffer(command_queue, inputMemObj, CL_TRUE, 0, strlen(inputString) * sizeof(char), inputString, 0, NULL, NULL);
    int wordLengths[] = { 5, 5, 2, 7, 9 };
    ret = clEnqueueWriteBuffer(command_queue, wordLengthsMemObj, CL_TRUE, 0, numWords * sizeof(int), wordLengths, 0, NULL, NULL);

    // Read the kernel source code from a file
    FILE* kernelFile = fopen("q4.cl", "r");
    if (!kernelFile) {
        printf("Failed to open kernel file.\n");
        return -1;
    }
    char* kernelSource = (char*)malloc(MAX_SOURCE_SIZE);
    size_t kernelSize = fread(kernelSource, 1, MAX_SOURCE_SIZE, kernelFile);
    fclose(kernelFile);

    // Create a program from the kernel source code
    program = clCreateProgramWithSource(context, 1, (const char**)&kernelSource, (const size_t*)&kernelSize, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);



    // Create a kernel from the program
    kernel = clCreateKernel(program, "reverse_words", &ret);

    // Set the kernel arguments
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&inputMemObj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&outputMemObj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&wordLengthsMemObj);
    ret = clSetKernelArg(kernel, 3, sizeof(int), (void*)&numWords);

    // Execute the kernel
    size_t global_item_size = numWords;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, NULL, 0, NULL, NULL);

    // Read the result from the output memory object
    char* outputString = (char*)malloc(strlen(inputString) * sizeof(char));
    ret = clEnqueueReadBuffer(command_queue, outputMemObj, CL_TRUE, 0, strlen(inputString) * sizeof(char), outputString, 0, NULL, NULL);

    // Print the reversed string
    printf("Reversed string: %s", outputString);

    // Clean up resources
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(inputMemObj);
    ret = clReleaseMemObject(outputMemObj);
    ret = clReleaseMemObject(wordLengthsMemObj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(kernelSource);
    free(outputString);

    return 0;
}
