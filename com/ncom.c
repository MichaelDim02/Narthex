/*
 *    ncom - Narthex combinator
 *
 *  By Michael Constantine Dimopoulos https://mcdim.xyz	<mk@mcdim.xyz>
 *  License: GNU GPL v3
 *
 *  ncom iterates over stdin and after printing the dictionary as is, it
 *  will print it again but will also append every line of stdin to each
 *  iteration creating, that way, a list of combinations (pairs) of
 *  the lines.
 *
 *  By default, it will append when the *  base is the same as the
 *  appended part (i.e wordword), but that can be *  switched off with the
 *  -b flag. It can also use other separators, such *  as a hyphen or a
 *  dot, all with their own flags.
 *
 * * * * * * * *
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define VERSION "v1.2.0"
#define BUFFER_SIZE 256

static void
help(char *exename)
{
	printf( "ncom - Narthex combinator %s\n"
		"By Michael Constantine Dimopoulos <mk@mcdim.xyz>\n\n"

		"-d  use delimiters (specified in a string)\n"
		"-n  exclude numerical bases\n"
		"-b  exclude base-appended\n"
		"-h  print this panel & exit\n"
		"-v  print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [-d] [-n] [-b]\n"
		"        %s [FILENAME] [OPTIONS]\n",
		VERSION, exename, exename);
	exit(EXIT_SUCCESS);
}

static inline void
die(char *str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

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

static inline void
ssprint(char *buffer, char *buffer2, char del, int n, int b)
{
	if ((n == 1 && isnumber(buffer) == 0) || n == 0) {
		if ((b == 1 && strcmp(buffer,buffer2) != 0) || b == 0) {
			if (del == ' ')
				printf("%s%s\n", buffer, buffer2);
			else
				printf("%s%c%s\n", buffer, del, buffer2);
		}
	}
}

static void
com(FILE *f2, FILE *f3, char del, int n, int b)
{
	char buffer[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];

	while (fgets(buffer, sizeof(buffer), f2) != NULL) {
		strtok(buffer, "\n");
		while (fgets(buffer2, sizeof(buffer2), f3) != NULL) {
			strtok(buffer2, "\n");
			ssprint(buffer, buffer2, del, n, b);
		}

		rewind(f3);
	}
}

static void
print_only(FILE *f)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s", buffer);
	}
}

void
main(int argc, char *argv[])
{
	int d, b, n, t;
	d = b = n = t = 0;
	char *cvalue = NULL;
	char del[10];
	char filename[256];
	int filename_given = 0;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt(argc, argv, "d:nvbh")) != -1 )
		switch (c) {
		case 'v':
			die(VERSION);
		case 'h':
			help(argv[0]);
		case 'd':
			d=1;
			strncpy(del, optarg, 10);
			break;
		case 'n':
			n=1;
			break;
		case 'b':
			b=1;
			break;
		case '?':
			exit(EXIT_FAILURE);
			break;
		}

	if (optind < argc) {
		strncpy(filename, argv[optind], 256);
		filename_given = 1;
	}

	FILE *f2, *f3;
	if (filename_given == 0) {
		f2 = save_stdin(stdin);
		rewind(f2);
		f3 = save_stdin(f2);
	} else {
		f2 = fopen(filename, "r");
		f3 = fopen(filename, "r");
		if (!f2) {
			fprintf(stderr, "File could not be opened: %s\n",
			filename);
			exit(EXIT_FAILURE);
		}
	}

	rewind(f2);
	print_only(f2);
	rewind(f2);
	rewind(f3);

	com(f2, f3, ' ', n, b);

	for (int i = 0; i < strlen(del); i++) {
		rewind(f2);
		rewind(f3);
		com(f2, f3, del[i], n, b);
	}

	fclose(f2);
	fclose(f3);

	exit(EXIT_SUCCESS);
}
