///////////////////////////////////////////////////////////////////////
//  HashSearch.c                    Author: Kersley Jatto
//
//
// This is the HashSearch.c file. This contains the main function that 
// will accept the file names and the list of words that should be
// ignored. 
///////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memwatch.h"
#include "HashTable.h"
#include "File-List.h"
#include "Search.h"

#define BUFFSIZE 1000
#define BUFFSIZE2 500000
#define BUFFSIZE3 2400


/*
 * Purpose: This function splits each query line into all the seprate words. 
 * Input: A string of characters representing a line.
 * Output: An array of strings
 */
char ** queryGen(char * query)
{
  //This is the array of strings that our program will return. 
  char ** querylist = (char**)calloc(sizeof(char*) * BUFFSIZE3, sizeof(char*));
  //Check if we're out of memory.
  if(querylist == NULL)
    {
      printf("WARNING: OUT OF MEMORY\n");
      return NULL;
    }

  //We set string equal to the address of the first index. 
  char * str = &query[0];
  int a; //This will loop through the fgets line.
  int b = 0; //This puts each individual string at the next index. 
  int initial = strlen(query); //We get the initial length of the fgets line for the for loop

  for(a = 0; a < initial; a++)
    {
      //If we run into a non-letter character, we change str's address and add the partition to the 
      //array. 
      if(isalpha(query[a]) == 0)
	{
	  query[a] = '\0';
	  querylist[b] = (char *)calloc(strlen(str) + 1, sizeof(char));
	  //Check if we're out of memory.
	  if(querylist[b] == NULL)
	    {
	      printf("WARNING: OUT OF MEMORY\n");
	      return NULL;
	    }
	  strcpy(querylist[b], str);
	  str = &query[a+1];
	  b++;
	}
    }
  if(str[0] != '\0')
    {
      querylist[b] = (char *) calloc(strlen(str) + 1, sizeof(char));
      //Check if we're out of memory
      if(querylist[b] == NULL)
	{
	  printf("WARNING: OUT OF MEMORY\n");
	  return NULL;
	}

      strcpy(querylist[b], str);
    }
  return querylist;
}

/*
 * Purpose: Checks if a string is a word.
 * Input: A word
 * Output: 0 or 1
 */
int isWord(char * word)
{
  int y;
  int length = strlen(word);
  for(y = 0; y < length; y++)
    {
      if(isalpha(word[y]) == 0) 
	{
	  return 0;
	}
    }
  return 1; 
}


/*
 * Purpose: This deallocates the query array when we're done with it.
 * Input: The array
 * Output: None
 */
void freeArray(char ** array)
{
  int i;
  for(i = 0; i < BUFFSIZE3; i++)
    {
      free(array[i]);
    }
  free(array);
}

/*
 * Purpose: This function prints an array of query words.
 * Input: A char array
 * Output: None
 */
void printArray(char ** array)
{
  printf("Here are the words that were searched for: \n\n");

  int i = 0;
  while(array[i] != NULL)
    {
      printf("%s\n", array[i]);
      i++;
    }
  printf("\n");
}


/*
 * Purpose: This function handles the querying. 
 * Input: Argv
 * Output: None
 */
void queryrun(char ** argv, HashTable * stopTable, HashTable * searchTable)
{
  //With both hash tables made, we will now initiate the query. The idea is that user, for as long
  //as they want, will be able to type in word queries. When a query is entered, the program will search 
  //through searchTable for the words. If they equal a stop list word, they are ignored. If it's a
  // multi-word, a file will only be returned if it has all the searched for words. 
  
  printf("\n\nThis is the HashSearch program. This program has taken the files you entered and creates two hash\ntables. The first hash table is comprised of a list of 'stoplist' words which the file will ignore whenever it stumbles on them.The second hash table is the core hash table of the program as it stores all non stoplist words excluding non letter characters. The program will let you enter queries until you enter 'Ctrl+D.\n");
  
  //This char variable will store an entire line of input as string. If it doesn't equal 1, then 
  //we run a query on it. 
  char queryWords[2400];
  
  printf("Search:");
  //printf
  while(fgets(queryWords, 2400, stdin) != NULL)
    { 
      //We invoke queryGen to make an array out of all the words.
      char ** query = queryGen(queryWords);
      
      //If query isn't a word or is more than one value, we stop. 
      if(isWord(query[0]) == 0)// || query[1] != NULL)
	{
	  printf("No results. Please type a valid query.\n");
	}
      //If the query is only one word, we simply see if it is in the Hash Table. If it is, 
      //we print out print out the list of files it is in.  
      else if(query[0] != NULL && query[1] == NULL)
	{
	  printArray(query);
	  
	  printf("Results:\n");
	  Search * results = get(searchTable, query[0]);
	  if(results != NULL)
	    {
	      //We invoke the list print function to print all the lists  with word. 
	      list_print(results->fileList);
#ifdef INCLUDE_DOCS
	      List * tmp;
	      for(tmp = results->fileList; tmp->next != NULL; tmp = tmp->next)
		{
		  printf("Filename: %s\n", tmp->filename);
		  int c;
		  FILE *file;
		  file = fopen(tmp->filename, "r");
		  if (file) 
		    {
		      while ((c = getc(file)) != EOF)
			putchar(c);
		      fclose(file);
		    }
		}
#endif
	    }
	  else
	    {
	      printf("No results found.\n");
	    }
	}
      //If we have a multi-word query, things get interesting. We only want to output files
      //that contain all the words so we utilize the interest function to create a list
      //of filenames that have all the words. 
      else
	{
	  //Print the query for reference.
	  printArray(query);
	  
	  //This is the list that will hold all the file names that contain all the query words 
	  List * shareList = list_create();
	  
	  //Set the starting index. 
	  int k = 0;

	  //The value of this variable will help the code know if any of the files in the list have all the query words
	  int match = 1;
	  
	  printf("Results:\n");
	  
	  //To get sharList started, we see if there's an interestion in the first two lists
	  //First we see if the two items are even in our Hash Table. 
	  
	  Search * results = get(searchTable, query[k]);
	  k++;
	  Search * results2 = get(searchTable, query[k]);


	  //First we need to see if the first 2 query words turned up in any of the given files. 
	  if(results != NULL && results2 != NULL)
	    {
	      //We invoke interest which makes a new linked list out of all files with both words. 
	      shareList = intersect(results->fileList, results2->fileList);
	      
	      //We check if shareList has anything and match isn't zero. 
	      if(shareList != NULL)
		{
		  //Now we move the array index value to 2. 
		  k++;
		  
		  //This loops as long as there's more query words to check and match doesn't equal 0.
		  while(query[k] != NULL && match != 0)
		    {
		      Search * results = get(searchTable, query[k]);

		      //If results isn't null, we then check if there's an intersection. If it is, we 
		      //set match to zero and quit there.. 
		      if(results != NULL)
			{
			  //We see if there's an intersection between the current list and the new word.
			  //If there is, we update our list with the interesection list. If it's null, 
			  //we set match to 0.
			  List * intersection  = intersect(shareList, results->fileList);

			  if(intersection != NULL)
			    {
			      //We free the memory shareList is pointing to before pointing to the new list
			      list_free(shareList);
			      shareList = intersection;
			    }
			  else
			    {
			      match = 0;
			    }
			}
		      else
			{
			  match = 0;
			}
		      
		      //Increment k to move to the index
		      k++;
		    }
		  //This if statement will print the list if we found at least 1 file with all the words. If it turns out there were no
		  //matches, then we print that no results were found.
		  if(shareList != NULL && match != 0)
		    {
		      list_print(shareList);
		    }
		  else
		    {
		      printf("No results were found for the search\n");
		    }
		  //We free shareList in preparation for the next query
		  list_free(shareList);
		}
	    }
	  else
	    {
	      //We print this if the first 2 query words failed
	      printf("No file contained all the queried words\n");
	    }
	}
      //Free the array of words from the query.
      freeArray(query);
      printf("\nWould you like to continue or terminate the program?\n");
      printf("Search:");
    }
  printf("Thanks for using the program!\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Purpose: To create a hash table for the ignore words and search words.
 * Input: The list of ignore words and the list of file names. 
 * Output: None
 */ 
int main(int argc, char ** argv)
{
  if(argc < 2)
    {
      fprintf(stderr, "Usage: %s <data file>\n", argv[0]);
      return 1;
    }
  ///////////////////////////////////////////////////////////
  //Declare a giant character array for the stop list words. 
  char theWord[100];
  
  //First we take the file location.
  FILE * input = fopen(argv[1], "r");
  
  if(input == NULL)
    {
      fprintf(stderr, "Warning: Cannot read. \n");
      return -1;
    }
  
  //We create the hash table to store the stop list words. 
  HashTable * stopTable = create_hashTable(BUFFSIZE);
  while(fscanf(input,"%s", theWord) == 1) 
    {
      char * str = &theWord[0];
      int a;
      int initial = strlen(theWord);
      for(a = 0; a < initial; a++)
	{
	  if(isalpha(theWord[a]) == 0)
	    {
	      theWord[a] = '\0';
	      Search * wordpiece = createSearch(str);
	      put(stopTable, wordpiece);
	      str = &theWord[a+1];
	    }
	}
      Search * fileWord = createSearch(str);
      put(stopTable, fileWord);
    }
  fclose(input);
  ///////////////////////////////////////////////////////////////////////////////////////////
  
  //Now we create the for loop that will make the core Hash Table. We utilize argv
  //as it'll contain each filename from 2 onward. 
  int k;
  
  //This hash table will be the one to store all the words to look out for. 
  HashTable * searchTable = create_hashTable(BUFFSIZE2); 
  for(k = 2; k < argc; k++)
    {
      //First we take the file location.
      FILE * input2 = fopen(argv[k], "r");
      
      if(input2 == NULL)
	{
	  fprintf(stderr, "Warning: Cannot read. \n");
	  return -1;
	}
      
      while(fscanf(input2,"%s", theWord) == 1)
	{
	  //This string points to the begining of the incoming word. It'll help us with tokenizing. 
	  char * str = &theWord[0];
	  int a;
	  int initial = strlen(theWord);
	  for(a = 0; a < initial; a++)
	    {
	      if(isalpha(theWord[a]) == 0)
		{
		  theWord[a] = '\0';
		  //We check if the word is already in the table or is a stop word. If not, we add it. 
		  if( get(searchTable, str) == NULL && get(stopTable, str) == NULL)
		    {
		      //Since it's not in the table, we create a whole new search object. 
		      Search * wordpiece = createSearch(str);
		      wordpiece->fileList = list_insert(wordpiece->fileList, argv[k]);
		      put(searchTable, wordpiece);
		      str = &theWord[a+1];
		    }
		  else if(get(searchTable, str) != NULL && get(stopTable, str) == NULL)
		    {
		      //Since it IS in the table, we check to see if the filename has already been accounted for
		      //If it isn't we add the filename to the existing Search Object's list. 
		      Search * found = get(searchTable,str);
		      if(list_find(found->fileList, argv[k]) == NULL)
			{
			  found->fileList = list_insert(found->fileList, argv[k]);
			}
		      str = &theWord[a+1];
		    }
		}
	    }
	  //These two blocks deal with any words that don't have to have non-letter characters removed. 
	  //Like the first two the if block occurs if it's not in the search table while the second one 
	  //occurs if the word already is.
	  if( get(searchTable, str) == NULL && get(stopTable, str) == NULL)
	    {
	      Search * fileWord = createSearch(str);
	      fileWord->fileList = list_insert(fileWord->fileList, argv[k]);
	      put(searchTable, fileWord);
	    }
	  else if(get(searchTable, str) != NULL && get(stopTable, str) == NULL)
	    {
	      Search * found = get(searchTable,str);
	      if(list_find(found->fileList, argv[k]) == NULL)
		{
		  found->fileList = list_insert(found->fileList, argv[k]);
		}
	    }
	}
      fclose(input2);
    }
  queryrun(argv, stopTable, searchTable);
  hash_free(searchTable);
  hash_free(stopTable);
  return 1;

}

