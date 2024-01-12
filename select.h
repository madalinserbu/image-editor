#ifndef __SELECT__
#define __SELECT__

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areCoordinatesValid(int x1, int y1, int x2, int y2, ImageInfo *image)
{
	// Ensure that the coordinates are in the correct order
	if (x1 > x2) {
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	if (y1 > y2) {
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	// Check if the coordinates are within the valid range
	if (x1 < 0 || y1 < 0 || x2 >= image->width || y2 >= image->height ||
		x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		return 0;
	}

	return 1; // Coordinates are valid
}

// Funcție pentru a selecta o porțiune a imaginii
int selectImage(int x1, int y1, int x2, int y2, ImageInfo *image)
{
	if (image->image == NULL) {
		printf("No image loaded\n");
		return 0; // Fără imagine încărcată
	}

	// Determinăm cele mai mici valori pentru fiecare interval (x1, x2, y1, y2)
	int minX = (x1 < x2) ? x1 : x2;
	int maxX = (x1 < x2) ? x2 : x1;
	int minY = (y1 < y2) ? y1 : y2;
	int maxY = (y1 < y2) ? y2 : y1;
	// Replace the 'swap_int' calls and coordinate validation with a single call
	if (!areCoordinatesValid(minX, minY, maxX - 1, maxY - 1, image)) {
		return 0; // Coordinates are not valid
	}

	// Setăm coordonatele pentru selecție
	image->x1 = minX;
	image->y1 = minY;
	image->x2 = maxX;
	image->y2 = maxY;
	printf("Selected %d %d %d %d\n", image->x1, image->y1, image->x2,
		   image->y2);

	return 1; // Succes
}

// Funcție pentru a selecta o porțiune a imaginii
int select_command(char *input, ImageInfo *image)
{
	// Verificăm dacă comanda este pentru a selecta întreaga imagine
	if (strstr(input, "ALL")) {
		// Apelăm funcția care realizează selecția întregii imagini
		char tmp[LENGTH];
		if (sscanf(input, "%s", tmp) == 1 && strcmp(tmp, "ALL") == 0) {
			// Setăm coordonatele pentru întreaga imagine
			if (image->image == NULL) {
				printf("No image loaded\n");
				return 0; // Fără imagine încărcată
			}
			image->x1 = 0;
			image->y1 = 0;
			image->x2 = image->width;
			image->y2 = image->height;
			printf("Selected ALL\n");
			return 1; // Succes
		}
		printf("Invalid command\n");
		return 0;
	} else {
		int x1, y1, x2, y2, extra;

		// Parsăm input-ul pentru a extrage coordonatele
		int result =
			sscanf(input, "%d %d %d %d %d", &x1, &y1, &x2, &y2, &extra);

		// Verificăm dacă s-au citit exact patru valori pentru o operație de
		// selectare
		if (result != 4) {
			printf("Invalid command\n");
			return 0; // Eșuare
		}

		if (x1 == x2 || y1 == y2) {
			printf("Invalid set of coordinates\n");
			return 0;
		}

		// Apelăm funcția care realizează selecția
		return selectImage(x1, y1, x2, y2, image);
	}
	return 1;
}

#endif