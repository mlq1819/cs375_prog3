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
#define DEBUG true
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
	int num = 0;
	int capacity = 0;
	size_t idx = 0;
	num = stoi(reader.current(), &idx, 10);
	idx++;
	capacity = stoi(reader.current().substr(idx, -1), NULL, 10);
	reader.next();
	Item items[num];
	for(int i=0; i<num; i++){
		int p = stoi(reader.current(), &idx, 10);
		idx++;
		int w = stoi(reader.current().substr(idx, -1), NULL, 10);
		items[i]=Item((unsigned int) p,(unsigned int) w);
		if(!reader.next())
			break;
	}
#if PRESORT
	quicksort(items, 0, (unsigned int) num);
#endif
	Algorithm alg = Algorithm(items, (unsigned int) num, (unsigned int) capacity);
	unsigned int computed_profit = 0;
	clock_t t = clock();
	switch(mode){
		case 0:
			computed_profit = alg.greedy1();
			break;
		case 1:
			computed_profit = alg.greedy2();
			break;
		case 2:
			computed_profit = alg.backtrack();
	}
	t = clock()-t;
	float m = ((float) t)/CLOCKS_PER_SEC * 1000;
	ofp << num << " " << computed_profit << " " << m << "\n";
	ofp.close();
#if DEBUG
cout << num << " " << computed_profit << " " << m << endl;
#endif
	return 0;
}