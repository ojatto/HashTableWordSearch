///////////////////////////////////////////////////////////////////////////
//  Search.c                     Author: Kersley Jatto
//
// This file defines the behavior of the Search struct and the function 
// that will check if a word is in the query in question.  
///////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "File-List.h"
#include "Search.h"
#include "memwatch.h"


/*
 * Purpose: This function creates a Search struct 
 * Input: A word and a pointer to linked list of file names. 
 * Output: A Search struct
 */ 
Search * createSearch(char * newSearch)
{
  Search * finder = (Search *)malloc(sizeof(Search));

  //Here we allocate space for the incoming word and copy.
  finder->searchWord = (char *)calloc(strlen(newSearch) + 1, sizeof(char));
  strcpy(finder->searchWord, newSearch);

  //We instantiate fileList with an empty list. 
  finder->fileList = list_create();
  return finder;
}
