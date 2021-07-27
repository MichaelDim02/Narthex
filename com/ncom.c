#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/*
 *    ncom - Narthex combinator (?)
 *
 *  By Michael Constantine Dimopoulos
 *  https://mcdim.xyz	<mk@mcdim.xyz>
 *  License: GNU GPL v3
 *  
 *  ncom iterates over stdin and after
 *  printing the dictionary as is, it will
 *  print it again but will also append
 *  every line of stdin to each iteration
 *  creating, that way, a list of combi-
 *  nations (pairs) of the lines.
 *
 *  By default, it will append when the
 *  base is the same as the appended part
 *  (i.e wordword), but that can be
 *  switched off with the -b flag. It
 *  can also use other separators, such
 *  as a hyphen or a dot, all with their
 *  own flags.
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
com(FILE *f2, FILE *f3, int d, int u, int m, int n, int b)
{
	char buffer[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];

	while (fgets(buffer, sizeof(buffer), f2) != NULL) {
		strtok(buffer, "\n");
		while (fgets(buffer2, sizeof(buffer2), f3) != NULL) {
			strtok(buffer2, "\n");
			if ((n == 0 && isnumber(buffer) == 0) || n == 1) {
				if ((b == 1 && strcmp(buffer,buffer2) != 0) || b == 0) {
					if (d == 1)      printf("%s.%s\n", buffer, buffer2);
					else if (m == 1) printf("%s-%s\n", buffer, buffer2);
					else if (u == 1) printf("%s_%s\n", buffer, buffer2);
					else             printf("%s%s\n",  buffer, buffer2);
				}
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
	printf( "ncom - Narthex combinator %s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-d  Use dot separator\n"
		"-u  Use underscore separator\n"
		"-m  Use hyphen separator\n"
		"-n  Exclude numerical bases\n"
		"-b  Exclude base-appended\n"
		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [OPTIONS]\n",
		VERSION, exename);
	exit(EXIT_SUCCESS);
}

static void
die(char * str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

void
main(int argc, char * argv[])
{
	int d=0, u=0, m=0, b=0, n=1;
	char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;

	while ( (c = getopt(argc, argv, "duuumnvbhh:")) != -1 )
		switch (c) {
			case 'v':
				die(VERSION);
			case 'h':
				help(argv[0]);
			case 'd':
				d=1;
				break;
			case 'u':
				u=1;
				break;
			case 'm':
				m=1;
				break;
			case 'n':
				n=1;
				break;
			case 'b':
				b=1;
				break;
			case '?':
				/*fprintf (stderr, "Unknown option `%c`\n", c);
				exit(EXIT_FAILURE);*/
				break;
		}
	/* for troubleshooting: */
	/* printf("d:%i\nm:%i\nu:%i\n", d, m, u); */

	FILE * f2, * f3;
	f2 = save_stdin(stdin);
	rewind(f2);
	f3 = save_stdin(f2);

	rewind(f2);
	print_only(f2);
	rewind(f2);
	rewind(f3);

	/* Now this will call com(); for every
	 * possible set option.
	 *
	 *          d  u  m      */

	com(f2, f3, 0, 0, 0, n, b);

	if (d == 1) {
		rewind(f2);
		rewind(f3);
		com(f2, f3, 1, 0, 0, n, b);
	}
	if (u == 1) {
		rewind(f2);
		rewind(f3);
		com(f2, f3, 0, 1, 0, n, b);
	}
	if (m == 1) {
		rewind(f2);
		rewind(f3);
		com(f2, f3, 0, 0, 1, n, b);
	}

	fclose(f2);
	fclose(f3);

	exit(EXIT_SUCCESS);
}
