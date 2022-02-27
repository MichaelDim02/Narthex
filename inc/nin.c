/*
 *    ninc - Narthex incrementor
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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define VERSION "v1.2.2"
#define BUFFER_SIZE 256

static void
help(char *exename)
{
	printf( "ninc - Narthex incrementor %s\n"
		"By Michael Constantine Dimopoulos <mk@mcdim.xyz>\n\n"

		"-d  use delimiters (specified in a string)\n"
		"-n  increment numerical lines as well\n"
		"-h  print this panel & exit\n"
		"-v  print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [MIN] [MAX] [OPTIONS]\n",
		VERSION, exename);
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

static int
isnumber(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (isdigit(str[i]) != 0)
			return 1;
	}
	return 0;
}

static inline int
check_num(int num, char * buffer)
{
	return ((num == 0 && isnumber(buffer) == 0) || num == 1);
}

static void
ninc(FILE *f, int min, int max, int numerical, char del)
{
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		strtok(buffer, "\n");
		for (int i = min; i <= max; i++) {
			if (check_num(numerical, buffer) == 1) {
				if (del == ' ')
					printf("%s%d\n", buffer, i);
				else
					printf("%s%c%d\n", buffer, del, i);
			}
		}
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
	int min = 1;
	int max = 10;
	int d = 0;
	char del[10];
	int numerical = 0;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt(argc, argv, "d:nvh")) != -1 )
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
			numerical=1;
			break;
		case '?':
			exit(EXIT_FAILURE);
			break;
		}


	if (optind < argc) {
		min = atoi(argv[optind]);
		max = atoi(argv[optind+1]);
	} else {
		fprintf(stderr, "%s: wrong number of arguments\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (min > max) {
		int temp = max;
		max = min;
		min = temp;
	}

	FILE *f;
	f = save_stdin(stdin);
	rewind(f);
	print_only(f);
	rewind(f);
	ninc(f, min, max, numerical, ' ');

	for (int i = 0; i < strlen(del); i++) {
		rewind(f);
		ninc(f, min, max, numerical, del[i]);
	}


	exit(EXIT_SUCCESS);

}
