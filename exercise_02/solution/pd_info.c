// OpenCL header file
#include <CL/cl.h>

// Additional standard headers
#include <stdio.h>

// Maximum length for string information
#define MAX_STRING_SIZE 100

int main(int argc, char **argv)
{
	// Error code for API calls
	cl_int err;
	// IDs of available platforms
	cl_platform_id *platforms;
	// Actual number of available platforms
	cl_uint num_platforms;
	// IDs of available devices
	cl_device_id *devices;
	// Actual number of available devices
	cl_uint num_devices;
	// Buffer for any string information
	char str_buf[MAX_STRING_SIZE];
	// Device type
	cl_device_type dev_type;
	// Device compute units count
	cl_uint dev_cu;
	// Loop iterator
	cl_uint i, j;

	// Acquire all available platform IDs
	err = clGetPlatformIDs(0, NULL, &num_platforms);
	platforms = (cl_platform_id *)malloc(num_platforms * sizeof(cl_platform_id));
	err = clGetPlatformIDs(num_platforms, platforms, NULL);

	// Output the number of platforms found
	printf("Number of available platforms: %d\n", num_platforms);

	// Iterate through the platforms
	for (i = 0; i < num_platforms; ++i)
	{
		// Query for device ID associated with this platform
		err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
		if (num_devices > 0)
		{
			// Output the platform number
			printf("\nPlatform %d:\n", i);

			// Query for the platform's vendor name
			err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, MAX_STRING_SIZE, str_buf, 0);
			// Output vendor name
			printf("\tVendor:  %s\n", str_buf);
			// Query for the platform's name
			err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, MAX_STRING_SIZE, str_buf, 0);
			// Output platform name
			printf("\tName:    %s\n", str_buf);
			// Query for the platform's vendor name
			err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, MAX_STRING_SIZE, str_buf, 0);
			// Output Vendor name
			printf("\tVersion: %s\n", str_buf);

			devices = (cl_device_id *)malloc(num_devices * sizeof(cl_device_id));
			err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);
			// Output the number of devices found
			printf("\tNumber of available devices: %d\n", num_devices);

			// Iterate through the devices
			for (j = 0; j < num_devices; ++j)
			{
				// Output the device number
				printf("\n\tDevice %d:\n", j);

				// Query for the device name
				clGetDeviceInfo(devices[j], CL_DEVICE_NAME, MAX_STRING_SIZE, str_buf, 0);
				// Output the device name
				printf("\t\tName:          %s\n", str_buf);

				// Query number of compute units
				clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &dev_cu, 0);

				// Output number of compute units
				printf("\t\tCompute units: %d\n", dev_cu);
			}
			free(devices);
		}
	}

	// Cleanup
	free(platforms);

	return 0;
}
