#include "myUtils.h"

void strip(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int len = strlen(array), x = 0;
   
	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';

	  x++;

	}// end while

}// end strip

void stripChar(char *line, int target)
{
	if(line == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int len = strlen(line);
	char str[len];
	strcpy(str, line);
	//printf("First letter of line is %d\n", line[0]);

	//printf("len is %d\n", len);
	if(line[0] == target) {
		printf("Target found\n");
		memmove(line, line+1, len -2);
		line[len -2] = '\0';
	}

	//printf("should now be %s\n", line);
   
}// end strip




char * makeString(char ** theArgs, int start, int numArgs) {
	int x;
	char * temp;
	char * saveptr;

	temp = calloc(numArgs+1, sizeof(char *));
	strcpy(temp, theArgs[start]);

	for(x=start+1;x<numArgs;x++) {;
		strncat(temp, " ", sizeof(" "));
		strncat(temp, theArgs[x], strlen(theArgs[x]));
	}

	//printf("End makeString, returning %s\n", temp);

	return temp;
}

