#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 *    Ninc - Narthex incrementor
 *
 *  By Michael Constantine Dimopoulos
 *  https://mcdim.xyz	<mk@mcdim.xyz>
 *  License: GNU GPL v3
 *
 */

#define VERSION "0.1"
#define BUFFER_SIZE 256

static int
isnumber(char * str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (isdigit(str[i]) != 0)
			return 1;
	}
	return 0;
}

static void
ninc(FILE *f, int min, int max, int numerical)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		strtok(buffer, "\n");
		puts(buffer);
		for (int i = min; i <= max; i++) {
			if ((numerical == 0 && isnumber(buffer) == 0) || numerical == 1) {
				printf("%s%d\n", buffer, i);
			}
		}
	}
}

static void
help(char * exename)
{
	printf( "Ninc - Narthex incrementor %s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-n  Increment numerical lines as well\n"
		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [MIN] [MAX] [OPTIONS]\n",
		VERSION, exename);
}

void
main(int argc, char * argv[])
{
	int min = 1;
	int max = 10;
	int numerical = 0;

	if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0)
			help(argv[0]);
		else if (strcmp(argv[1], "-v") ==0)
			printf("%s\n", VERSION);
		exit(0);
	} else if (argc == 3) {
		min = atoi(argv[1]);
		max = atoi(argv[2]);
	} else if (argc == 4) {
		min = atoi(argv[1]);
		max = atoi(argv[2]);
		if (strcmp(argv[3], "-n") == 0)
			numerical = 1;
	} else {
		fprintf(stderr, "%s: wrong number of arguments\n", argv[0]);
		exit(0);
	}

	if (min <= max) {
		ninc(stdin, min, max, numerical);
	}
	exit(0);
}
