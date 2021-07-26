#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/*
 *    Ncom - Narthex combinator (?)
 *
 *  By Michael Constantine Dimopoulos
 *  https://mcdim.xyz	<mk@mcdim.xyz>
 *  License: GNU GPL v3
 *  
 *  Currently under development
 *  :)
 *
 */

#define VERSION "v1.0"
#define BUFFER_SIZE 256

static FILE *
save_stdin(FILE *f)
{
	FILE *f2 = tmpfile();
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
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
com(FILE *f2, FILE *f3, int d, int u, int m, int n)
{
	char buffer[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f2) != NULL) {
		strtok(buffer, "\n");
		while (fgets(buffer2, sizeof(buffer2), f3) != NULL) {
			strtok(buffer2, "\n");
			if ((n == 0 && isnumber(buffer) == 0) || n == 1) {
				printf("%s%s\n", buffer, buffer2);
				if (d == 1) printf("%s%s%s\n", buffer, ".", buffer2);
				if (m == 1) printf("%s%s%s\n", buffer, "-", buffer2);
				if (u == 1) printf("%s%s%s\n", buffer, "-", buffer2);
			}
		}
		rewind(f3);
	}
}

static void
print_only(FILE *f)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s", buffer);
	}
}

static void
help(char * exename)
{
	printf( "Ninc - Narthex incrementor %s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-d  Use dot separator\n"
		"-u  Use underscore separator\n"
		"-m  Use hyphen separator\n"
		"-n  Exclude numerical bases\n"
		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [OPTIONS]\n",
		VERSION, exename);
	exit(EXIT_SUCCESS);
}

void
die(char * str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

void
main(int argc, char * argv[])
{
	int d=0, u=0, m=0, n=1;
	char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;

	while ( (c = getopt (argc, argv, "dumnvhh:")) != -1 )
		switch (c) {
			case 'v':
				die(VERSION);
			case 'h':
				help(argv[0]);
			case 'd':
				d=1;
				break;
			case 'u':
				u=0;
				break;
			case 'm':
				m=1;
				break;
			case 'n':
				n=1;
				break;
			case '?':
				fprintf (stderr, "Unknown option `\\x%x'.\n", optopt);
				exit(EXIT_FAILURE);
		}
	FILE * f2, * f3;
	f2 = save_stdin(stdin);
	rewind(f2);
	f3 = save_stdin(f2);

	rewind(f2);
	print_only(f2);
	rewind(f2);
	rewind(f3);
	com(f2, f3, d, u, m, n);

	fclose(f2);

	exit(EXIT_SUCCESS);
}
