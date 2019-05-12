#define HAVE_STRUCT_TIMESPEC
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<iostream>
#include<array>

#define NUMBER_OF_THREADS 5 //number of threads
#define MAX_ARRAY 5000 //size of array

//extern int arrayA[];//declare a global array 
int TOTAL = 0;//create global variable total 
int arrayA[MAX_ARRAY];//define global array of 5000 integers
//int sum[5] = { 0 };
int global_index = 0;
pthread_mutex_t mutex1;

using namespace std;
void *sum_array(void *threadID)
{
	long tid;
	tid = (long)threadID;

	pthread_mutex_lock(&mutex1);

	//each thread computes sum of the values
	//in the range (tid-1)*1000 to (tid*1000 -1)

	for (int i = (tid * 1000); i < ((tid + 1) * 1000); i++)
		TOTAL += arrayA[i];

	//int local_index, partial_sum = 0;
	//do {
	//	pthread_mutex_lock(&mutex1);
	//	local_index = global_index;
	//	global_index++;
	//	pthread_mutex_unlock(&mutex1);

	//	if (local_index < MAX_ARRAY)
	//		partial_sum += *(arrayA + local_index);
	//} while (local_index < MAX_ARRAY);

	//pthread_mutex_lock(&mutex1);
	//TOTAL += partial_sum;
	//pthread_mutex_unlock(&mutex1); //release access to mutex


	/*Lock the mutex and update the global sum*/
	
	pthread_mutex_unlock(&mutex1);

	return 0;
}

//void* sum_array(void * threadID);
int main(int argc, char*argv[])
{
	//declare an array of threads
	pthread_t threads[NUMBER_OF_THREADS];
	pthread_mutex_init(&mutex1, NULL);

	//initialized global array
	for (int i = 1; i <= MAX_ARRAY; i++)
		arrayA[i] = i;

	//create 5 threads
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, sum_array, (void*)i);

	//join 5 threads, waiting for all 5 threads to complete
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], NULL);

	//adding sum of all 5 parts
	/*for (i = 0; i < NUMBER_OF_THREADS; i++)
		TOTAL += sum[i];*/

	cout << "sum is " << TOTAL << endl;

	return 0;
}

/*
void* sum_array(void * threadID)
{
	long tid;
	tid = (long)threadID;
	//each thread computes sum of the values
	//in the range (tid-1)*1000 to (tid*1000 -1)

	for (int i = (tid * 1000); i < ((tid+1) * 1000); i++)
		sum[tid] += arrayA[i];
}*/