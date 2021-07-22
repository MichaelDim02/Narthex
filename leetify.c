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


#define VERSION "v1.0"
#define BUFFER_SIZE 256

char
save_stdin(FILE *f)
{
	FILE *fw = fopen("/tmp/tempfile-61436134.txt", "w");
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL)  {
		fprintf(fw, "%s", buffer);
	}
	fclose(fw);
	fclose(f);
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
enhance(FILE *f, int full_upper)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		int i;

		/*
		 *
		 *     vv EDIT THIS PART vv
		 *
		 */

		for (i=0; i<=BUFFER_SIZE; i++) {
			if      (buffer[i] == 'a' || buffer[i] == 'A') buffer[i] = '@';
			else if (buffer[i] == 'o' || buffer[i] == 'O') buffer[i] = '0';
			else if (buffer[i] == 'i' || buffer[i] == 'I') buffer[i] = '1';
			else if (buffer[i] == 'e' || buffer[i] == 'E') buffer[i] = '3';
		/*	else if (buffer[i] == 't' || buffer[i] == 'T') buffer[i] = '7';*/
		}
		printf("%s",buffer);
	}
}

void die(char * str)
{
	printf("%s\n", str);
	exit(0);
}

void help(char * exename)
{
	printf( "Nhance - Narthex leetfier%s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"
		"Usage:	cat [FILENAME] | %s\n",
		"	%s [FILENAME]\n",
		VERSION, exename);
	exit(0);
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

	if (file != 0) {
		FILE *f = fopen(argv[file], "r");

		if (f)
			save_stdin(f);
		else
			fprintf(stderr, "nenhan: %s\n", strerror(errno));
	} else {
		save_stdin(stdin);
	}

	FILE *fr = fopen("/tmp/tempfile-61436134.txt", "r");
	print_only(fr);
	rewind(fr);
	enhance(fr,0);
	if (full_upper == 1) {
		rewind(fr);
		enhance(fr,1);
	}
	fclose(fr);
	remove("/tmp/tempfile-61436134.txt");

	exit(0);
}
