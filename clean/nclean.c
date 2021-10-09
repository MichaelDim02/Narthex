/*
 *    nclean - Narthex cleaner 
 *
 *  By Michael Constantine Dimopoulos
 *  https://mcdim.xyz	<mk@mcdim.xyz>
 *  License: GNU GPL v3
 *
 *  nclean will iterate over stdin and
 *  print only the lines have met your
 *  set criteria.
 *  For example, it can print only
 *  lines that have both a number and
 *  a special character that are more
 *  than six chars in length.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define VERSION "v1.0"
#define BUFFER_SIZE 256

static void
usage(char *exename)
{
	fprintf(stderr, "Usage:	cat [FILENAME]"
		"| %s [-c] [-n] [-s] [-l] 10\n",
		exename);
}

static void
help(char *exename)
{
	printf( "nclean - Narthex cleaner %s\n"
		"By Michael C. Dim. <mk@mcdim.xyz>\n\n"

		"-c  Must have capital letters\n"
		"-n  Must have numbers\n"
		"-s  Must have symbols\n"
		"-l  Must have min length specified\n"
		"-h  Print this panel & exit\n"
		"-v  Print current version & exit\n\n"

		"Usage:	cat [FILENAME] | %s [-c] [-n] [-s] [-l] 10\n",
		VERSION, exename);
	exit(EXIT_SUCCESS);
}

static void
die(char * str)
{
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

static int
case_check(char * str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (isupper(str[i]) != 0)
			return 1;
	}
	return 0;
}

static int
numb_check(char * str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (isdigit(str[i]) != 0)
			return 1;
	}
	return 0;
}

static int
symb_check(char * str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if(str[i] == '!' || str[i] == '@' || str[i] == '#'
		|| str[i] == '$' || str[i] == '%' || str[i] == '^'
		|| str[i] == '&' || str[i] == '*' || str[i] == '('
		|| str[i] == ')' || str[i] == '-' || str[i] == '{'
		|| str[i] == '}' || str[i] == '[' || str[i] == ']'
		|| str[i] == ':' || str[i] == ';' || str[i] == '"'
		|| str[i] == '\''|| str[i] == '<' || str[i] == '>'
		|| str[i] == '.' || str[i] == '/' || str[i] == '?'
		|| str[i] == '~' || str[i] == '`' )
			return 1;
	}
	return 0;
}

static int
len_check(char * str, int len)
{
	return strlen(str) >= len ? 1 : 0; 
}

static void
clean(FILE *f, int c, int n, int s, int l)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), f) != NULL) {
		strtok(buffer, "\n");
		int fc = 1, fn = 1, fs = 1, fl = 1;

		if (c == 1) fc = case_check(buffer);
		if (n == 1) fn = numb_check(buffer);
		if (s == 1) fs = symb_check(buffer);
		if (l > 0)  fl = len_check(buffer, l);

		/* for troubleshooting:
		 * printf("fc:%d\nfn:%d\nfs:%d\nfl:%d\n",fc, fn, fs, fl);
		 * */
		if (fc==1 && fn==1 && fs==1 && fl==1) {
			printf("%s\n",buffer);
		}
	}
}

void
main(int argc, char * argv[])
{
	int c1=0, n=0, s=0, l=0, lvalue=0;
	char *cvalue = NULL;
	int index;
	int c;
	extern char *optarg;
	int optind = 0;


	while ( (c = getopt(argc, argv, "cnsvhl:")) != -1 ) {
		switch (c) {
			case 'v':
				die(VERSION);
			case 'h':
				help(argv[0]);
			case 'c':
				c1=1;
				break;
			case 'n':
				n=1;
				break;
			case 's':
				s=1;
				break;
			case 'l':
				l=1;
				lvalue=atoi(optarg);
				break;
			case '?':
				usage(argv[0]);
				exit(EXIT_FAILURE);
				break;
		}
	}

	if (c1 == 1 || n == 1 || s == 1 || l == 1) {
		clean(stdin, c1, n, s, lvalue);
	} else {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
