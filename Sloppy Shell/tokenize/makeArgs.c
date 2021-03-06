#include "makeArgs.h"

void clean(int argc, char **argv)
{
  int x;
  for(x = 0; x < argc; x++) {
    free(argv[x]);
  }

  free(argv);



}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{

	int count = 0;
	char * temp;
	char copy[MAX];
	char * saveptr;
	int x;
	char delim[] = "\t\n ";

	strcpy(copy, s);

	temp = strtok_r(s, delim, &saveptr);
	while(temp != NULL) {
		count++;
		temp = strtok_r(NULL, delim, &saveptr);
	}

	(*argv) = (char**)calloc(count+1, sizeof(char *));
	temp = strtok_r(copy, delim, &saveptr);

	(*argv)[0] = (char *)calloc(strlen(temp)+1, sizeof(temp));
	strcpy((*argv)[0], temp);

	for(x=1;x<count;x++) {;
		temp = strtok_r(NULL, delim, &saveptr);

		(*argv)[x] = (char *)(calloc(strlen(temp)+1, sizeof(char)));
		strcpy((*argv)[x], temp);
	}

	if(count>0)
		return count;
	else
		return 1;

}// end makeArgs
