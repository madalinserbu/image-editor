#ifndef __SAVE__
#define __SAVE__

#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to save the image in ASCII format
void save_ascii(ImageInfo *image, char filename[])
{
	FILE *ascii = fopen(filename, "w"); // Open the file for writing text
	fprintf(ascii, "%d %d\n", image->width, image->height);
	fprintf(ascii, "%d\n", 255);

	// Iterate through each pixel in the image
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			// Write pixel values to the file
			if (image->type != 3) {
				fprintf(ascii, "%d ", (int)round(image->image[i][j].r));
			} else {
				fprintf(ascii, "%d ", (int)round(image->image[i][j].r));
				fprintf(ascii, "%d ", (int)round(image->image[i][j].g));
				fprintf(ascii, "%d ", (int)round(image->image[i][j].b));
			}
		}
		fprintf(ascii, "\n"); // Move to the next line in the file for the next
							  // row of pixels
	}
	fclose(ascii);
}

// Function to save the image in binary format
void save_binary(ImageInfo *image, char filename[])
{
	FILE *binary = fopen(filename, "w"); // Open the file for writing
	if (image->type == 5)
		fprintf(binary, "%s\n", "P5");
	if (image->type == 6)
		fprintf(binary, "%s\n", "P6");
	fprintf(binary, "%d %d\n", image->width, image->height);
	fprintf(binary, "%d\n", 255);

	// Iterate through each pixel in the image
	for (int i = 0; i < image->height; ++i) {
		for (int j = 0; j < image->width; ++j) {
			// Write pixel values to the file
			if (image->type != 6) {
				char red = (char)round(image->image[i][j].r);
				fwrite(&red, sizeof(char), 1, binary);
			} else {
				char red, green, blue;
				red = (char)round(image->image[i][j].r);
				green = (char)round(image->image[i][j].g);
				blue = (char)round(image->image[i][j].b);
				fwrite(&red, sizeof(char), 1, binary);
				fwrite(&green, sizeof(char), 1, binary);
				fwrite(&blue, sizeof(char), 1, binary);
			}
		}
	}
	fclose(binary);
}

// Function to handle the SAVE command
int save(char *input, ImageInfo *image)
{
	char filename[100];
	char c;
	if (!image->image) {
		printf("No image loaded\n");
		return 0;
	}

	sscanf(input, "%s", filename);
	sscanf(input, " %c", &c);

	// Check if the command ends with a newline character
	if (c == '\n')
		save_binary(image, filename);
	else {
		char format;
		sscanf(input, " %c", &format);

		// Determine the format based on user input
		if (format == 'a') {
			if (image->type > 3)
				image->type -= 3;
			save_ascii(image, filename);
		} else {
			if (image->type <= 3)
				image->type += 3;
		}
		save_binary(image, filename);
	}
	printf("Saved %s\n", filename);
	return 1;
}

#endif
