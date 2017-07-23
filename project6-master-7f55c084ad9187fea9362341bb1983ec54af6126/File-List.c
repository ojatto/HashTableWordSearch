//////////////////////////////////////////////////////////////////////
//  File-List.c                   Author: Kersley Jatto
// 
// This file will manage the lists that contain the file names. 
//////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "File-List.h" 
#include "memwatch.h"


/*
 * Purpose: Create a new linked list. 
 * Input: None
 * Output: An empty Linked List. 
 */
List *list_create()
{
  return NULL;
}

/*
 * Purpose: This function will add a new node at the beginning containing the 
 * name of a file and its address. 
 * Input: The head of a list, a file name, and the address. 
 * Output: The updated list.
 */
List *list_insert(List * head, char * string)
{
  Node *new_node = malloc(sizeof(Node));
  if(new_node == NULL)
    {
      fprintf(stderr, "Out of memory\n");
      exit(-1);
    }
  new_node->filename = (char *)calloc(strlen(string) + 1, sizeof(char));
  strcpy(new_node->filename, string);
  new_node->next = NULL;
  
  
  //If our list is empty, we set head equal to the new node. 
  if(head == NULL)
    {
      head = new_node;
    }
  else if(list_find(head, string) == NULL)
    {
      new_node->next = head;
      head = new_node;
    }
  
  return head; 
}

/*
 * Purpose: This function will search a list to make sure the file hasn't,
 * already been inserted. 
 * Input: The head of a list, file name, and address. 
 * Output: The updated list. 
 */ 
char * list_find(List * head, char * string)
{
  Node * temp;
  //We iterate through the list and if the given word exists, we return 1. 
  for(temp = head; temp->next != NULL; temp = temp->next)
    {
      if(strcmp(temp->filename, string) == 0)
	{
	  return temp->filename;
	}
    }
  return NULL;
}

/*
 * Purpose: This function will print the document names in the list. 
 * Input: The head of the list to print
 * Output: The file names and their locations
 */
void list_print(List * head)
{
  if(head == NULL)
    {
      printf("Error: List does not exist.\n");
    }
  else
    {
      //If the list isn't empty, we print each filename. 
      Node *tmp;
      for(tmp = head; tmp != NULL; tmp = tmp->next)
	{
	  printf("%s\n", tmp->filename);
	}
      printf("\n");
    }
}

/*
 * Purpose: This will take a super list and a new list. If the new list contains all the queried  
 * Input: The main list and the next list. 
 * Output: An up-to-date unified list. 
 */
List * intersect(List* head1, List* head2)
{
  List * shareList = list_create();

  Node * temp;
  Node * temp2;

  for(temp = head1; temp != NULL; temp = temp->next)
    { 
      for(temp2 = head2; temp2 != NULL; temp2 = temp2->next)
	{	  
	  if(strcmp(temp->filename, temp2->filename) == 0)
	    {
	      shareList = list_insert(shareList, temp2->filename);
	    }	  
	}
    }
  
  return shareList;
}

/*
 * Purpose: This function copies a list.
 * Input: Head of the list to copy
 * Output: The list copy
 */
List *list_copy(List * head)
{
  List * copy = list_create();

  Node * tmp;
  Node * tmp2;
  Node * tmp3;
  if(head != NULL)
    {
      tmp = head;
      copy = (Node*)malloc(sizeof(Node));
      tmp3 = copy;
      tmp3->next = NULL;
      tmp = tmp->next;
      while(tmp != NULL)
	{
	  tmp2 = (Node*)malloc(sizeof(Node));
	  tmp2->filename = (char *)calloc(strlen(tmp->filename) + 1, sizeof(char));
	  strcpy(tmp2->filename, tmp->filename);
	  tmp2->next = NULL;
	  tmp3->next = tmp2;
	  tmp = tmp->next;
	  tmp3 = tmp3->next;
	}
    }
  return copy;
}

/*
 * Purpose: This function frees a list. 
 * Input: Head of the list to free
 * Output:None
 */
void list_free(List * head)
{
  Node * temp;
  if(head == NULL)
    {
      return;
    }
  //If the list isn't empty, we delete the nodes and free them.
  temp = head;
  while(temp != NULL)
    {
      Node *rm = temp;
      temp = temp->next;
      free(rm->filename);
      free(rm);
    }
}
