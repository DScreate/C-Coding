#include "linkedList.h"

/**
 * @brief The so called "constructor" for the linked list
 *
 * The linked list constructor builds a non circular linked list that
 * contains a dummy head not.  This is meant to be similar to a Java
 * linked list constructor.
 *
 * @return LinkedList * - The linked list pointer that contains a dummy head node but is not circular.
 */
LinkedList * linkedList() {
   LinkedList * myList = (LinkedList *)calloc(1, sizeof(LinkedList));
   myList->head = (Node *)calloc(1, sizeof(Node));
   return myList;
}


/**
 * @brief The add last function for the linked list
 *
 * Appends the specified node to the end of this list
 *
 * @param theList - The specified linked list
 * @param nn - The node to be added
 *
 * @warning - The passed in LinkedList * theList is checked - exit(-99) if NULL
 * @warning - The passed in Node * nn is checked - exit(-99) if NULL
 */
void addLast(LinkedList * theList, Node * nn) {
   if(theList == NULL) {
      perror("Null list\n");
      exit(-99);
   }
   if(nn == NULL) {
      perror("Null new node\n");
      exit(-99);
   }
   
   Node * cur = theList->head;
   while(cur->next != NULL) {
      cur = cur->next;
   }
   

   cur->next = nn;
   nn->prev = cur;
   theList->size++;
}


/**
 * @brief The add first function for the linked list
 *
 * Appends the specified node to the beginning of this list
 *
 * @param theList - The specified linked list
 * @param nn - The node to be added
 *
 * @warning - The passed in LinkedList * theList is checked - exit(-99) if NULL
 * @warning - The passed in Node * nn is checked - exit(-99) if NULL
 */
void addFirst(LinkedList * theList, Node * nn) {
   if(theList == NULL) {
      perror("Null list\n");
      exit(-99);
   }
   if(nn == NULL) {
      perror("Null new node\n");
      exit(-99);
   }
   
   if(theList->size == 0) {
	  //printf("Adding node onto empty list\n");
      theList->head->next = nn;
      nn->prev = theList->head;
   } else {
	  //printf("Adding node between head and another node\n");
      nn->next =  theList->head->next;
      nn->next->prev = nn;
      nn->prev = theList->head;
      theList->head->next = nn;
   }
   theList->size++;
}


/**
 * @brief The remove first function for the linked list
 *
 * Removes the specified node to the beginning of this list
 *
 * @param theList - The specified linked list
 * @param *removeData - The function pointer for freeing the specific data type
 *
 * @warning - The passed in LinkedList * theList is checked - exit(-99) if NULL
 */
void removeFirst(LinkedList * theList, void (*removeData)(void *)) {
   if(theList == NULL) {
      perror("Null list\n");
      exit(-99);
   }
   


   Node * cur = theList->head->next;
   theList->head->next = cur->next;

   removeData(cur->data);
   cur->next->prev = theList->head;
   cur->next = NULL;
   cur->prev = NULL;
   free(cur);
   cur = NULL;

   theList->size--;
}


/**
 * @brief The remove last function for the linked list
 *
 * Removes the specified node to the end of this list
 *
 * @param theList - The specified linked list
 * @param *removeData - The function pointer for freeing the specific data type
 *
 * @warning - The passed in LinkedList * theList is checked - exit(-99) if NULL
 */
void removeLast(LinkedList * theList, void (*removeData)(void *)) {
   if(theList == NULL) {
      perror("Null list\n");
      exit(-99);
   }
   
   Node * cur = theList->head->next;
   while(cur->next != NULL) {
      cur = cur->next;
   }

   removeData(cur->data);
   if(cur->next != NULL) {
	   cur->next->prev = cur->prev;
   }

   cur->prev->next = cur->next;


   cur->next = NULL;
   cur->prev = NULL;
   free(cur);
   cur = NULL;

   theList->size--;
}


/**
 * @brief The remove item function for the linked list
 *
 * Removes the first occurrence of the specified element from this list, if it
 * is present.  If this list does not contain the element, it is unchanged.
 *
 * @param theList - The specified linked list
 * @param nn - The node to be added
 * @param *removeData - The function pointer for freeing the specific data type
 * @param *compare - The compare function to compare specific data type
 *
 * @warning - The passed in LinkedList * theList is checked - exit(-99) if NULL
 * @warning - The passed in Node * nn is checked - exit(-99) if NULL
 */
void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *)) {
	   if(theList == NULL) {
	      perror("Null list\n");
	      exit(-99);
	   }
	   if(nn == NULL) {
	      perror("Null new node\n");
	      exit(-99);
	   }
	   Node * cur = theList->head->next;
	   int removed = 0;
	   while(cur != NULL && removed != 1) {
		   if(compare(cur->data, nn->data) == 0) {
			  removeData(cur->data);

			  if(cur->next != NULL) {
			   cur->next->prev = cur->prev;
			  }

			  cur->prev->next = cur->next;

			  cur->next = NULL;
			  cur->prev = NULL;
			  free(cur);
			  cur = NULL;

			  removed = 1;
		   } else {
			   cur = cur->next;
		   }
	   }

	   removeData(nn->data);
	   free(nn);

	   theList->size--;
}


/**
 * @brief Empties the list and its contents
 *
 * Removes all of the elements from this list.  The list will be empty after the function completes
 *
 * @param theList - The specified linked list~
 * @param *removeData - The function pointer for freeing the specific data type
 *
 * @param *compare - The compare function to compare specific data type
 *
 * @warning - The passed in LinkedList * theList is checked - if NULL nothing happens
 */
void clearList(LinkedList * theList, void (*removeData)(void *)) {
	   if(theList != NULL) {
		   Node * cur = theList->head->next;
		   Node * next;
		   while(cur != NULL) {
			   next = cur->next;
			   removeData(cur->data);
			   free(cur);
			   cur = next;
		   }

		   free(theList->head);
	   }


}


/**
 * @brief Prints the contents of this linked list
 *
 * Prints the contents, if there are any of this linked list.  If the list is NULL
 * or empty, "Empty List" is printed.
 *
 * @param theList - The specified linked list
 * @param *convert - The function pointer for printing the specific data type
 *
 * @warning - The passed in LinkedList * theList is checked - if NULL "Empty List" is printed
 */
void printList(const LinkedList * theList, void (*convertData)(void *)) {
	   if(theList == NULL || theList->size == 0) {
		   printf("Empty List\n");
	   } else {
		   Node * cur = theList->head->next;
		   while(cur != NULL) {
			   convertData(cur->data);
			   printf("\n");
			   cur = cur->next;
		   }
	   }
}

Node * getLast(const LinkedList * theList) {
   if(theList == NULL || theList->size == 0) {
	   printf("Empty List\n");
   } else {
	   Node * cur = theList->head;
	   while(cur->next != NULL) {
		   cur = cur->next;
	   }

	return cur;

   }
}

Node * getIndex(const int index, const LinkedList * theList) {
	if(theList == NULL || theList->size == 0) {
		printf("Empty List\n");
		//exit(-99);
	} else if(index > theList->size || index < 0) {
		printf("Bad index\n");
		//exit(-99);
	} else {

		Node * cur = theList->head->next;
		int ix = 0;
		while(ix < index) {
			cur = cur->next;
			ix++;
		}

		return cur;
	}
}
