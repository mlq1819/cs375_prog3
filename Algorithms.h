#ifndef MQ_ALGO_H
#define MQ_ALGO_H
#include "item.h"
#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#ifndef DEBUG
#define DEBUG true
#endif

unsigned int max(unsigned int, unsigned int);
unsigned int max(unsigned int, unsigned int, unsigned int);
void swap(Item * A, unsigned int a, unsigned int b);
unsigned int partition(Item * A, unsigned int low, unsigned int high);
void quicksort(Item * A, unsigned int low, unsigned int high);
void quicksort_helper(Item * A, unsigned int low, unsigned int high);
bool isSorted(const Item * A, size_t size);

class Algorithm{
	private:
		Item * items;
		size_t size;
		unsigned int capacity;
		unsigned int getMaxPossible() const;
		unsigned int getMaxPossible(unsigned int) const;
		unsigned int greedy2_helper(unsigned int) const;
		unsigned int backtrack_helper(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	public:
		Algorithm(Item *, size_t, unsigned int);
		size_t getSize() const {return this->size;};
		unsigned int getCapacity() const {return this->capacity;};
		unsigned int greedy1();
		unsigned int greedy2();
		unsigned int backtrack();
};

#endif