#define HAVE_STRUCT_TIMESPEC
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<iostream>
#include<vector>
#include <chrono> 

#define NUMBER_OF_THREADS 4 //number of threads
#define MAX 10000

auto MatrixA = new float[MAX][MAX];
auto MatrixB = new float[MAX][MAX];
auto MatrixC = new float[MAX][MAX];

using namespace std;
using namespace std::chrono;

void *multiply(void *threadID)
{
	long tid;
	tid = (long)threadID;

	//each thread computes 1/4 of the matrix
	for (int i = tid * MAX / 4; i < (tid + 1) * MAX / 4; i++) {
		for (int j = 0; j < MAX; j++) {
			MatrixC[i][j] = 0; // initialize matrix C
			for (int k = 0; k < MAX; k++)
				MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
		}
	}
	pthread_exit(0);
}

int main() {

	//int start = clock();
	auto start = high_resolution_clock::now();

	//declare 4 threads
	pthread_t threads[NUMBER_OF_THREADS];

	int rowNum, colNum;
	float rowVal, colVal;

	// Generating random values in MatrixA and MatrixB
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			MatrixA[i][j] = ((double)rand() / (RAND_MAX));
			MatrixB[i][j] = ((double)rand() / (RAND_MAX));
		}
	}
	cin >> rowNum >> rowVal >> colNum >> colVal;

	// The first matrix will change all the elements of the
	// row to the new input value
	for (int i = 0; i < MAX; i++)
		MatrixA[rowNum][i] = rowVal;

	// second matrix will change all the elements of the column to
	// new input value

	for (int i = 0; i < MAX; i++)
		MatrixB[i][colNum] = colVal;

	// Creating four threads, each evaluating its own part 
	for (int i = 0; i < NUMBER_OF_THREADS; i++) {
		pthread_create(&threads[i], NULL, multiply, (void*)i);
	}

	// join 4 threads and wait for all threads to complete 
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], NULL);

	cout << "The array results are: \n";
	cout << "[" << rowNum-1 << "]" << " " << "[" << colNum << "]" << " " << MatrixC[rowNum-1][colNum] << endl;
	cout << "[" << rowNum << "]" << " " << "[" << colNum-1 << "]" << " " << MatrixC[rowNum][colNum-1] << endl;
	cout << "[" << rowNum << "]" << " " << "[" << colNum << "]" << " " << MatrixC[rowNum][colNum] << endl;
	cout << "[" << rowNum << "]" << " " << "[" << colNum+1 << "]" << " " << MatrixC[rowNum][colNum+1] << endl;
	cout << "[" << rowNum+1 << "]" << " " << "[" << colNum << "]" << " " << MatrixC[rowNum+1][colNum] << endl;
	//int stop = clock();
	auto stop = high_resolution_clock::now();
	//cout << "Processing time of the array multiplication was " << (stop - start) / double(CLOCKS_PER_SEC) * 1000 << endl;
	
	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Processing time of the array multiplication was "
		<< duration.count() << " milliseconds" << endl;

	delete[]MatrixA;
	delete[] MatrixB;
	delete[] MatrixC;
	return 0;
}