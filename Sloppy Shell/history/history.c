/*
 * history.c
 *
 *  Created on: Apr 24, 2017
 *      Author: derek
 */

#include "../history/history.h"

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
void cleanTypeHistory(void * ptr) {
	if(ptr == NULL) {
		perror("Null pointer");
		exit(-99);
	}

	History * hist = ptr;
	free(hist->command);
	hist->command = NULL;

	//free(hist->tokCommand);

	//hist->num = 0;

	free(hist);

	ptr = NULL;
}


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
void * buildTypeHistory(FILE * fin) {
	if(fin == NULL) {
		perror("Null fin");
		exit(-99);
	}

	char temp[MAX];
	fgets(temp, MAX, fin);
	strip(temp);
	History * hist = calloc(1, sizeof(History));
	hist->command = (char *)calloc(strlen(temp)+1, sizeof(char));
	strcpy(hist->command, temp);
	hist->command[strlen(hist->command)-1] = '\0';

	//hist->num = makeargs(temp, &(hist->tokCommand));

	return hist;
}


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
void * buildTypeHistoryString(char * input) {
	if(input == NULL) {
		perror("Null input");
		exit(-99);
	}

	strip(input);
	History * hist = calloc(1, sizeof(History));
	hist->command = (char *)calloc(strlen(input)+1, sizeof(char));
	strcpy(hist->command, input);

	//hist->num = makeargs(input, &(hist->tokCommand));

	return hist;
}

/**
 * @brief Prints the specific history.
 *
 *
 * @param passedIn - The void * passed in representing a specific history
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void printTypeHistory(void * passedIn) {
	if(passedIn == NULL) {
		perror("Null pointer");
		exit(-99);
	}

	History * hist = (History *)passedIn;

	printf("%s", hist->command);
}


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
void * buildTypeHistory_Prompt(FILE * fin) {
	if(fin == NULL) {
		perror("Null fin");
		exit(-99);
	}

	return buildTypeHistory(fin);
}

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
int compareHistory(const void * p1, const void * p2) {
	if(p1 == NULL || p2 == NULL) {
		perror("NULL Pointer");
		exit(-99);
	}

	History * h1 = (History *)p1;
	History * h2 = (History *)p2;

	return strcmp(h1->command, h2->command);
}
