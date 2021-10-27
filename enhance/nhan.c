/*
 *     nhance - Narthex enhancer
 *    
 *  By Michael Constantine Dimopoulos https://mcdim.xyz <mk@mcdim.xyz>
 *  License: GNU GPL v3
 *  
 *  nhance iterates over stdin and, after printing the dictionary as is
 *  it will reprint it this time with the first letter capitalized. Ir
 *  can also append full capitalizations at the end of the dictionary
 *  with the -f flag.
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

#define VERSION "v1.3.1"
#define BUFFER_SIZE 256


static void
help(char *exename)
{
	printf( "nhance - Narthex enhancer %s\n"
		"By Michael Constantine Dimopoulos <mk@mcdim.xyz>\n\n"

		"-f  append full capitalization\n"
		"-h  print this panel & exit\n"
		"-v  print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [-f]\n"
		"	%s [-f] [FILENAME]\n",
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
	while (fgets(buffer, sizeof(buffer), f) != NULL)  {
		fprintf(f2, "%s", buffer);
	}
	fclose(f);
	return f2;
}

void
cap(char string[])
{  
	int i;
	int x = strlen(string);
	for (i=0; i<x-1; i++){
		if (isalpha(string[i])){ 
			string[i]= toupper(string[i]);
		}
	}
}

void
print_only(FILE *f)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s",buffer);
	}
}

static void
enhance(FILE *f, int full_upper)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		if (isalpha(buffer[0])) {
			if (full_upper == 0)
				buffer[0] = toupper(buffer[0]);	
			else
				cap(buffer);

			printf("%s",buffer);	
		}

	}
}

void
main(int argc, char *argv[])
{
	int full_upper, file = 0, i;
	for (i = 0; i < argc; i++) {
		if (strcmp(argv[i],"-f")==0) 
			full_upper = 1;
		else if (strcmp(argv[i],"-v")==0)
			die(VERSION); 
		else if (strcmp(argv[i],"-h")==0)
			help(argv[0]);
		else
			file = i;
	}

	FILE *f2;
	if (file != 0) {
		FILE *f = fopen(argv[file], "r");

		if (f) {
			f2 = save_stdin(f);
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
	enhance(f2,0);

	if (full_upper == 1) {
		rewind(f2);
		enhance(f2,1);
	}

	fclose(f2);

	exit(EXIT_SUCCESS);
}
