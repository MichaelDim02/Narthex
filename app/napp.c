/*
 *    napp - Narthex appender
 *
 *  By Michael Constantine Dimopoulos https://mcdim.xyz	<mk@mcdim.xyz>
 *  License: GNU GPL v3
 *
 *  napp will append to the end of, or insert to the front of, each line
 *  of stdin, characters from a specified character set, or words from a
 *  wordlist. It may or may not print stdin as is (-s)
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

#define VERSION "v1.1.2"
#define BUFFER_SIZE 256

static inline void
usage(char *exename)
{
	fprintf(stderr, "Usage:	cat [FILENAME]"
		"| %s [-c] [CHARSET] [-w] [FILE] [-s] [-f]\n",
		exename);
}

static void
help(char *exename)
{
	printf( "napp - Narthex appender %s\n"
		"By Michael Constantine Dimopoulos <mk@mcdim.xyz>\n\n"

		"-c  specify charset\n"
		"-w  specify dictionary of words\n"
		"-f  insert before the word (default is after)\n"
		"-s  salt mode (do not print wordlist as is)\n"
		"-h  print this panel & exit\n"
		"-v  print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [-c] [CHARSET] [-w] [FILE]"
	        "[-s] [-f]\n", VERSION, exename);
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
	while(fgets(buffer, sizeof(buffer), f) != NULL)  {
		fprintf(f2, "%s", buffer);
	}
	fclose(f);
	return f2;
}

static void
nappc(FILE *f, int front, char c)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		strtok(buffer, "\n");
		if (front)
			printf("%c%s\n", c, buffer);
		else
			printf("%s%c\n", buffer, c);
	}
}

static void
nappw(FILE *f, int front, char *w)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		strtok(buffer, "\n");
		if (front)
			printf("%s%s\n", w, buffer);
		else
			printf("%s%s\n", buffer, w);
	}
}

static void
print_only(FILE *f)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s",buffer);
	}
}

void
main(int argc, char * argv[])
{
	int c1, w, s, front;
	c1 = w = s = front = 0;
	char cv[BUFFER_SIZE], wv[BUFFER_SIZE];
	int index;
	int c;
	extern char *optarg;
	int optind = 0;

	while ((c = getopt(argc, argv, "c:w:sfvh")) != -1 ) {
		switch (c) {
		case 'v':
			die(VERSION);
		case 'h':
			help(argv[0]);
		case 'c':
			c1=1;
			w=0;
			strncpy(cv, optarg, BUFFER_SIZE);
			break;
		case 'w':
			w=1;
			c1=0;
			strncpy(wv, optarg, BUFFER_SIZE);
			break;
		case 's':
			s=1;
			break;
		case 'f':
			front=1;
			break;
		case '?':
			usage(argv[0]);
			exit(EXIT_FAILURE);
			break;
		}
	}

	if (c1 != 1 && w != 1) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *f;
	f = save_stdin(stdin);
	rewind(f);

	if (!s) {
		print_only(f);
		rewind(f);
	}

	if (w) {
		FILE *f2;
		f2 = fopen(wv,"r");

		if (f2 == NULL) {
			fprintf(stdout, "%s: Error opening file\n",
			argv[0]);
			exit(EXIT_FAILURE);
		}

		char word[BUFFER_SIZE];
		while(fgets(word, sizeof(word), f2) != NULL) {
			strtok(word, "\n");
			nappw(f, front, word);
			rewind(f);
		}
	}

	if (c1) {
		for (int i = 0; cv[i] != '\0'; i++) {
			nappc(f, front, cv[i]);
			rewind(f);
		}
	}

	exit(EXIT_SUCCESS);
}
