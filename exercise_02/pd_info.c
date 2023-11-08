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
	// TODO: Add code to query for platform IDs

	// Output the number of platforms found
	printf("Number of available platforms: %d\n", num_platforms);

	// Iterate through the platforms
	for (i = 0; i < num_platforms; ++i)
	{
		// Query for device ID associated with this platform
		// TODO: Add code to query for number of devices exposed by current platform
		if (num_devices > 0)
		{
			// Output the platform number
			printf("\nPlatform %d:\n", i);

			// TODO: Add code to query the platform's vendor name, name, and version
			//       and output the results. Use str_buf as a buffer for the information.

			// TODO: Add code to query the actual device IDs

			// Output the number of devices found
			printf("\tNumber of available devices: %d\n", num_devices);

			// Iterate through the devices
			for (j = 0; j < num_devices; ++j)
			{
				// Output the device number
				printf("\n\tDevice %d:\n", j);

				// TODO: Add code to query the device's name and maximal number of compute units.
				//       Output the results. Use str_buf and dev_cu to obtain the information.
			}
			break;
		}
	}

	// Cleanup
	free(devices);
	free(platforms);

	return 0;
}
