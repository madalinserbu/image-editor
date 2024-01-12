#ifndef __APPLY__
#define __APPLY__

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to clamp a value between a specified range
int clamp_value(double x, int min, int max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return x;
}

// Function to apply a filter to the selected region of the image
void apply_filter(int filter_type, ImageInfo *image)
{
	if (image == NULL || image->image == NULL) {
		printf("No image loaded\n");
		return;
	}

	if (image->type != 3 && image->type != 6) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	// Define filter kernels
	int edgeKernel[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
	int sharpenKernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
	int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	int gaussianBlurKernel[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

	int(*selectedKernel)[3] = NULL;

	// Assign selected kernel based on the filter type
	switch (filter_type) {
	case 1:
		selectedKernel = edgeKernel;
		break;
	case 2:
		selectedKernel = sharpenKernel;
		break;
	case 3:
		selectedKernel = blurKernel;
		break;
	case 4:
		selectedKernel = gaussianBlurKernel;
		break;
	default:
		printf("Invalid filter type\n");
		return;
	}

	// Allocate memory for the auxiliary matrix
	rgb **auxiliaryMatrix = (rgb **)malloc(image->height * sizeof(rgb *));
	for (int i = 0; i < image->height; ++i) {
		auxiliaryMatrix[i] = (rgb *)malloc(image->width * sizeof(rgb));
	}
	int edge_u, edge_l, edge_d, edge_r;
	if (image->x1 == 0)
		edge_l = image->x1 + 1;
	else
		edge_l = image->x1;
	if (image->y1 == 0)
		edge_u = image->y1 + 1;
	else
		edge_u = image->y1;
	if (image->x2 == image->width)
		edge_r = image->x2 - 1;
	else
		edge_r = image->x2;
	if (image->y2 == image->height)
		edge_d = image->y2 - 1;
	else
		edge_d = image->y2;

	// Apply the filter to the selected region
	for (int i = edge_u; i < edge_d; ++i) {
		for (int j = edge_l; j < edge_r; ++j) {
			double sumr = 0.0, sumg = 0.0, sumb = 0.0;

			// Apply the kernel for every pixel
			for (int m = 0; m < 3; ++m) {
				for (int n = 0; n < 3; ++n) {
					int x = j - 1 + n;
					int y = i - 1 + m;

					if (x >= 0 && x < image->width && y >= 0 &&
						y < image->height) {
						sumr += image->image[y][x].r * selectedKernel[m][n];
						sumg += image->image[y][x].g * selectedKernel[m][n];
						sumb += image->image[y][x].b * selectedKernel[m][n];
					}
				}
			}

			// Apply the clamp function to avoid overflow
			auxiliaryMatrix[i][j].r =
				clamp_value(sumr / ((filter_type == 3)	 ? 9.0
									: (filter_type == 4) ? 16.0
														 : 1.0),
							0, 255);
			auxiliaryMatrix[i][j].g =
				clamp_value(sumg / ((filter_type == 3)	 ? 9.0
									: (filter_type == 4) ? 16.0
														 : 1.0),
							0, 255);
			auxiliaryMatrix[i][j].b =
				clamp_value(sumb / ((filter_type == 3)	 ? 9.0
									: (filter_type == 4) ? 16.0
														 : 1.0),
							0, 255);
		}
	}

	// Copy the values from the auxiliary matrix to the image matrix
	for (int i = edge_u; i < edge_d; ++i) {
		for (int j = edge_l; j < edge_r; ++j) {
			image->image[i][j] = auxiliaryMatrix[i][j];
		}
	}

	// Free memory for the auxiliary matrix
	for (int i = 0; i < image->height; ++i) {
		free(auxiliaryMatrix[i]);
	}
	free(auxiliaryMatrix);

	printf("APPLY %s done\n", (filter_type == 1)   ? "EDGE"
							  : (filter_type == 2) ? "SHARPEN"
							  : (filter_type == 3) ? "BLUR"
												   : "GAUSSIAN_BLUR");
}

// Function to handle the APPLY command
int apply_command(char *input, ImageInfo *image)
{
	if (image == NULL || image->image == NULL) {
		printf("No image loaded\n");
		return 0;
	}
	char param[LENGTH];
	if (sscanf(input, "%s", param) == EOF) {
		printf("Invalid command\n");
		return 0;
	}
	// Parse the parameter to get the filter type
	int filter_type = -1;

	if (strcmp(param, "EDGE") == 0) {
		filter_type = 1;
	} else if (strcmp(param, "SHARPEN") == 0) {
		filter_type = 2;
	} else if (strcmp(param, "BLUR") == 0) {
		filter_type = 3;
	} else if (strcmp(param, "GAUSSIAN_BLUR") == 0) {
		filter_type = 4;
	} else
		printf("Apply parameter invalid\n");

	// Check if the filter type is valid
	if (filter_type != -1) {
		// Apply the filter to the selected region of the image
		apply_filter(filter_type, image);
	} else
		printf("Apply parameter invalid\n");
	return 0;
}

#endif
