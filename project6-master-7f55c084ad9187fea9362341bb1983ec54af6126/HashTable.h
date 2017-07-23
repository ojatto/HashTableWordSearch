/////////////////////////////////////////////////////////////////////////
//  Hashtable.h                    Author: Kersley Jatto
// 
// This is the header file for the HashTable file. This header file 
// contains the calls for the functions used to create and free a hash 
// table. 
/////////////////////////////////////////////////////////////////////////


#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "memwatch.h"
#include "Search.h"

typedef struct hashtable HashTable;

struct hashtable{
  Search **wordArray;
  int size;
};

#endif

/*
 * Purpose: Create a new hash table.
 * Input: Size
 * Output: A new Hash Table array. 
 */
HashTable *create_hashTable(int);

/*
 * Purpose: This function will transform the key int an address to the file.
 * Input: The key and the tablesize. 
 * Output: A location
 */
unsigned int hash(char *, int);

/*
 * Purpose: This function will retrieve the search object from the array that
 * contains the key by using the provided location.
 * Input: A char string and the hash table to search through
 */
Search * get(HashTable *, char * word);

/* 
 * Purpose: This function places a key into the Hash Table
 * Input: The search object to insert into, the string, and the hash table.
 * Output: None
 */
void put(HashTable *, Search *);

/*
 * Purpose: This function deallocates the hash table once we're done with it. 
 * Input: The hash table
 * Output: None
 */ 
void hash_free(HashTable *);

