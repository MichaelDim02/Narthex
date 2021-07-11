#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char * argv[])
{
	int min = 1;
	int max;
	if (argc > 1) {
		if (argc == 2) {
			if (strcmp(argv[1], "-h") == 0)
				printf("Help");
			else if (strcmp(argv[1], "-v") ==0)
				printf("Version");
			else
				max = atoi(argv[1]);
		}
		if (argc == 3) {
			int max = atoi(argv[1]);
			char * filename = argv[2];
		} else if (argc == 4) {
			min = atoi(argv[1]);
			int max = atoi(argv[2]);
			char * filename = argv[3];
		}
	} else {
		printf( "Narthex incrementor\n"
			"By mk@mcdim.xyz\n\n"

			"Usage:	nicre [MIN] [MAX] [FILENAME]\n"
			" 	nicre [MAX] [FILENAME]\n"
			"	nicre [MIN] [MAX]\n"
			"	nicre [MAX]\n");
	}
}
