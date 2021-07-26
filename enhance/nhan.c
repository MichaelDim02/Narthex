#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/*
 *     Nhance - Narthex enhancer
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

void cap(char string[]){  
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
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s",buffer);
	}
}

void
enhance(FILE *f, int full_upper)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		if (isalpha(buffer[0])) {
			if (full_upper ==0)
				buffer[0] = toupper(buffer[0]);	
			else
				cap(buffer);
			printf("%s",buffer);	
		}

	}
}

void die(char * str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

void help(char * exename)
{
	printf( "Nhance - Narthex enhancer %s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-f  Append full capitalization\n"
		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"
		"Usage:	cat [FILENAME] | %s [OPTIONS]\n"
		"	%s [OPTIONS] [FILENAME]\n",
		VERSION, exename, exename);
	exit(EXIT_SUCCESS);
}

void
main(int argc, char* argv[])
{
	int full_upper, file = 0, i;
	for (i=0; i<argc; i++) {
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
