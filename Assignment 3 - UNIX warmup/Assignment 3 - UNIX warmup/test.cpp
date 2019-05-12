#define HAVE_STRUCT_TIMESPEC
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#define NUMBER_OF_THREADS 5 //number of threads
#define MAX_ARRAY 5000 //size of array

int TOTAL = 0;//create global variable total 
int arrayA[MAX_ARRAY];//declare global array of 5000 integers
pthread_mutex_t sum_mutex;//declare semaphore variable

using namespace std;
void *sum_array(void *threadID)
{
	long tid;
	tid = (long)threadID;

	/*Lock the mutex and update the global sum*/
	pthread_mutex_lock(&sum_mutex);

	//each thread computes sum of the values
	//in the range (tid-1)*1000 to (tid*1000 -1)

	for (int i = (tid * 1000); i < ((tid + 1) * 1000); i++)
		TOTAL += arrayA[i];

	//unlock to release access to TOTAL
	pthread_mutex_unlock(&sum_mutex);
	pthread_exit(0);
}

int main(int argc, char*argv[])
{
	//declare an array of threads
	pthread_t threads[NUMBER_OF_THREADS];
	pthread_mutex_init(&sum_mutex, NULL);//initialized mutex

	//initialized global array
	for (int i = 0; i < MAX_ARRAY; i++)
		arrayA[i] = i + 1;

	//create 5 threads
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, sum_array, (void*)i);

	//join 5 threads, waiting for all 5 threads to complete
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], NULL);

	cout << "Total sum from 1 to 5000 is " << TOTAL << endl;

	/*debugging
	int total = 0;
	for (int i = 0; i < MAX_ARRAY; i++)
		total += arrayA[i];
	cout << "Total sum using c++ is " << total << endl;
	*/
	pthread_mutex_destroy(&sum_mutex);

	return 0;
}