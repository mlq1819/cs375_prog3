#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include "Filereader.h"

using namespace std;

int main(int argc, char ** argv){
	if(argc<4){
		printf("Not enough arguments: %d\n", argc);
		return 1;
	}
	char * of_name = argv[2];
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
	capacity = stoi(reader.current(idx, string::npos), NULL, 10);
	
	
	return 0;
}