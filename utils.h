#ifndef __UTILS__
#define __UTILS__

// Define a constant for the maximum length
#define LENGTH 1000

#include <stdlib.h>

// Structure to represent RGB color values
typedef struct {
	int r;
	int g;
	int b;
} rgb;

// Structure to store information about an image
typedef struct {
	int width, height; // Width and height of the image
	int x1, y1; // Coordinates of the top-left corner of the selected region
	int x2, y2; // Coordinates of the bottom-right corner of the selected region
	char magic[3];	   // Magic identifier for the image format
	int type;		   // Type of the image
	unsigned char max; // Maximum intensity value for color channels
	rgb **image;	   // 2D array to store RGB pixel values
} ImageInfo;

// Function to allocate memory for the image
int allocateImageMemory(ImageInfo *image)
{
	// Allocate memory for the rows of the image
	image->image = (rgb **)malloc(image->height * sizeof(rgb *));
	if (image->image == NULL)
		return 0;

	// Allocate memory for each column in every row
	for (int i = 0; i < image->height; ++i) {
		image->image[i] = (rgb *)malloc(image->width * sizeof(rgb));
		if (image->image[i] == NULL) {
			// Free previously allocated memory if an allocation fails
			for (int j = 0; j < i; ++j) {
				free(image->image[j]);
			}
			free(image->image);
			return 0;
		}
	}

	return 1; // Memory allocation successful
}

// Function to free the allocated memory for the image
void freeImageMemory(ImageInfo *image)
{
	if (image->image != NULL) {
		// Free memory for each row
		for (int i = 0; i < image->height; ++i)
			free(image->image[i]);

		// Free memory for the array of rows
		free(image->image);
		image->image = NULL; // Set the pointer to NULL after freeing
	}
}

#endif
