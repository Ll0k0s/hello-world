#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int N = 10000;
#define M 40
//const int M = 100;
int cnt[M];

struct list
{
	pthread_t my_thread
	int array;
	int lost;
}

void *thread_function(void *arg);

int main(void)
{
	pthread_t my_thread[M];

	for(int i = 0; i < M; i++){
		pthread_create(&my_thread[i], NULL, *thread_function, (void*)&i);
	}

	for(int i = 0; i < M; i++){
		pthread_join(my_thread[i], NULL);
	}

	printf("True result = %i\n", N);

	for(int i = 0; i < M; i++){
		int lost = (N - cnt[i]) * 100 / N;
		printf("cnt[%i] = %i\tlost = %i %\n", i, cnt[i], lost);
	}
	return 0;
}
void *thread_function(void *arg)
{
	for (int i; i < N; i++){
		cnt[*((int *)arg)]++;
		//usleep(1);
	}
}
