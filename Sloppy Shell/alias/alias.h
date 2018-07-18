/*
 * alias.h
 *
 *  Created on: Apr 23, 2017
 *      Author: magnus
 */

#ifndef ALIAS_ALIAS_H_
#define ALIAS_ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../linkedList/linkedList.h"
#include "../utils/myUtils.h"


struct alias
{
   char * command;
   char * commandAlias;
   //char ** tokCommand;
   //int * num;
};

typedef struct alias Alias;


/**
 * @brief Cleans up all dynamically allocated memory
 *
 *
 * Each pointer in the specific data type is set to NULL after it has been freed.
 *
 * @param passedIn - The void * passed in representing the specific alias
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void cleanTypeAlias(void * ptr);


/**
 * @brief Builds and returns a single alias.
 *
 * Reads the initial data from the file and then builds
 * an object of type alias.
 *
 * @note The carriage return will be removed when reading from the file
 *
 * @param fin - The FILE * representing the open file
 * @return void * - Representing a alias object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeAlias(FILE * fin);


/**
 * @brief Prints the specific alias.
 *
 *
 * @param passedIn - The void * passed in representing a specific alias
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void printTypeAlias(void * passedIn);


/**
 * @brief Builds and returns alias struct.
 *
 * Reads the initial data from the keyboard by prompting the user.
 * A alias object is constructed.
 *
 * @note The carriage return will be removed when reading from the keyboard
 *
 * @param fin - The FILE * representing stdin
 * @return void * - Representing a alias object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeAlias_Prompt(FILE * fin);


/**
 * @brief Compares two objects of type alias.
 *
 * aliass are compared based on title and if the title are the same then totalActors
 *
 * @note The passed in items will need to be cast to the appropriate alias type.
 *
 * @param p1 - The void * representing an object of type alias
 * @param p2 - The void * representing an object of type alias
 * @return int - Representing order < 0 indicates p1 is less than p2,
 * > 0 indicates p1 is greater than p2 and == 0 indicates p1 == p2 for contents
 *
 * @warning - The passed in void * p1 is checked - exit(-99) if NULL
 * @warning - The passed in void * p2 is checked - exit(-99) if NULL
 */
int compareAlias(const void * p1, const void * p2);


#endif /* ALIAS_ALIAS_H_ */
