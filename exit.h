#ifndef __EXIT__
#define __EXIT__

#include "utils.h"
#include <stdio.h>
#include <string.h>

// Function to handle the EXIT command
// Frees the memory allocated for the loaded image and exits the program
int exit_command(ImageInfo *image)
{
	// Check if there is no image loaded
	if (image->image == NULL) {
		printf("No image loaded\n");
		return 0; // No image to exit from
	}

	// Free the allocated memory for the image
	freeImageMemory(image);

	return 1; // Successful exit
}

#endif
