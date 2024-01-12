#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apply.h"
#include "crop.h"
#include "equalize.h"
#include "exit.h"
#include "load.h"
#include "save.h"
#include "select.h"
#include "utils.h"

int main(void)
{
	char comanda[100], s[100];
	char p[100];
	ImageInfo image;
	image.image = NULL;
	image.height = 0;
	image.width = 0;
	image.x1 = 0;
	image.x2 = 0;
	image.y1 = 0;
	image.y2 = 0;

	do {
		// Reading from stdin line by line
		fgets(s, 100, stdin);
		// Determinating the operation keyword from the entire input
		char s_cpy[100];
		// Storing the name of the operation in p
		strcpy(s_cpy, s);
		// Extracting the command
		strcpy(p, strtok(s_cpy, " \n"));
		strcpy(comanda, p);

		// If there is a command, handle it
		if (comanda[0] != '\0') {
			// Cropping the name of the operation from the input
			strcpy(s_cpy, s + strlen(p) + 1);
			strcpy(s, s_cpy);

			// Check the command and execute the corresponding operation
			if (!strcmp(comanda, "LOAD"))
				load_command(s, &image);
			else if (!strcmp(comanda, "SELECT"))
				select_command(s, &image);
			else if (!strcmp(comanda, "CROP"))
				crop_command(&image);
			else if (!strcmp(comanda, "APPLY"))
				apply_command(s, &image);
			else if (!strcmp(comanda, "SAVE"))
				save(s, &image);
			else if (!strcmp(comanda, "EXIT"))
				exit_command(&image);
			else if (!strcmp(comanda, "EQUALIZE"))
				equalize_command(&image);
			else {
				printf("Invalid command\n");
			}
		}
	} while (strcmp(comanda, "EXIT"));

	return 0;
}
