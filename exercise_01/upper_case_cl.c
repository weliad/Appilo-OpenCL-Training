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
	// TODO: Add code to query for the first platform
	if (err != CL_SUCCESS)
	{
		printf("Error: No OpenCL platform found on this system.\n");
		return -1;
	}

	// Query for the first available device.
	// TODO: Add code to query for the first device
	if (err != CL_SUCCESS)
	{
		printf("Error: device found on this platform.\n");
		return -1;
	}

	// Set context properties
	// TODO: Add context properties initialization code
	// Create the context.
	// TODO: Add code to create an execution context
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a context.\n");
		return -1;
	}

	// Create a command-queue
	// TODO: Add code to create a command queue with default properties
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a command-queue.\n");
		return -1;
	}

	// Create a program object with source code
	// TODO: add code to create a program object
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a program object.\n");
		return -1;
	}
	
	// Build the program for our device in one-step
	// TODO: add code to build our program
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to build the program.\n");
		return -1;
	}

	// Create a kernel from our program
	// TODO: Add code to create a kernel object
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a kernel object.\n");
		return -1;
	}

	// Create a buffer for the string
	// TODO: Add code to create a buffer object for the string
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to create a buffer for output.\n");
		return -1;
	}

	// Add a command for writing the string to the device
	// TODO: Add code to write input string to device
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to read back the result.\n");
		return -1;
	}

	// Set kernel arguments
	// TODO: Add code to set kernel arguments
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to set kernel parameters.\n");
		return -1;
	}

	// Queue kernel for execution
	// TODO: Add code to queue the kernel for execution
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to enqueue kernel for execution.\n");
		return -1;
	}

	// Add a command to read back the result from the device
	// TODO: Add code to read back the result
	if (err != CL_SUCCESS)
	{
		printf("Error: Unable to read back output from the device.\n");
		return -1;
	}

	// Output result to the screen
	printf("%s\n", h_str);

	// Release resources
	// TODO: Add cleanup code
	return 0;
}

