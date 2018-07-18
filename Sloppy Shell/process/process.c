#include "process.h"

void processCommand(char ** theArgs, int numArgs, LinkedList * histList, LinkedList * aliasList, int * histCount, int * histSize) {
	if(theArgs == NULL || histList == NULL || aliasList == NULL) {
		perror("NULL parameter in processCommand");
		exit(-99);
	}
	char * s;
	char * nextArgs[numArgs];

	int index;

	int x;
	int y = 0;
	int redirectFound = 0;


	//printf("\n===VARIABLE CHECK===\n===HISCOUNT = %d===\n===HISTSIZE = %d===\n", *histCount, *histSize);


	while(y < numArgs && redirectFound == 0) {
		//printf("checking for redirect at %d, it is %s\n", y, theArgs[y]);
		if((strcmp(theArgs[y], ">") == 0) || (strcmp(theArgs[y], "<") == 0) || (strcmp(theArgs[y], "&") == 0)) {
			//printf("Redirect found\n");
		}
		if((strcmp(theArgs[y], ">") == 0)) {
			//printf("> found\n");
			if(theArgs[y+1] == NULL) {
					printf("Not enough arguments\n");
			} else {
				char * commandString = makeString(theArgs, 0, y);
				//printf("commandString made, I will be passing %s\n", commandString);
				char * string = makeString(theArgs, y+1, numArgs);
				//printf("String made, I will be passing %s\n", string);
				redirect(commandString, string);
				free(commandString);
				free(string);
			}
			redirectFound = 1;;

		}


		nextArgs[y] = theArgs[y];
		y++;

	}

	if(redirectFound != 1) {

		if(strcmp(theArgs[0], "!!") == 0) {
			if(histList->size > 0 ) {
					Node * node = getLast(histList);
					History * last = (History *)node->data;
					execCommand(last->command);
			} else
				printf("No history!\n");

		} else if(((strstr(theArgs[0], "!"))) != NULL) {
					char * temp = strtok(theArgs[0], "!");
					int num = atoi(temp);
					if(histList->size > 0 ) {
							Node * node = getIndex(num, histList);
							History * last = (History *)node->data;
							execCommand(last->command);
					} else
						printf("No history!");
		} else {

			if(strcasecmp(theArgs[0], "alias") == 0) {
				if(theArgs[1] == NULL) {
					printList(aliasList, printTypeAlias);

				} else if(strstr(theArgs[1], "=") != NULL) {

					char * temp = makeString(theArgs, 1, numArgs);
					Node * nn = buildNode_Type(buildTypeAliasString(temp));
					addLast(aliasList, nn);
					free(temp);
				} else if(theArgs[2] == NULL) {
					printf("Invalid alias command\n");
					printf("You had theArgs[1] as %s\n", theArgs[1]);

				} else {



					char * temp = makeString(theArgs, 1, numArgs);
					Node * nn = buildNode_Type(buildTypeAliasString(temp));
					addLast(aliasList, nn);
					free(temp);

				}


			}

			char * temp = makeString(theArgs, 0, numArgs);
			char * temp2 = calloc(strlen(temp)+1, sizeof(char));
			strcpy(temp2, temp);

			if(strcasecmp(theArgs[0], "history") == 0) {

				   if(histList == NULL || histList->size == 0) {
					   printf("Empty List\n");
				   } else {
					   Node * cur;
					   int ix;
					   if(histList->size > *histCount) {
						   ix = histList->size - *histCount;
						   printf("size is %d\nix is %d\n", histList->size, ix);
						   cur = getIndex(ix, histList);
					   } else {
						   ix = 0;
						   cur = histList->head->next;
					   }
					   while(cur != NULL  && ix < (*histCount) + ix) {
						   printf("%d ", ix);
						   printTypeHistory(cur->data);
						   printf("\n");
						   cur = cur->next;
						   ix++;
					   }
				   }

			} else {
				int processed = 0;

				// Check to see if the command is an existing alias
				Node * cur = aliasList->head->next;
				while(cur != NULL) {
					Alias * alias = cur->data;
					if(strcasecmp(alias->command, temp) == 0) {
						char * theAlias = calloc(strlen(alias->commandAlias)+1, sizeof(char));
						strcpy(theAlias, alias->commandAlias);
						execCommand(theAlias);
						free(theAlias);
						processed = 1;
						break;
					}

					cur = cur->next;
				}
				if(strcasecmp(theArgs[0], "alias") != 0 && processed != 1)
					execCommand(temp);

			}


			if(histList->size > 0 ) {
			Node * node = getLast(histList);
				History * last = (History *)node->data;

				if(strcasecmp(last->command, temp2) != 0) {
					Node * nn;
					nn = buildNode_Type(buildTypeHistoryString(temp2));
					if(histList->size >= histSize)
						removeFirst(histList, cleanTypeHistory);
					addLast(histList, nn);
				}

			} else {
				Node * nn;
				nn = buildNode_Type(buildTypeHistoryString(temp2));

				addLast(histList, nn);
			}


			free(temp);
			free(temp2);

		}
	}
}


void changeDirectory(char ** argv) {
	//printf("CD found!\n");
	// If just "cd" is inputed then change current directory to HOME
	if(argv[1] == NULL) {
		chdir(getenv("HOME"));
	}
	// Otherwise we use chdir method to attempt to change the directory
	// Note: this returns a -1 if the method fails, allowing us to check
	// to see if directory exists. THANK YOU MAN PAGES
	else {
		int res;
		res = chdir(argv[1]);
		if(res == 0) {
			printf("Directory changed\n");
		}

		else {
			printf("Could not change directory, res is %d\n", res);
		}
	}

}


void execCommand(char * s) {
	char ** argv;
	char ** prePipe = NULL, ** postPipe = NULL;
	int preCount = 0, postCount = 0;
	int argc, pipeCount;

	pipeCount = containsPipe(s);
	if(pipeCount > 0)
	{

		prePipe = parsePrePipe(s, &preCount);
		postPipe = parsePostPipe(s, &postCount);
		pipeIt(prePipe, postPipe);
		clean(preCount, prePipe);
		clean(postCount, postPipe);

	}// end if pipeCount

	else
	{
		argc = makeargs(s, &argv);
		if(strcasecmp(argv[0], "cd") == 0) {
			changeDirectory(argv);
		} else if(argc != -1)
			forkIt(argv);

		clean(argc, argv);
		argv = NULL;
	}

// end non-cd else block
}

void forkIt(char ** argv)
{
	int status;
	pid_t pid;


	pid = fork();

	if(pid != 0 )
	{
		// parent
		waitpid(pid, &status, 0);
	}
	else
	{
		// child


		execvp(argv[0], argv);


		printf("Unknown command\n");
		exit(0);

	}

}

void redirect(char * command, char * output) {
	int fd;
	pid_t pid;
	int status;


	pid = fork();

	if(pid != 0 )
	{
		// parent
		//printf("Parent Starting\n");
		waitpid(pid, &status, 0);
		//printf("Parent Ending\n");
	}
	else
	{
		// child

		fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execCommand(command);

		exit(0);

	}

}
