/////////////////////////////////////////////////////////////////////////
//  HashTable.c                    Author: Kersley Jatto
// 
// This file contains the 
/////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memwatch.h"
#include "HashTable.h"
#include "File-List.h"
#include "Search.h"
 
/*
 * Purpose: Create a new hash table.
 * Input: Size
 * Output: A new Hash Table array. 
 */
HashTable *create_hashTable(int tableSize)
{
  //We make an array of Search pointers.
  HashTable * hash_table = (HashTable*)malloc(sizeof(HashTable));
  hash_table->size = tableSize;
  hash_table->wordArray = (Search**)malloc(sizeof(Search*) * hash_table->size);
  
  int i;
  for(i = 0; i < hash_table->size; i++)
    {
      hash_table->wordArray[i] = NULL;
    } 
  return hash_table;
}

/*
 * Purpose: This function will transform the key int an address to the file.
 * Input: The key and the tablesize. 
 * Output: A location
 */
unsigned int hash(char *key, int tableSize) 
{
  unsigned int hashValue, alpha = 31415,  beta = 27183;
  for (hashValue = 0; *key != 0; 
       key++, alpha = alpha*beta % (tableSize-1))
    hashValue = (alpha*hashValue + *key) % tableSize;
  return hashValue;
}

/*
 * Purpose: This function will retrieve the search object from the array that
 * contains the key by using the provided location.
 * Input: A char string and the hash table to search through
 */
Search * get(HashTable * table, char * word)
{
  //This holds the the first index we'll check. 
  int index = hash(word, table->size);
  //This holds index's initial value so we can compare later to see if we've checked each index. 
  int startpoint = index;
  if(table->wordArray[index] != NULL && strcasecmp(table->wordArray[index]->searchWord, word) == 0)
    {
      return table->wordArray[index];
    }
  else
    {
      while(table->wordArray[index] != NULL && strcasecmp(table->wordArray[index]->searchWord, word) != 0 )
        {	  
	  index++;
	  //If our search for the item takes us to the last index we reset to zero. 
          if(index == table->size)
            {
              index = 0;
            }
	  //This makes sure we don't check the hash table twice. 
	  if(index == startpoint)
	    {
	      return NULL;
	    }
        }
      if(table->wordArray[index] != NULL && strcasecmp(table->wordArray[index]->searchWord, word) == 0)
	{
	  return table->wordArray[index];
	}
    }
  return NULL;
}
/* 
 * Purpose: This function places a key into the Hash Table
 * Input: The search object to insert into, the string, and the hash table.
 * Output: None
 */
void put(HashTable * table, Search * find)
{
  int index = hash(find->searchWord, table->size);
  //We store the initial index. We need to keep track of where we started in case the table gets full. 
  int startpoint = index;
  if(table->wordArray[index] == NULL)
    {
      table->wordArray[index] = find;
    }
  else
    {
      while(table->wordArray[index] != NULL)
	{
	  index++;
	  if(index == table->size)
	    {
	      index = 0;
	    }
	  if(index == startpoint)
	    {
	      printf("HASH TABLE HAS REACHED FULL CAPACITY. TERMINATING PROGRAM!!!!!!!!!\n");
	      exit(1);
	    }
	}
      if(table->wordArray[index] == NULL)
	table->wordArray[index] = find;
    }
}

/*
 * Purpose: This function deallocates the hash table once we're done with it. 
 * Input: The hash table
 * Output: None
 */ 
void hash_free(HashTable * table)
{
  int i;
  for(i = 0; i < table->size; i++)
    {
      if(table->wordArray[i] != NULL)
	{
	  list_free(table->wordArray[i]->fileList);
	  free(table->wordArray[i]->searchWord);
	  free(table->wordArray[i]);
	}
    }
  free(table->wordArray);
  free(table);
}
