#include "Algorithms.h"

using namespace std;

void swap(Item * A, unsigned int a, unsigned int b){
	Item a_i = Item(A[a]);
	A[a]=Item(A[b]);
	A[b]=a_i;
}

unsigned int partition(Item * A, unsigned int low, unsigned int high){
	Item pivot = A[high];
	unsigned int i = low;
	for(unsigned int j=low; j<high; j++){
		if(A[j]<pivot){
			if(i!=j)
				swap(A, i, j);
			i++;
		}
	}
	swap(A, i, high);
	return i;
}

void quicksort(Item * A, unsigned int low, unsigned int high){
	if(low<high){
		unsigned int p = partition(A, low, high);
		if(p>0)
			quicksort(A, low, p-1);
		quicksort(A, p+1, high);
	}
}

bool isSorted(const Item * A, size_t size){
	for(unsigned int i=1; i<size; i++){
		if(A[i-1]>A[i])
			return false;
	}
	return true;
}

Algorithm::Algorithm(Item * items, size_t size, unsigned int capacity){
	this->items=items;
	this->size=size;
	this->capacity=capacity;
	this->solution=vector<Item>();
}

unsigned int Algorithm::getSolutionProfit() const {
	unsigned int sum = 0;
	for(unsigned int i=0; i<this->solution.size(); i++){
		sum+=this->solution[i];
	}
	return sum;
}

vector<Item> Algorithm::greedy1(){
	this->solution.erase(this->solution.begin(), this->solution.end());
	if(!isSorted(this->items, this->size))
		quicksort(this->items, 0, this->size);
	unsigned int total_profit=0;
	unsigned int total_weight=0;
	for(unsigned int i=0; i<this->size; i++){
		if(total_weight+this->items[i].getWeight()<=this->capacity){
			total_weight+=this->items[i].getWeight();
			total_profit+=this->items[i].getProfit();
			this->solution.push_back(Item(this->items[i]));
		}
	}
	this->solution.shrink_to_fit();
	return this->solution;
}

vector<Item> Algorithm::greedy2(){
	this->solution.erase(this->solution.begin(), this->solution.end());
	if(!isSorted(this->items, this->size))
		quicksort(this->items, 0, this->size);
	unsigned int total_profit=0;
	unsigned int total_weight=0;
	
	
	
	this->solution.shrink_to_fit();
	return this->solution;
}

vector<Item> Algorithm::backtrack(){
	this->solution.erase(this->solution.begin(), this->solution.end());
	if(!isSorted(this->items, this->size))
		quicksort(this->items, 0, this->size);
	unsigned int total_profit=0;
	unsigned int total_weight=0;
	
	
	
	this->solution.shrink_to_fit();
	return this->solution;
}