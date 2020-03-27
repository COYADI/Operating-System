#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int POINT_PER_THREAD = 1000000;
int POINT_IN_CIRCLE  = 0;
int THREAD_CNT = 100;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *runner()
{
	int in_circle = 0;
	srand(time(NULL));
	for (int i = 0; i < POINT_PER_THREAD; i++)
	{
		double x, y;
		int seed;
		x = ((double)(rand_r(&seed) % 201) - 100) / 100;
		y = ((double)(rand_r(&seed) % 201) - 100) / 100;

		//printf("%lf %lf\n", x, y);
		if(x * x + y * y <= 1)
			in_circle++;
	}

	pthread_mutex_lock(&mutex);
	POINT_IN_CIRCLE += in_circle;
	pthread_mutex_unlock(&mutex);

}

int main(int argc, char const *argv[])
{
	double pi;

	pthread_t tid[THREAD_CNT];
	pthread_attr_t attr;

	pthread_attr_init(&attr);

	for(int i = 0; i < THREAD_CNT; i++)
		pthread_create(&tid[i], &attr, runner, NULL);
	for(int i = 0; i < THREAD_CNT; i++)
		pthread_join(tid[i], NULL);

	pi = 4 * (double)POINT_IN_CIRCLE / (THREAD_CNT * POINT_PER_THREAD);
	//printf("%d %d %d\n", POINT_IN_CIRCLE, THREAD_CNT, POINT_PER_THREAD);

	printf("pi = %lf\n", pi); 
	return 0;
}