#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stddef.h>

struct Block {
    size_t size;
    int free;
    struct Block* next;
};

void initialize();

void split(struct Block* fitting_slot, size_t size);

void* MyMalloc(size_t noOfBytes);

void merge();

void MyFree(void* ptr);

#endif 

