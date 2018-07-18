/*
 * fileUtil.c
 *
 *  Created on: Apr 24, 2017
 *      Author: derek
 */


#include "../utils/fileUtil.h"


FILE * openUSHRC(int * histCount, int * histSize) {
	FILE * fin = fopen(".ushrc", "r");
	char * temp;
	//char * saveptr;

	if(fin == NULL) {
		printf(".ushrc file doesn't exit, creating and setting default values...\n");
		fin = fopen(".ushrc", "wb");
		fprintf(fin, "HISTCOUNT=100\n");
		fprintf(fin, "HISTSIZE=1000\n");
		*histCount = 100;
		*histSize = 1000;

	} else {
		printf("ushrc found, now checking for data\n");
		temp = calloc(MAX, sizeof(char));
		fgets(temp,MAX,fin);
		strip(temp);
		strtok(temp,"=");

		//strtok_r(temp,"=",&saveptr);

		if(strcmp("HISTCOUNT", temp) == 0) {
			*histCount = atoi(strtok(NULL, "="));


			fgets(temp,MAX,fin);
			strip(temp);
			strtok(temp,"=");
			*histSize = atoi(strtok(NULL, "="));
		} else {
			*histSize = atoi(strtok(NULL, "="));

			fgets(temp,MAX,fin);
			strip(temp);
			strtok(temp,"=");
			*histCount = atoi(strtok(NULL, "="));
		}

		printf("histCount is %d\n", *histCount);
		printf("histSize is %d\n", *histSize);
		rewind(fin);

		free(temp);
	}

	return fin;
}

void writeUSHRC_Hist(FILE * histFin,LinkedList * histList, int histSize) {
	char buffer[MAX];
	char * argv[50];
	int argc;
	int index = 0;
	//printf("===NOW IN WRITING MODE FOR HIST FILE===\n");
	rewind(histFin);

	if(histFin == NULL) {
		printf("===Error point! I will handle it this time===\n===but please have a proper file in the future!\n===");
		printf(".ushrc_history file doesn't exit, I will make one\n");
		histFin = fopen(".ushrc_history", "wb");

	}


	if(histList->size > histSize) {
		//printf("Size is large!\n");
		//printf("histSize is %d\n", histSize);
		//printf("theList size is %d\n", histList->size);
		index = histList->size - histSize;
	}

	while(index < histList->size) {
		Node * cur = getIndex(index, histList);
		History * theHist = cur->data;
		char * temp = theHist->command;
		fprintf(histFin, "%s\n", temp);
		index++;
	}
}


FILE * openUSHRC_hist(LinkedList * histList) {
	FILE * fin = fopen(".ushrc_history", "r+");
	char buffer[MAX];
	char * argv[50];
	int argc;

	if(fin == NULL) {
		printf(".ushrc_history file doesn't exit, I will make one\n");
		fin = fopen(".ushrc_history", "wb");

	} else {
		printf(".ushrc_history has been found, I will now read through it\n");

		while(fgets(buffer, MAX, fin))
		{
			if((argv[0] = strtok(buffer, " \t\n")) == NULL)
			{
				printf("Invalid Input\n");
			}
			else
			{
				argc = 1;

				while((argv[argc] = strtok(NULL, " \t\n")) != NULL)
				{
					argc++;
				}


				char * temp = makeString(argv, 0, argc);

				Node * nn = buildNode_Type(buildTypeHistoryString(temp));
				addLast(histList, nn);
				free(temp);

			}
		}
	}

	return fin;
}


void execUSHRC(FILE * fin, LinkedList * aliasList) {
	char buffer[MAX];
	char * argv[50];
	int argc;

	while(fgets(buffer, MAX, fin)) {
		if((argv[0] = strtok(buffer, " \t\n")) == NULL)
		{
			printf("Invalid Input\n");
		} else
		{
				argc = 1;


			while((argv[argc] = strtok(NULL, " \t\n")) != NULL)
			{
				argc++;
			}

			if(strcasecmp(argv[0], "alias") == 0) {

				if(argv[1] == NULL) {
				printList(aliasList, printTypeAlias);

				} else if(strstr(argv[1], "=") != NULL) {

				char * temp = makeString(argv, 1, argc);
				Node * nn = buildNode_Type(buildTypeAliasString(temp));
				addLast(aliasList, nn);
				free(temp);

				} else if(argv[2] == NULL) {
					printf("Invalid alias command\n");
					printf("You had theArgs[1] as %s\n", argv[1]);

				} else {



					char * temp = makeString(argv, 1, argc);
					Node * nn = buildNode_Type(buildTypeAliasString(temp));
					addLast(aliasList, nn);
					free(temp);

				}


			}
			if(strstr(argv[0], "PATH") !=NULL) {
				//printf("Path found\n");
				//printf("argv[0] is %s\n", argv[0]);

				char * ptr = strstr(argv[0], "/");
				//printf("ptr is %s\n", ptr);

				char  * pathString = malloc((strlen(getenv("PATH")) + strlen(ptr))+2);
				strcpy(pathString, getenv("PATH"));
				strcat(pathString, ":");
				strcat(pathString, ptr);
				setenv("PATH", pathString, 1);
				printf("PATH is now %s", getenv("PATH"));

				free(pathString);
			}
		}
	}

}

FILE * openInputFile_Prompt()
{
   char temp[100];
   printf("Please enter the name of the input file ");
   fgets(temp, 100, stdin);
   strip(temp);
   FILE * fin = fopen(temp, "r");

   while(fin == NULL)
   {
      printf("Please enter the name of the input file ");
      fgets(temp, 100, stdin);
      strip(temp);
      fin = fopen(temp, "r");
   }// end while

   return fin;
}// end openInputFile_Prompt

FILE * openInputFileType_Prompt(char * type)
{
   char temp[100];
   printf("Please enter the name of the %s input file ", type);
   fgets(temp, 100, stdin);
   strip(temp);
   FILE * fin = fopen(temp, "r");

   while(fin == NULL)
   {
      printf("Please enter the name of the input file ");
      fgets(temp, 100, stdin);
      strip(temp);
      fin = fopen(temp, "r");
   }// end while

   return fin;
}// end openInputFileType_Prompt


int countRecords(FILE * fin, int linesPerRecord)
{
	if(fin == NULL || linesPerRecord <= 0)
	{
		perror("fin is null or linesPerRecord<=0");
		exit(-99);
	}// end if

   int count = 0;
   char temp[MAX];
   fgets(temp, MAX, fin);
   while(!feof(fin))
   {
      count ++;
      fgets(temp, MAX, fin);

   }// end while

   if(count == 0)
   {
   		perror("count is 0");
   		exit(-99);
   }// end if

   rewind(fin);
   return count / linesPerRecord;
}// end count records


int readTotal(FILE * fin)
{
	if(fin == NULL)
	{
		perror("fin is null");
		exit(-99);
	}// end if

	int total;
	char temp[MAX];
	fgets(temp, MAX, fin);

	total = atoi(temp);
	if(total <= 0)
	{
		perror("total is <= 0");
		exit(-99);
	}// end if

	return total;

}// end readTotal


