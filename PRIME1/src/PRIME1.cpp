//============================================================================
// Name        : PRIME1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : generate all prime numbers between two given numbers
/*Input

The input begins with the number t of test cases in a single line (t<=10).
In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

Output

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

Example

Input:
2
1 10
3 5

Output:
2
3
5
7

3
5
 */
//============================================================================

#include <iostream>
#include <vector>
#include <utility>
namespace 
{
    const int BATCH_SIZE = 100000;
}
using namespace std;

long int largestNumberChecked = 1;
long int largestMax = 0;

void print(long int min, long int max, vector<long int>& primes){
	//the list has all primes calculated upto max. Now print out all non-zero numbers from min to max
	vector<long int>::iterator iter = primes.begin();
	while( iter != primes.end()){
		if (*iter < min);
		else if (*iter > max)
			break;
		else
			cout << *iter << endl;
		iter++;
	}
	cout << endl;

}

void find_some_primes(long int startOfBatch,long int endOfBatch,vector<long int>& primes){
	//populate the numbers vector with a batch of numbers, and use the sieve to find primes in this batch
	vector<long int> numbers;
	for ( long int i = startOfBatch; i < endOfBatch; i+=2){
		numbers.push_back(i);
	}
	int offset = startOfBatch !=3 ? startOfBatch: 0;
	long int largestNumberInTheBatch = numbers.back();

	// sieve out all multiples of the primes first
	for (vector<long int>::iterator iter = primes.begin();iter != primes.end();iter++){
		long int j = 3;
		while ((*iter) * j < largestNumberInTheBatch){
			if ((*iter) * j < startOfBatch);//don't check for numbers smaller than the batch beginning
			else
				numbers[((*iter) *j)/2 - offset] = 0;  // zero out all multiples of this number
			j+=2;
		}
	}

	//Now,strike out all multiples of all numbers from batchStart to end/2 in the numbers vector
	for (long int i = 3;i <= endOfBatch/2 - offset; i+=2){
		if (numbers[i] == 0 ) continue;
		long int j = 3;
		while ( i*j < largestNumberInTheBatch){
				numbers[(i*j)/2 - offset] = 0;  // zero out all multiples of this number
			j+=2;
		}
	}

	// numbers now has all primes in this sub-range. Copy these primes into the primes vector.
	for (unsigned int i = 0; i < numbers.size();i++){
		if (numbers[i] != 0)
			primes.push_back(numbers[i]);
	}
	largestNumberChecked = endOfBatch;
}

//Sieve of Eratosthenes modified to work only on odd numbers
void find_all_primes(long int min, long int max,vector<long int>& primes){
	if (max < min){
		cout << "BAD RANGE!!!"<< min <<" > "<<max;
		return;
	}
	if (max < largestNumberChecked)
		print(min,max,primes);
	else{
		// as long as we haven't hit the max number, keep generating primes for batches of BATCH_SIZE
		//and store only the primes
		while(1){
			long int startOfBatch = (largestNumberChecked % 2 == 0) ? 3 : largestNumberChecked;
			long int endOfBatch = (startOfBatch + BATCH_SIZE) > max ? max : (startOfBatch + BATCH_SIZE);
			if (max == 3)	break;
			find_some_primes(startOfBatch,endOfBatch,primes);
			if (endOfBatch == max)	break;
		}
		print(min,max,primes);
	}
}


int main() {
	cout << "enter no. of test cases"<< endl;
	int testCases;
	cin >> testCases;
	// a vector of pairs to hold the min and max values for each test case
	vector<pair<long int, long int> > ranges;

	for (int i = 0;i < testCases; i++){
		cout << "enter next range"<< endl;
		long int min,max;
		cin >> min >> max;
		ranges.push_back(make_pair(min,max));
		if (max > largestMax)
			largestMax = max;
	}
	//vector primes, to hold primes upto the maximum value.
	vector<long int> primes(1,2); //primes[0] = 2
	largestNumberChecked = 2;
	//now find the primes
	vector<pair<long int,long int> >::iterator iter = ranges.begin();
	while(iter != ranges.end()){
		find_all_primes(iter->first,iter->second,primes);
		iter++;
	}
	return 0;
}

