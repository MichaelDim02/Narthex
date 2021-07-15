#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 *    Nenhancer - Narthex enhancer
 *
 *  By Michael Constantine Dimopoulos
 *  https://mcdim.xyz	<mk@mcdim.xyz>
 *  License: GNU GPL v3
 *
 */

#define VERSION "1.0"
#define BUFFER_SIZE 256

static void
cap(char string[])
{  
	int i;
        /* You want to get the length of the whole string. */
	int x = strlen(string); 
	for (i=0; i<x-1; i++){
		if (isalpha(string[i])){ 
			string[i]= toupper(string[i]);
		}
	}
}

static inline void
print_only(FILE *f)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s",buffer);
	}
}

static void
enhance(FILE *f, int full_upper)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		if (isalpha(buffer[0])) {

			if (full_upper ==0) {
				buffer[0] = toupper(buffer[0]);	
				printf("%s",buffer);
			} else {
				cap(buffer);
				printf("%s", buffer);	
			}
		}
	}
}

void
main(int argc, char* argv[])
{
	if (argc == 1) {
		enhance(stdin,0);
	} else {
		FILE *f = fopen(argv[1], "r");
		if (f) {
			print_only(f);
			rewind(f);
			enhance(f,0);
			rewind(f);
			enhance(f,1);
			fclose(f);
		} else {
			fprintf(stderr, "error opening %s\n", argv[1]);
			exit(1);
		}	
	} 
	exit(0);
}
