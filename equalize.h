#ifndef __EQUALIZE__
#define __EQUALIZE__

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Function to clamp a double value between 0 and 255
int my_clamp(double x)
{
    if (x < 0)
        x = 0;
    else if (x > 255)
        x = 255;
    return (int)x;
}

// Function to calculate the sum of elements in a vector up to a certain position
int sum(int *vector, int position)
{
    int s = 0;
    for (int i = 0; i <= position; ++i) {
        s += vector[i];
    }
    return s;
}

// Function to apply the equalization operation on a pixel
int equalize_pixel(int pixel, int *histogram, int num_pixels)
{
    int aux = sum(histogram, pixel) * 255 / num_pixels;
    return my_clamp(aux);
}

// Function for equalizing a black and white image
ImageInfo *equalize_command(ImageInfo *img)
{
    if (img == NULL || img->image == NULL) {
        printf("No image loaded\n");
        return NULL;
    }

    if (img->type != 2) // Check if the image is black and white
    {
        printf("Black and white image needed\n");
        return NULL;
    }

    // Calculate the histogram
    int histogram[256] = {0};
    int num_pixels = img->width * img->height;

    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
            histogram[img->image[i][j].r]++;
        }
    }

    // Apply equalization on each pixel
    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
            img->image[i][j].r =
                equalize_pixel(img->image[i][j].r, histogram, num_pixels);
        }
    }

    printf("Equalize done\n");
    return img;
}

#endif