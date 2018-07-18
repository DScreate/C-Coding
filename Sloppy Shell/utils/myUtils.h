/**
 * @file myUtils.h
 * @author Stu Steiner
 * @date 29 Dec 2015
 * @brief The basic myUtils.h that will be used during the quarter
 *
 * The myUtils.h defines the basic menu and strip functions that will be
 * required during the course of the quarter.
 */
#ifndef MYUTILS_H
#define MYUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


/**
 * @brief Creates a string by putting the various arguments together in an array of char *
 *
 *
 * @note The carriage return is removed from the input buffer
 *
 * @return char * - Representing string created from the various args
 */
char * makeString(char ** theArgs, int start, int numArgs);

/**
 * @brief Strinps the \r and \n from the string if they exist.
 *
 * Walks through the character array one character at a time
 * if a '\r' or '\n' are encountered it is changed to a '\0'
 * entered by the user is within range.
 *
 * @param The character array potentially containing a '\r' and/or '\n'
 *
 * @warning - The passed in pointer is checked - exit(-99) if NULL
 */
void strip(char *array);

void stripChar(char *line, int target);
#endif
