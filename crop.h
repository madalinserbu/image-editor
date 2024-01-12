#ifndef __CROP__
#define __CROP__

#include "utils.h"
#include <stdio.h>
#include <string.h>

// Function to crop the image to the current selection frame
int crop_command(ImageInfo *image)
{
	// Check if an image is loaded
	if (image->image == NULL) {
		printf("No image loaded\n");
		return 0;
	}

	// Calculate the dimensions of the new sub-image
	int newWidth = image->x2 - image->x1;
	int newHeight = image->y2 - image->y1;

	// Allocate space for the new sub-image
	rgb **newImage = (rgb **)malloc(newHeight * sizeof(rgb *));
	for (int i = 0; i < newHeight; i++) {
		newImage[i] = (rgb *)malloc(newWidth * sizeof(rgb));
	}

	// Transfer pixels from the old image to the new sub-image
	for (int i = 0; i < newHeight; i++) {
		for (int j = 0; j < newWidth; j++) {
			newImage[i][j] = image->image[i + image->y1][j + image->x1];
		}
	}

	// Deallocate space for the old image
	for (int i = 0; i < image->height; i++) {
		free(image->image[i]);
	}
	free(image->image);

	// Set values for the new image
	image->width = newWidth;
	image->height = newHeight;
	image->image = newImage;

	image->x1 = 0;
	image->y1 = 0;
	image->x2 = newWidth;
	image->y2 = newHeight;

	// Display success message
	printf("Image cropped\n");
	return 1;
}

#endif
