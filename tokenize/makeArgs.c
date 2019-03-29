#include "makeArgs.h"

void clean(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
	{
		free(argv[x]);
		argv[x] = NULL;
	}// end for

	free(argv);
	argv = NULL;
}// end clean

void printargs(char **argv)
{
	int x = 0;
	/*
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);*/
	while (argv[x] != NULL) {
		fprintf(stderr, "'%s' ", argv[x]);
		x++;
	}
	fprintf(stderr, "\n");

}// end printargs

int makeargs(char *s, char *** argv)
{
	//printf("passed in string is %s\n", s);
	char copy[strlen(s) + 1];
	strcpy(copy, s);
	//printf("passed in string is now %s\n", s);

	int count = 0;
	char * saveptr = NULL;

	char * token = strtok_r(copy, " ", &saveptr);

	while(token != NULL)
	{
		count ++;
		token = strtok_r(NULL, " ", &saveptr);
		//printf("got token %s\n", token);
	}

	if(count == 0)
		return -1;

	(*argv) = (char **)calloc(count + 1, sizeof(char *));
	//printf("Count: %d\n", count);
	strcpy(copy, s);
	token = strtok_r(copy, " ", &saveptr);
	(*argv)[0] = (char *)calloc(strlen(token) + 1, sizeof(char));
	strcpy((*argv)[0], token);

	int x;
	for(x = 1; x < count; x++)
	{
		token = strtok_r(NULL, " ", &saveptr);
		(*argv)[x] = (char *)calloc(strlen(token) + 1, sizeof(char));
		strcpy((*argv)[x], token);
	}// end for	
	//free(copy);
   	return count;

}// end makeArgs
