// May Trinh, Ashma Henry, Marissa Noris
// CMPS 4103 - Final Exam
// Source code of Experiment 1 - without semaphore

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include<iostream>

#define NUM_THREADS 5
int COUNTER_MAX = 10;
int COUNTER = 1;

using namespace std;
void* printCounter(void* pArg)
{
	long tid = (long)pArg;
	while (COUNTER <= COUNTER_MAX) {
		cout << "Display: " << COUNTER << " Thread: " << tid + 1 << endl;
		COUNTER++;
	}
	cout << "Counter is already 10. Thread " << tid + 1 << endl;
	return 0;
}

int main()
{
	//declare threads
	pthread_t threads[NUM_THREADS];

	//create threads
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_create(&threads[i], NULL, &printCounter, (void*)i);

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	return 0;
}
