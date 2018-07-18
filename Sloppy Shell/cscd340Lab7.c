/*
 * cscd340Lab7.c
 *
 *      Author: Derek Sams
 */

#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./utils/fileUtil.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./alias/alias.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./history/history.h"



int main()
{

	int histCount;
	int histSize;
	LinkedList * histList  = linkedList();
	LinkedList * aliasList = linkedList();

	FILE * fin = openUSHRC(&histCount, &histSize);
	FILE * histFin = openUSHRC_hist(histList);
	execUSHRC(fin, aliasList);

	char * argv[50];
	char s[MAX];
	int argc;


	printf("command?: ");
	fgets(s, MAX, stdin);
	strip(s);

	while(strcmp(s, "exit") != 0) {
		//printf("Test point 2\n");

		// First, need to check to see if we have any readable input
		if((argv[0] = strtok(s, " \t\n")) == NULL)
			printf("Invalid Input\n");
		else {
		// We know we have at least 1 token
			argc = 1;

			// A tiny version of the more potent makeArgs function
			// in order to not bother with cleaning memory and the such
			// I am electing to just use this simple loop instead of the full function
			while((argv[argc] = strtok(NULL, " \t\n")) != NULL) {
				argc++;
			}

			processCommand(argv, argc, histList, aliasList, &histCount, &histSize);
		}

		//clean(argc, argv);
		//argc = 0;

		printf("command?: ");
		fgets(s, MAX, stdin);
		strip(s);

	}// end while

	writeUSHRC_Hist(histFin, histList, histSize);


	clearList(histList, cleanTypeHistory);
	free(histList);
	clearList(aliasList, cleanTypeAlias);
	free(aliasList);
	fclose(fin);
	fclose(histFin);
	printf("Goodbye!\n");

	return 0;

}// end main

