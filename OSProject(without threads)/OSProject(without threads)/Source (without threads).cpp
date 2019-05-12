#include<iostream>
#include<vector>
#include <chrono> 

#define MAX 10000

auto MatrixA = new float[MAX][MAX];
auto MatrixB = new float[MAX][MAX];
auto MatrixC = new float[MAX][MAX];

using namespace std;
using namespace std::chrono;

void multiply()
{
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			MatrixC[i][j] = 0; // initialize matrix C
			for (int k = 0; k < MAX; k++)
				MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
		}
	}
}

int main() {
	auto start = high_resolution_clock::now();

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
	
	multiply();

	cout << "The array results are: \n";
	cout << "[" << rowNum - 1 << "]" << " " << "[" << colNum << "]" << " " << MatrixC[rowNum - 1][colNum] << endl;
	cout << "[" << rowNum << "]" << " " << "[" << colNum - 1 << "]" << " " << MatrixC[rowNum][colNum - 1] << endl;
	cout << "[" << rowNum << "]" << " " << "[" << colNum << "]" << " " << MatrixC[rowNum][colNum] << endl;
	cout << "[" << rowNum << "]" << " " << "[" << colNum + 1 << "]" << " " << MatrixC[rowNum][colNum + 1] << endl;
	cout << "[" << rowNum + 1 << "]" << " " << "[" << colNum << "]" << " " << MatrixC[rowNum + 1][colNum] << endl;

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Processing time of the array multiplication was "
		<< duration.count() << " milliseconds" << endl;

	delete[]MatrixA;
	delete[] MatrixB;
	delete[] MatrixC;
	return 0;
}