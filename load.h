#ifndef __LOAD__
#define __LOAD__

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to remove comments from a file
void removeComments(FILE *file)
{
	char c;

	// Continue reading characters as long as the first non-whitespace
	// character is '#' (indicating a comment)
	while ((c = fgetc(file)) == '#') {
		// Continue reading characters until the end of the line (ignore the
		// comment)
		while ((c = fgetc(file)) != '\n') {
			// Consume characters until the end of the line (ignoring the
			// comment)
		}
	}

	// Move the cursor back by one position to read the first character after
	// the comment
	fseek(file, -1, SEEK_CUR);
}

// Function to load an image from a file
int load_command(char *input, ImageInfo *img)
{
	char filename[LENGTH];
	strcpy(filename, strtok(input, "\n"));

	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Failed to load %s\n", filename);
		freeImageMemory(img); // Free the allocated memory before returning
		return 0;
	}

	// If there's already an image loaded, free its memory
	if (img->image != NULL)
		freeImageMemory(img);

	// Remove comments from the beginning of the file
	removeComments(file);

	// Read the magic number to determine the type of image
	fscanf(file, "%s", img->magic);

	// Determine the type of image based on the magic number
	if (strcmp(img->magic, "P2") == 0) {
		img->type = 2; // Grayscale text images
	} else if (strcmp(img->magic, "P3") == 0) {
		img->type = 3; // Color text images
	} else if (strcmp(img->magic, "P5") == 0) {
		img->type = 5; // Grayscale binary images
	} else if (strcmp(img->magic, "P6") == 0) {
		img->type = 6; // Color binary images
	} else {
		printf("Invalid image format\n");
		fclose(file);
		freeImageMemory(img);
		return 0;
	}

	// Remove comments from the file
	removeComments(file);

	// Read the width and height of the image
	fscanf(file, "%d %d\n", &(img->width), &(img->height));

	// Remove comments from the file
	removeComments(file);

	// If the image is not black & white, read its maximum intensity of color
	if (img->type != 1 && img->type != 4)
		fscanf(file, "%hhu\n", &img->max);

	// Remove comments from the file
	removeComments(file);

	// Allocate memory for the image
	allocateImageMemory(img);
	if (img->image == NULL) {
		fprintf(stderr, "malloc() failed\n");
		fclose(file);
		return -1; // Allocation error
	}

	// Read pixel values based on the image type
	if (img->type <= 3) {
		for (int i = 0; i < img->height; ++i) {
			for (int j = 0; j < img->width; ++j) {
				if (img->type != 3) {
					unsigned char value;
					fscanf(file, "%hhu", &value);
					img->image[i][j].r = value;
					img->image[i][j].b = value;
					img->image[i][j].g = value;
				} else {
					unsigned char red, green, blue;
					fscanf(file, "%hhu", &red);
					fscanf(file, "%hhu", &green);
					fscanf(file, "%hhu", &blue);
					img->image[i][j].r = red;
					img->image[i][j].b = blue;
					img->image[i][j].g = green;
				}
			}
		}
	} else {
		for (int i = 0; i < img->height; ++i) {
			for (int j = 0; j < img->width; ++j) {
				if (img->type != 6) {
					unsigned char value;
					fread(&value, sizeof(unsigned char), 1, file);
					img->image[i][j].r = value;
					img->image[i][j].b = value;
					img->image[i][j].g = value;
				} else {
					unsigned char red, green, blue;
					fread(&red, sizeof(unsigned char), 1, file);
					fread(&green, sizeof(unsigned char), 1, file);
					fread(&blue, sizeof(unsigned char), 1, file);
					img->image[i][j].r = red;
					img->image[i][j].b = blue;
					img->image[i][j].g = green;
				}
			}
		}
	}

	fclose(file);

	printf("Loaded %s\n", filename);

	return 1; // Success
}

#endif
