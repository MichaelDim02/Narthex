/*
 *    ngen - Narthex generator
 *
 *  By Michael Constantine Dimopoulos https://mcdim.xyz <mk@mcdim.xyz>
 *  License: GNU GPL v3
 *
 *  ninc will iterate over stdin and  after printing the dictionary as is
 *  it will reprint it but will also multiply each line with the
 *  difference of max-min, and will append n to each line, where n is
 *  increased after every line from min to max inclusive. (I know, I know.
 *  Just try to use it and it will make more sense).
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "v1.0"

static void
help(char *exename)
{
	printf( "ngen - Narthex generator %s\n"
		"By Michael Constantine Dimopoulos <mk@mcdim.xyz>\n\n"

		"-h  print this panel & exit\n"
		"-v  print current version & exit\n\n"

		"Usage:	%s [MIN] [MAX] [CHARSET]\n"
		"MAX must be greater than or equal to MIN\n",
		VERSION, exename);
	exit(EXIT_SUCCESS);
}

static inline void
die(char *str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

int rec(char *chars, int l, int *c, int len, int exit)
{
	if (exit == 1) return 1;

	for (int i=0; i<=len-1; i++) {
		printf("%c", chars[c[i]]);
	}
	printf("\n");

	for (int i=len-1; i>=0; i--) {
		if (c[i] < l) {
			c[i]++;
			exit = rec(chars, l, c, len, exit);
		} else {
			if (i == 0) {
				return 1;
			}
			c[i] = 0;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc != 2 && argc != 4) {
		help(argv[0]);
	}

	if (strcmp(argv[1], "-h") == 0) {
		help(argv[0]);
	}

	if (strcmp(argv[1], "-v") == 0) {
		printf("%s\n", VERSION);
		exit(EXIT_SUCCESS);
	}

	if (argc != 4) {
		help(argv[0]);
	}

	int min = atoi(argv[1]);
	int max = atoi(argv[2]);

	if (min > max) die("MAX must be greater than or equal to MIN");

	/* get unique */
	int len = strlen(argv[3]);
	int size = 1;
	char *uniq = (char *)malloc(size * sizeof(char));
	uniq[0] = '\0';

	for (int i=0; i<len; i++) {
		int found = 0;
		for (int j=0; j<strlen(uniq); j++) {
			if (argv[3][i] == uniq[j]) {
				found = 1;
			}
		}

		if (found == 0) {
			size++;
			uniq = (char *)realloc(uniq, size * sizeof(char));
			uniq[size-2] = argv[3][i];
			uniq[size-1] = '\0';
		}
	}
	/* ********** */

	for (int l=min; l<=max; l++) {
		int s = strlen(uniq)-1;
		int c[l];
		for (int i=0; i<l; i++) {
			c[i] = 0;
		}

		rec(uniq, s, c, l, 0);
	}
	return 0;
}
