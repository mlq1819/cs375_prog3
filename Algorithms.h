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

void swap(Item * A, unsigned int a, unsigned int b);
unsigned int partition(Item * A, unsigned int low, unsigned int high);
void quicksort(Item * A, unsigned int low, unsigned int high);
bool isSorted(const Item * A, size_t size);

class Algorithm{
	private:
		Item* items;
		size_t size;
		unsigned int capacity;
		std::vector<Item> solution;
	public:
		Algorithm(Item *, size_t, unsigned int);
		size_t getSize() const {return this->size;};
		unsigned int getCapacity() const {return this->capacity;};
		std::vector<Item> greedy1();
		std::vector<Item> greedy2();
		std::vector<Item> backtrack();
		unsigned int getSolutionProfit() const;
		unsigned int getSolutionSize() const {return this->solution.size();};
};

#endif