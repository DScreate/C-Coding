/*
 * alias.c
 *
 *  Created on: Apr 24, 2017
 *      Author: derek
 */

#include "../alias/alias.h"


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
void cleanTypeAlias(void * ptr) {
	if(ptr == NULL) {
		perror("Null pointer");
		exit(-99);
	}

	Alias * al = ptr;
	free(al->command);
	al->command = NULL;

	free(al->commandAlias);
	al->commandAlias = NULL;

	free(al);

	ptr = NULL;
}


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
void * buildTypeAlias(FILE * fin) {
	if(fin == NULL) {
		perror("Null fin");
		exit(-99);
	}

	char temp[MAX];
	fgets(temp, MAX, fin);
	strip(temp);
	Alias * al = calloc(1, sizeof(Alias));
	al->command = (char *)calloc(strlen(temp)+1, sizeof(char));
	strcpy(al->command, temp);

	return al;
}

/**
 * @brief Builds and returns a single alias.
 *
 * Reads the initial data from the file and then builds
 * an object of type alias.
 *
 *
 * @return void * - Representing a alias object
 *
 */
void * buildTypeAliasString(char * input) {
	if(input == NULL) {
		perror("Null input");
		exit(-99);
	}

	char * cmd;
	char * alias;

	cmd = strtok(input, "=");

	if(isspace(cmd[strlen(cmd)-1])) {
		//printf("Space found\n" );
		memmove(cmd, cmd, strlen(cmd) -1);
		cmd[strlen(cmd) -1] = '\0';
	}

	alias = strtok(NULL, "=");

	strip(alias);
	if(isspace(alias[0])) {
		memmove(alias, alias+1, strlen(alias) -1);
		alias[strlen(alias) -1] = '\0';
	}


	stripChar(alias, 34);
	stripChar(alias, 39);


	Alias * al = calloc(1, sizeof(Alias));
	al->command = (char *)calloc(strlen(cmd)+1, sizeof(char));
	strcpy(al->command, cmd);

	al->commandAlias = (char *)calloc(strlen(alias)+1, sizeof(char));
	strcpy(al->commandAlias, alias);


	printf("\n---%s is aliased as %s---\n", cmd, alias);
	return al;
}

/**
 * @brief Prints the specific alias.
 *
 *
 * @param passedIn - The void * passed in representing a specific alias
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void printTypeAlias(void * passedIn) {
	if(passedIn == NULL) {
		perror("Null pointer");
		exit(-99);
	}

	Alias * al = (Alias *)passedIn;


	printf("%s aliased as %s", al->commandAlias, al->command);
}


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
void * buildTypeAlias_Prompt(FILE * fin) {
	return buildTypeAlias(fin);
}


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
int compareAlias(const void * p1, const void * p2) {
	if(p1 == NULL || p2 == NULL) {
		perror("NULL Pointer");
		exit(-99);
	}

	Alias * a1 = (Alias *)p1;
	Alias * a2 = (Alias *)p2;

	return strcmp(a1->command, a2->command);
}
