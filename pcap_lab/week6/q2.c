
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

int main() {
    // Create input array
    const int N = 10;
    int *arr = (int*)malloc(N * sizeof(int));
    printf("Input array: ");
    for(int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;
    fp = fopen("q2.cl", "r");
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
    
    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
    
    // Create an OpenCL context
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    
    // Create memory buffers on the device for the input and output array
    cl_mem arr_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, N * sizeof(int), NULL, &ret);
    
    // Copy the input array to the device memory
    ret = clEnqueueWriteBuffer(command_queue, arr_mem_obj, CL_TRUE, 0, N * sizeof(int), arr, 0, NULL, NULL);
    
    // Create a program from the kernel source code
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);
    
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "parallelSelectionSort", &ret);
    
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&arr_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(int), &N);
    
    // Execute the OpenCL kernel on the array
    size_t global_item_size = N;
    size_t local_item_size = 1;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
    
    // Read the memory buffer on the device to the output array
    ret = clEnqueueReadBuffer(command_queue, arr_mem_obj, CL_TRUE, 0, N * sizeof(int), arr, 0, NULL, NULL);
    
    // Print the sorted array
    printf("Sorted array: ");
    for(int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(arr_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(arr);
    free(source_str);
    
    return 0;
}
