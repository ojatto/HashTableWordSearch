all: HashSearch FR_debug

HashSearch: HashTable.o File-List.o Search.o  memwatch.o HashSearch.o
	gcc -o HashSearch  HashTable.o File-List.o  Search.o memwatch.o  HashSearch.o  -Wall -DMEMWATCH -DMW_STDIO

Search.o: Search.h memwatch.h
	gcc -c Search.c -Wall -DMEMWATCH -DMW_STDIO

HashTable.o: HashTable.h Search.h File-List.h memwatch.h
	gcc -c HashTable.c -Wall -DMEMWATCH -DMW_STDIO

File-List.o: File-List.h  memwatch.h
	gcc -c File-List.c -Wall -DMEMWATCH -DMW_STDIO

memwatch.o: memwatch.c memwatch.h
	gcc -c memwatch.c -Wall -DMEMWATCH -DMW_STDIO

HashSearch.o: Search.h File-List.h HashTable.h  memwatch.h
	gcc -c HashSearch.c -Wall -DMEMWATCH -DMW_STDIO

FR_debug: HashSearch.c  memwatch.c Search.c File-List.c HashTable.c
	gcc -g -o FR_debug -DINCLUDE_DOCS HashTable.c memwatch.c Search.c File-List.c HashSearch.c -DMEMWATCH -DMW_STDIO

clean:
	rm *.o
