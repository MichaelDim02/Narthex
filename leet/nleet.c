/*
 *     nleet - Narthex leetifier
 *    
 *  By Michael Constantine Dimopoulos https://mcdim.xyz <mk@mcdim.xyz>
 *  License: GNU GPL v3 *        
 *  nleet will iterate over stdin or a file and, after printing the
 *  dictionary as is, it will reprint it this time with some characters
 *  replaced with their leet equivalents (hello -> h3ll0), as determined
 *  by nleet, or, alternatively, as specified by the user.
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
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define VERSION "v1.4.0"
#define BUFFER_SIZE 256


static void
help(char *exename)
{
	printf( "nleet - Narthex leetfier %s\n"
		"By Michael Constantine Dimopoulos <mk@mcdim.xyz>\n\n"

		"-h  print this panel & exit\n"
		"-v  print current version & exit\n\n"
		"Usage:	cat [FILENAME] | %s [OPTIONS]\n"
		"	%s [FILENAME] [OPTIONS]\n",
		VERSION, exename, exename);
	exit(EXIT_SUCCESS);
}

static inline void
die(char * str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

static FILE *
save_stdin(FILE *f)
{
	FILE *f2 = tmpfile();
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL)  {
		fprintf(f2, "%s", buffer);
	}
	fclose(f);
	return f2;
}

static void
print_only(FILE *f)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s",buffer);
	}
}

static void
leetify(FILE *f, char a[], char b[], int len)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		int i, j;

		int npflag = 0;
		for (i = 0; i < BUFFER_SIZE; i++) {
			for (j = 0; j < len; j++) {
				if (buffer[i] == a[j]) {
 					npflag = 1;
					buffer[i] = b[j];
				}
			}
		}

		if (npflag == 1) printf("%s",buffer);
	}
}

void
main(int argc, char* argv[])
{
	int file = 0, args = 0, j = 0;
	char a[100], b[100];
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i],"-v") == 0) {
			die(VERSION); 
		} else if (strcmp(argv[i], "-h") == 0) {
			help(argv[0]);
		} else {
			if (strlen(argv[i]) == 3 && i<100) {
				args = 1;
				a[j] = argv[i][0];
				b[j] = argv[i][2];
				j++;
			} else {
				file = i;
			}
		}
	}

	FILE *f2;
	if (file != 0) {
		FILE *f = fopen(argv[file], "r");

		if (f) {
			f2= save_stdin(f);
		} else {
			fprintf(stderr, "%s: %s\n", argv[0], strerror(errno));
			exit(EXIT_FAILURE);
		}
	} else {
		f2 = save_stdin(stdin);
	}

	rewind(f2);
	print_only(f2);
	rewind(f2);
	if (args == 1) {
		leetify(f2, a, b, j);
	} else {
		char c[4] = {'a', 'e', 'i', 'o'};
		char d[4] = {'@', '3', '1', '0'};
		leetify(f2, c, d, 4);
	}

	fclose(f2);

	exit(EXIT_SUCCESS);
}
