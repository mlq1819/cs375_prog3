#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <time.h>
#include "Filereader.h"
#include "item.h"
#include "Algorithms.h"
#define PRESORT true
#ifndef DEBUG
#define DEBUG false
#endif

using namespace std;

int main(int argc, char ** argv){
	if(argc<4){
		printf("Not enough arguments: %d\n", argc);
		return 1;
	}
	int mode = stoi(argv[3], NULL, 10);
	
	ifstream ifp;
	ifp.open(argv[1]);
	if(!ifp.is_open() && ifp.good()){
		cout << "Bad Input File Name: \"" << argv[1] << "\"" << endl;
		return 1;
	}
	FileReader reader = FileReader(&ifp);
	if(!reader.readFile()){
		cout << "Reader Failure" << endl;
		ifp.close();
		return 1;
	}
	ifp.close();
	ofstream ofp;
	ofp.open(argv[2]);
	if(!ofp.is_open() || !ofp.good()){
		cout << "Bad Output File Name: \"" << argv[2] << "\"; printing to STDOUT instead" << endl;
		return 1;
	}
	vector<int> nums = vector<int>();
	nums.push_back(0);
	vector<int> capacities = vector<int>();
	capacities.push_back(0);
	vector<Algorithm> algs = vector<Algorithm>();
	size_t idx = 0;
	reader.start();
	do{
		nums[nums.size()-1] = stoi(reader.current(), &idx, 10);
		idx++;
		capacities[capacities.size()-1] = stoi(reader.current().substr(idx, -1), NULL, 10);
		Item items[nums[nums.size()-1]];
#if DEBUG
cout << "Reading next " << nums[nums.size()-1] << " lines; Capacity=" << capacities[capacities.size()-1] << endl;
#endif
		reader.next();
		for(int i=0; i<nums[nums.size()-1]; i++){
			int p = stoi(reader.current(), &idx, 10);
			idx++;
			int w = stoi(reader.current().substr(idx, -1), NULL, 10);
#if DEBUG
cout << "Read item: p=" << p << ";w=" << w << endl;
#endif
			items[i]=Item((unsigned int) p,(unsigned int) w);
			if(!reader.next())
				break;
		}
#if PRESORT
quicksort(items, 0, nums[nums.size()-1]);
#endif
		algs.push_back(Algorithm(items, (unsigned int) nums[nums.size()-1], (unsigned int) capacities[capacities.size()-1]));
	} while(!reader.atEnd());
	for(unsigned int i=0; i<algs.size(); i++){
		unsigned int computed_profit = 0;
		clock_t t = clock();
		switch(mode){
			case 0:
				computed_profit = algs[i].greedy1();
				break;
			case 1:
				computed_profit = algs[i].greedy2();
				break;
			case 2:
				computed_profit = algs[i].backtrack();
		}
		t = clock()-t;
		float m = ((float) t)/CLOCKS_PER_SEC * 1000;
		ofp << algs[i].getSize() << " " << computed_profit << " " << m << "\n";
#if DEBUG
cout << algs[i].getSize() << " " << computed_profit << " " << m << endl;
#endif
	}
	ofp.close();
	return 0;
}