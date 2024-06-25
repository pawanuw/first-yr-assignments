#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h"

char memory[25000];

/*
struct Block {
	size_t size;
	int free;
	struct Block *next;
}; */

struct Block *freeList= (void*) memory;

void initialize() {
	
	freeList-> size = 25000 - sizeof(struct Block);
	freeList-> free = 1;
	freeList-> next = NULL; 
	
}

void split(struct Block *fitting_slot, size_t size) {
	
	struct Block *new= (void*)fitting_slot + size + sizeof(struct Block);
	new-> size = (fitting_slot-> size) - size - sizeof(struct Block); 
	new-> free = 1; 
	new-> next = fitting_slot-> next; 
	fitting_slot-> size = size; 
	fitting_slot-> free = 0;
	fitting_slot-> next = new;
}

void *MyMalloc(size_t noOfBytes) {
	
	struct Block *curr;
	void *result;
	
	if(!(freeList-> size)) {
		initialize();
	}
	
	curr = freeList;
	
	while((((curr-> size) < noOfBytes) || ((curr-> free) == 0)) && (curr-> next != NULL)) {
		//prev = curr;
		curr = curr-> next;
	}
	
	if((curr-> size) == noOfBytes) {
		curr-> free = 0;
		result = (void*) (++curr); 
		return result;
	}
	
	else if ((curr-> size) > (noOfBytes + sizeof(struct Block))) {
		split (curr, noOfBytes);
		result = (void*) (++curr);
		return result;
	}
	
	else {
		result = NULL;
		printf("Sorry. No sufficient memory to allocate\n");
		return result;
	}
}

void merge() {
	
	struct Block *curr;
	curr = freeList;
	while((curr-> next) != NULL) {
		if((curr-> free) && (curr-> next-> free)) {
			curr-> size += (curr-> next-> size) + sizeof(struct Block);
			curr-> next = curr-> next-> next;
		}
		//prev = curr;
		curr = curr-> next;
	}
}

void MyFree(void *ptr) {
	
	if(((void*) memory <= ptr) && (ptr <= (void*)(memory + 25000))) {
		struct Block *curr = ptr;
		--curr;
		curr-> free = 1;
		merge();	
	}
	
	else {
		printf("Please provide a valid pointer allocated by MyMalloc\n");
	}
}

