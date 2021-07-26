#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 *    ninc - Narthex incrementor
 *
 *  By Michael Constantine Dimopoulos
 *  https://mcdim.xyz	<mk@mcdim.xyz>
 *  License: GNU GPL v3
 *
 *  ninc will iterate over stdin and
 *  after printing the dictionary as
 *  is, it will reprint it but will
 *  also multiply each line with the
 *  difference of max-min, and will
 *  append n to each line, where n is
 *  increased after every line from
 *  min to max inclusive. (I know, I
 *  know. Just try to use it and it
 *  will make more sense).
 *
 */

#define VERSION "v1.0"
#define BUFFER_SIZE 256

FILE *
save_stdin(FILE *f)
{
	FILE *f2 = tmpfile();
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL)  {
		fprintf(f2, "%s", buffer);
	}
	fclose(f);
	return f2;
}

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
		for (int i = min; i <= max; i++) {
			if ((numerical == 0 && isnumber(buffer) == 0) || numerical == 1) {
				printf("%s%d\n", buffer, i);
			}
		}
	}
}

void
print_only(FILE *f)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s",buffer);
	}
}

static void
help(char * exename)
{
	printf( "ninc - Narthex incrementor %s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-n  Increment numerical lines as well\n"
		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [MIN] [MAX] [OPTIONS]\n",
		VERSION, exename);
	exit(EXIT_SUCCESS);
}

static void
die(char * str)
{
	printf("%d\n", str);
	exit(EXIT_SUCCESS);
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
		exit(EXIT_FAILURE);
	}

	if (min <= max) {
		FILE * f;
		f = save_stdin(stdin);
		rewind(f);
		print_only(f);
		rewind(f);
		ninc(f, min, max, numerical);
	}

	exit(EXIT_SUCCESS);
}
