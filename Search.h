///////////////////////////////////////////////////////////////////////////
//  Search.h                     Author: Kersley Jatto
//
// This is a header for the Search.c file which will define the aspects of 
// Search objects. 
///////////////////////////////////////////////////////////////////////////

#ifndef SEARCH_H
#define SEARCH_H

#include "memwatch.h"
#include "File-List.h"

typedef struct search Search;

struct search
{
  char * searchWord;
  List * fileList;
};

#endif

/*
 * Purpose: This function creates a Search struct 
 * Input: A word and a pointer to linked list of file names. 
 * Output: A Search struct
 */ 
Search * createSearch(char * newSearch);

/*
 *
 * Purpose: This function accepts a query and checks if the Search word is what 
 * was queried for or is amongst a multi-word query. If it is, the list gets returned.
 * Input: The query words 
 * Output: The linked list in the Search struct
 *
List * word_query(Search * find, char * word);
*/
