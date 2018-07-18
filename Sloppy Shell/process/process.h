#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../pipes/pipes.h"
#include "../linkedList/linkedList.h"
#include "../history/history.h"
#include "../alias/alias.h"
#include "../utils/fileUtil.h"

void processCommand(char ** theArgs, int numArgs, LinkedList * histList, LinkedList * aliasList, int * histCount, int * histSize);
void execCommand(char * s);
void forkIt(char ** argv);
void changeDirectory(char ** argv);
void redirect(char * command, char * output);

#endif
