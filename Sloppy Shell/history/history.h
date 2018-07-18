/*
 * history.h
 *
 *  Created on: Apr 23, 2017
 *      Author: magnus
 */

#ifndef HISTORY_HISTORY_H_
#define HISTORY_HISTORY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../linkedList/linkedList.h"
#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"


struct history
{
   char * command;
   //char ** tokCommand;
   //int num;
};

typedef struct history History;


/**
 * @brief Cleans up all dynamically allocated memory
 *
 *
 * Each pointer in the specific data type is set to NULL after it has been freed.
 *
 * @param passedIn - The void * passed in representing the specific history
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void cleanTypeHistory(void * ptr);


/**
 * @brief Builds and returns a single history.
 *
 * Reads the initial data from the file and then builds
 * an object of type history.
 *
 * @note The carriage return will be removed when reading from the file
 *
 * @param fin - The FILE * representing the open file
 * @return void * - Representing a history object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeHistory(FILE * fin);

/**
 * @brief Builds and returns a single history.
 *
 * Reads the initial data from the file and then builds
 * an object of type history.
 *
 * @note The carriage return will be removed when reading from the file
 *
 * @param input - The char * representing the passed string
 * @return void * - Representing a history object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeHistoryString(char * input);


/**
 * @brief Prints the specific history.
 *
 *
 * @param passedIn - The void * passed in representing a specific history
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void printTypeHistory(void * passedIn);


/**
 * @brief Builds and returns history struct.
 *
 * Reads the initial data from the keyboard by prompting the user.
 * A history object is constructed.
 *
 * @note The carriage return will be removed when reading from the keyboard
 *
 * @param fin - The FILE * representing stdin
 * @return void * - Representing a history object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeHistory_Prompt(FILE * fin);


/**
 * @brief Compares two objects of type history.
 *
 * historys are compared based on title and if the title are the same then totalActors
 *
 * @note The passed in items will need to be cast to the appropriate history type.
 *
 * @param p1 - The void * representing an object of type history
 * @param p2 - The void * representing an object of type history
 * @return int - Representing order < 0 indicates p1 is less than p2,
 * > 0 indicates p1 is greater than p2 and == 0 indicates p1 == p2 for contents
 *
 * @warning - The passed in void * p1 is checked - exit(-99) if NULL
 * @warning - The passed in void * p2 is checked - exit(-99) if NULL
 */
int compareHistory(const void * p1, const void * p2);

#endif /* HISTORY_HISTORY_H_ */
