// OpenCL header file
#include <CL/cl.h>

// Additional standard headers
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	// Error code for API calls
	cl_int err;
	// ID of the selected platform (OpenCL implementation)
	cl_platform_id platform;
	// ID of the selected device (OpenCL implementation)
	cl_device_id device;
	// Context properties
	cl_context_properties cxprops[3];
	// Context object
	cl_context context;
	// Command-queue object
	cl_command_queue queue;
	// Program object
	cl_program program;
	// Kernel object
	cl_kernel kernel;
	// Memory object to store string on device.
	cl_mem d_str;
	// Our string in host memory
	char h_str[100] = "Hello world!";
	// Our string length
	cl_uint str_len = strlen(h_str);
	// C-string holding the OpenCL C source code
	const char *srccode =  
		"__kernel                                                       "
		"void upper_case(__global unsigned char *str,                   "
		"                unsigned int strlen)                           "
		"{                                                              "
		"  int i = 0;                                                   "
		"  for (; i < strlen; ++i)                                      "
		"    str[i] = (str[i] >= 'a' && str[i] <= 'z') ? /* in range? */"
		"             (str[i] - 'a' + 'A') :     /* if so, raise case */"
		"             (str[i]);            /* otherwise, don’t change */"
		"}                                                              ";


	// Query for the first available platform.
	err = clGetPlatformIDs(1, &platform, 0);
	if (err != CL_SUCCESS)
	{
		printf("Error: No OpenCL platform found on this system.\n");
		return -1;
	}

	// Query for the first available device.
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, 0);
	if (err != CL_SUCCESS)
	{
		printf("Error: device found on this platform.\n");
		return -1;
	}

	// Set context properties
	cxprops[0] = CL_CONTEXT_PLATFORM;
	cxprops[1] = (cl_context_properties)platform;
	cxprops[2] = 0;
	// Create the context.
	context = clCreateContext(cxprops, 1, &device, 0, 0, &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a context.\n");
		return -1;
	}

	// Create a command-queue
	queue = clCreateCommandQueueWithProperties(context, device, 0, &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a command-queue.\n");
		clReleaseContext(context);
		return -1;
	}

	// Create a program object with source code
	program = clCreateProgramWithSource(context, 1, &srccode, 0, &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a program object.\n");
		clReleaseCommandQueue(queue);
		clReleaseContext(context);
		return -1;
	}
	
	// Build the program for our device in one-step
	err = clBuildProgram(program, 1, &device, "", 0, 0);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to build the program.\n");
		clReleaseProgram(program);
		clReleaseCommandQueue(queue);
		clReleaseContext(context);
		return -1;
	}

	// Create a kernel from our program
	kernel = clCreateKernel(program, "upper_case", &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a kernel object.\n");
		clReleaseProgram(program);
		clReleaseCommandQueue(queue);
		clReleaseContext(context);
		return -1;
	}

	// Create a buffer for the string
	d_str = clCreateBuffer(context, CL_MEM_READ_WRITE, strlen(h_str), 0, &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a buffer for output.\n");
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		clReleaseCommandQueue(queue);
		clReleaseContext(context);
		return -1;
	}

	// Add a command for writing the string to the device
	err = clEnqueueWriteBuffer(queue, d_str, CL_TRUE, 0, strlen(h_str), &h_str, 0, 0, 0);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to read back the result.\n");
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		clReleaseCommandQueue(queue);
		clReleaseContext(context);
		return -1;
	}

	// Set kernel arguments
	err |= clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_str);
	err = clSetKernelArg(kernel, 1, sizeof(cl_uint), &str_len);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to set kernel parameters.\n");
		clReleaseMemObject(d_str);
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		clReleaseCommandQueue(queue);
		clReleaseContext(context);
		return -1;
	}

	// Add a command to execute our kernel to the command-queue
	size_t gws[1] = { 1 };
	size_t lws[1] = { 1 };
	err = clEnqueueNDRangeKernel(queue, kernel, 1, 0, gws, lws, 0, 0, 0);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to enqueue kernel for execution.\n");
		clReleaseMemObject(d_str);
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		clReleaseCommandQueue(queue);
		clReleaseContext(context);
		return -1;
	}

	// Add a command to read back the result from the device
	err = clEnqueueReadBuffer(queue, d_str, CL_TRUE, 0, strlen(h_str), &h_str, 0, 0, 0);
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to read back output from the device.\n");
		clReleaseMemObject(d_str);
		clReleaseKernel(kernel);
		clReleaseProgram(program);
		clReleaseCommandQueue(queue);
		clReleaseContext(context);
		return -1;
	}

	// Output result to the screen
	printf("%s\n", h_str);

	// Release resources
	clReleaseMemObject(d_str);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	return 0;
}

