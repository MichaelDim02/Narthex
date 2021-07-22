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
	exit(0);
}

void help(char * exename)
{
	printf( "Nhance - Narthex enhancer %s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-f  Append full capitalization\n"
		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"
		"Usage:	cat [FILENAME] | %s [OPTIONS]\n",
		"	%s [OPTIONS] [FILENAME]\n",
		VERSION, exename);
	exit(0);
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
