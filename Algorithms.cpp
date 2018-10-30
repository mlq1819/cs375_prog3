#include "Algorithms.h"

using namespace std;

unsigned int max(unsigned int a, unsigned int b){
	unsigned int max = a;
	if(b>max)
		max=b;
	return max;
}

unsigned int max(unsigned int a, unsigned int b, unsigned int c){
	unsigned int max = a;
	if(b>max)
		max=b;
	if(c>max)
		max=c;
	return max;
}

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

double Algorithm::getMaxPossible() const {
	return getMaxPossible(0);
}

unsigned int Algorithm::getMaxPossible(unsigned int start) const {
	unsigned int total_profit=0;
	unsigned int total_weight=0;
	unsigned int i = start;
	while(i<this->size && total_weight+this->items[i]<=this->capacity){
		total_profit+=this->items[i].getProfit();
		total_weight+=this->items[i].getWeight();
	}
	if(i<this->size && total_weight!=this->capacity){
		unsigned int difference = this->capacity-total_weight;
		total_profit+=(difference*this->items[i].getProfit())/this->items[i].getWeight();
		total_weight+=difference;
	}
	return total_profit;
}

unsigned int Algorithm::greedy1(){
	vector<Item> solution = vector<Item>();
	if(!isSorted(this->items, this->size))
		quicksort(this->items, 0, this->size);
	unsigned int total_profit=0;
	unsigned int total_weight=0;
	for(unsigned int i=0; i<this->size; i++){
		if(total_weight+this->items[i].getWeight()<=this->capacity){
			total_weight+=this->items[i].getWeight();
			total_profit+=this->items[i].getProfit();
			solution.push_back(Item(this->items[i]));
		}
	}
	return solution.size();
}

unsigned int Algorithm::greedy2(){
	vector<Item> solution = vector<Item>();
	if(!isSorted(this->items, this->size))
		quicksort(this->items, 0, this->size);
	unsigned int pmax, gmax;
	gmax=greedy1();
	pmax=greedy2_helper(0);
	if(pmax>gmax)
		return pmax;
	return gmax;
}

unsigned int Algorithm::greedy2_helper(unsigned int c) const {
	if(c>=this->size)
		return 0;
	unsigned int h = greedy2_helper(c+1);
	unsigned int j = this->items[i].getProfit();
	if(this->items[i].getWeight()>this->capacity)
		j=0;
	if(j>h)
		return j;
	return h;
}

unsigned int Algorithm::backtrack(){
	if(!isSorted(this->items, this->size))
		quicksort(this->items, 0, this->size);
	unsigned int all_profit=0;
	for(unsigned int i=0; i<this->size; i++)
		all_profit+=this->items[i].getProfit();
	unsigned int first_bound = getMaxPossible(0);
	return backtrack_helper(0, 0, first_bound, all_profit, 0, 0);
}

unsigned int Algorithm::backtrack_helper(unsigned int cur_profit, unsigned int cur_weight, unsigned int cur_bound, unsigned int cur_best, unsigned int cur_idx){
	if(cur_idx>=this->size){
		return 0;
	} else {
		bool promising = true;
		promising = promising && cur_weight<=this->capacity;
		promising = promising && cur_bound>cur_best;
		if(!promising)
			return 0;
		unsigned int take = backtrack_helper(cur_profit+this->items[cur_idx].getProfit(), cur_weight+this->items[cur_idx].getWeight(), cur_bound, max(cur_profit, cur_best), cur_idx+1);
		unsigned int leave = backtrack_helper(cur_profit, cur_weight, cur_profit+getMaxPossible(cur_idx+1), max(take, cur_profit, cur_best), cur_idx+1);
		return max(take, cur_profit, leave);
	}
}