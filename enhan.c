#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


char version[7] = "v1.0";

char
save_stdin(FILE *f)
{
	FILE *fw = fopen("tempfile-61436134.txt", "w");
	char buffer[256];
	while(fgets(buffer, sizeof(buffer), f) != NULL)  {
		fprintf(fw, "%s", buffer);
	}
	fclose(fw);
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
	char buffer[256];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		printf("%s",buffer);
	}
}

void
enhance(FILE *f, int full_upper)
{
	char buffer[256];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		if (isalpha(buffer[0])) {
			if (full_upper ==0) {
				buffer[0] = toupper(buffer[0]);	
				printf("%s",buffer);
			} else {
				cap(buffer);
				printf("%s",buffer);	
			}
		}

	}
}

void
main(int argc, char* argv[])
{
	int full_upper, file = 0;
	int i;
	for (i=0; i<argc; i++) {
		if (strcmp(argv[i],"-f")==0) {
			full_upper = 1;
		} else if (strcmp(argv[i],"-v")==0){
			printf("%s\n", version); 
			exit(0);
		} else if (strcmp(argv[i],"-h")==0){
			printf("blank\n");
			exit(0);
		} else {
			file = i;
		}
	}

	if (file != 0) {
		FILE *f = fopen(argv[file], "r");
		if (f) {
			save_stdin(f);
			fclose(f);
		} else {
			fprintf(stderr, "enhan: %s\n", strerror(errno));
		}
	} else {
		save_stdin(stdin);
	}

	FILE *fr = fopen("tempfile-61436134.txt", "r");
	print_only(fr);
	rewind(fr);
	enhance(fr,0);
	if (full_upper == 1) {
		rewind(fr);
		enhance(fr,1);
	}
	fclose(fr);
	remove("tempfile-61436134.txt");

	exit(0);
}
