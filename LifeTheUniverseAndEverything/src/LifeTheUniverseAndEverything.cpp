//============================================================================
// Name        : LifeTheUniverseAndEverything.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Take in numbers from stdin and keep printing them until you hit 42
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> numbers; // create a vector, for fun
	while(1){
		int i;
		cin >> i;
		if (i == 42)
			break;
		numbers.push_back(i);
	}
	//print all the numbers now
	for (vector<int>::iterator i = numbers.begin(); i != numbers.end(); i++)
		cout << *i<<endl;
	return 0;
}
