#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

#define N 10
int main()
{
    cl_int status; // OpenCL function status
    cl_device_id device_id; // device ID
    cl_context context; // context
    cl_command_queue cmd_queue; // command queue
    cl_program program; // program
    cl_kernel kernel_odd_sort, kernel_even_sort; // kernels
    
    // Input array
    int input_array[N] = {5, 10, 1, 3, 9, 7, 4, 6, 11, 8};
    
    // OpenCL platform and device initialization
    cl_uint num_platforms;
    status = clGetPlatformIDs(0, NULL, &num_platforms);
    cl_platform_id *platforms = (cl_platform_id*)malloc(num_platforms * sizeof(cl_platform_id));
    status = clGetPlatformIDs(num_platforms, platforms, NULL);
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &status);
    
    // Create a command queue
    cmd_queue = clCreateCommandQueue(context, device_id, 0, &status);
    
    // Create memory buffers on the device for the input and output data
    cl_mem input_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, N * sizeof(int), NULL, &status);
    
    // Write data from host memory to the input buffer
    status = clEnqueueWriteBuffer(cmd_queue, input_buffer, CL_TRUE, 0, N * sizeof(int), input_array, 0, NULL, NULL);
    
    // Read the kernel source code from a file
    FILE *fp;
    const char fileName[] = "q3.cl";
    char *source_str;
    size_t source_size;
    fp = fopen(fileName, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char *)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
    
    // Create program from source code
    program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &status);
    
    // Build program
    status = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    
    // Create kernels
    kernel_odd_sort = clCreateKernel(program, "odd_sort", &status);
    kernel_even_sort = clCreateKernel(program, "even_sort", &status);
    
    // Set arguments of kernels
    status = clSetKernelArg(kernel_odd_sort, 0, sizeof(cl_mem), (void *)&input_buffer);
    status = clSetKernelArg(kernel_even_sort, 0, sizeof(cl_mem), (void *)&input_buffer);
    
    // Execute & wait for kernels to finish
    size_t global_size = N;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0)
            status = clEnqueueNDRangeKernel(cmd_queue, kernel_odd_sort, 1, NULL, &global_size, NULL, 0, NULL, NULL);
        else
            status = clEnqueueNDRangeKernel(cmd_queue, kernel_even_sort, 1, NULL, &global_size, NULL, 0, NULL, NULL);
        
        // Wait for kernel to finish
        status = clFinish(cmd_queue);
    }
    
    // Read output data from device to host
    int output_array[N];
    status = clEnqueueReadBuffer(cmd_queue, input_buffer, CL_TRUE, 0, N * sizeof(int), output_array, 0, NULL, NULL);
    
    // Print sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", output_array[i]);
    }
    printf("\n");
    
    // Clean up resources
    status = clReleaseKernel(kernel_odd_sort);
    status = clReleaseKernel(kernel_even_sort);
    status = clReleaseProgram(program);
    status = clReleaseMemObject(input_buffer);
    status = clReleaseCommandQueue(cmd_queue);
    status = clReleaseContext(context);
    
    return 0;
}
