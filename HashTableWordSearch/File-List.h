//////////////////////////////////////////////////////////////////////
//  File-List.h                   Author: Kersley Jatto
// 
// This is the header for the File-List.c file which will make 
// linked lists. 
//////////////////////////////////////////////////////////////////////

#ifndef FILELIST_H
#define FILELIST_H

#include "memwatch.h"

typedef struct node Node;
typedef Node List;

struct node{
  char * filename;
  Node * next;
};

#endif

/*
 * Purpose: Create a new linked list. 
 * Input: None
 * Output: An empty Linked List. 
 */
List *list_create();

/*
 * Purpose: This function will add a new node at the beginning containing the 
 * name of a file and its address. 
 * Input: The head of a list, a file name, and the address. 
 * Output: The updated list.
 */
List *list_insert(List * head, char * string);

/*
 * Purpose: This function will search a list to make sure the file hasn't,
 * already been inserted. 
 * Input: The head of a list, file name, and address. 
 * Output: The updated list. 
 */ 
char * list_find(List * head, char * string);

/*
 * Purpose: This function will print the document names in the list. 
 * Input: The head of the list to print
 * Output: The file names and their locations
 */
void list_print(List * head);

/*
 * Purpose: This will take a list of list heads and output a list of filenames ranked by how many of    * the query words they had. 
 * Input: A linked list and the query words 
 * Output: A ranked linked list
 */
List *intersect(List* head1, List* head2);
/*
 * Purpose: This function copies a list.
 * Input: Head of the list to copy
 * Output: The list copy
 */
List *list_copy(List * head);

/*
 * Purpose: This function frees a list. 
 * Input: Head of the list to free
 * Output:None
 */
void list_free(List * head);
