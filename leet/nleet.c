#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/*
 *     Nhance - Narthex leetifier
 *    
 *  By Michael Constantine Dimopoulos
 *  https://mcdim.xyz   <mk@mcdim.xyz>
 *  License: GNU GPL v3
 *        
 */


#define VERSION "v1.2"
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

void
print_only(FILE *f)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s",buffer);
	}
}

void
leetify(FILE *f, int full_upper)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		int i;

		/*
		 *
		 *     vv EDIT THIS PART vv
		 *
		 */

		int npflag = 0;
		for (i=0; i<=BUFFER_SIZE; i++) {
			if (buffer[i] == 'a' || buffer[i] == 'A') {
				buffer[i] = '@';
				npflag = 1;
			} else if (buffer[i] == 'o' || buffer[i] == 'O') {
				buffer[i] = '0';
				npflag = 1;
			} else if (buffer[i] == 'i' || buffer[i] == 'I') {
				buffer[i] = '1';
				npflag = 1;
			} else if (buffer[i] == 'e' || buffer[i] == 'E') {
				buffer[i] = '3';
				npflag = 1;
		/*	} else if (buffer[i] == 't' || buffer[i] == 'T') {
		 *		buffer[i] = '7';
		 *		npflag = 1; */
			}
		}
		if (npflag == 1) printf("%s",buffer);
	}
}

static void
die(char * str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

static void
help(char * exename)
{
	printf( "Nhance - Narthex leetfier %s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"
		"Usage:	cat [FILENAME] | %s\n"
		"	%s [FILENAME]\n",
		VERSION, exename, exename);
	exit(EXIT_SUCCESS);
}

void
main(int argc, char* argv[])
{
	int full_upper, file = 0, i;
	for (i=0; i<argc; i++) {
		if (strcmp(argv[i],"-v")==0)
			die(VERSION); 
		else if (strcmp(argv[i],"-h")==0)
			help(argv[0]);
		else
			file = i;
	}

	FILE *f2;
	if (file != 0) {
		FILE *f = fopen(argv[file], "r");

		if (f)
			f2= save_stdin(f);
		else
			fprintf(stderr, "%s: %s\n", argv[0], strerror(errno));
			exit(EXIT_FAILURE);
	} else {
		f2 = save_stdin(stdin);
	}

	rewind(f2);
	print_only(f2);
	rewind(f2);
	leetify(f2,0);
	if (full_upper == 1) {
		rewind(f2);
		leetify(f2,1);
	}

	fclose(f2);

	exit(EXIT_SUCCESS);
}
