// May Trinh, Ashma Henry, Marissa Noris
// CMPS 4103 - Final Exam
// Source code of Experiment 2 - with semaphore

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include<iostream>

#define NUM_THREADS 5
pthread_mutex_t mutex;
pthread_cond_t cond[NUM_THREADS];
int COUNTER_MAX = 10;
int COUNTER = 1;

using namespace std;
struct thread_arg
{
	int index;
	pthread_cond_t *wait; //wait condition for each thread
	pthread_cond_t *signal; //signal condition for each thread
};

void* printCounter(void* pArg)
{
	struct thread_arg *threadArg = (struct thread_arg *)pArg;
	int tid = threadArg->index;
	while (COUNTER <= COUNTER_MAX) {

		pthread_mutex_lock(&mutex);
		cout << "Display: " << COUNTER << " Thread: " << tid + 1 << endl;
		COUNTER++;

		//signal the next thread
		pthread_cond_signal(threadArg->signal);

		//wait for turn
		pthread_cond_wait(threadArg->wait, &mutex);
		pthread_mutex_unlock(&mutex);
	}

	cout << "Counter is already 10. Thread " << tid + 1 << endl;
	pthread_cond_signal(threadArg->signal);
	return 0;
}

int main()
{
	//declare threads
	pthread_t threads[NUM_THREADS];

	pthread_mutex_init(&mutex, NULL);
	struct thread_arg threadCond[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_cond_init(&cond[i], NULL);

	//initialize waiting and signaling condition for each thread
	for (int i = 0; i < NUM_THREADS; i++)
	{
		threadCond[i].index = i;
		threadCond[i].wait = &cond[i];
		if (i == NUM_THREADS - 1)
			threadCond[i].signal = &cond[0];
		else
			threadCond[i].signal = &cond[i + 1];

		//create threads with unique wait and signal condition
		pthread_create(&threads[i], NULL, &printCounter, (void*)&threadCond[i]);
	}

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	return 0;
}
