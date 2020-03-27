#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;
int min;
double avg;

void *max_func(int *array)
{
	max = array[1];
	for (int i = 1; i < array[0]; i++)
	{
		if(array[i] > max)
			max = array[i];
	}
	pthread_exit(0);
}
void *min_func(int *array)
{
	min = array[1];
	for (int i = 1; i < array[0]; i++)
	{
		if(array[i] < min)
			min = array[i];
	}
	pthread_exit(0);
}
void *avg_func(int *array)
{
	double temp = 0;
	for (int i = 1; i < array[0]; i++)
	{
		temp += (double)array[i];
	}
	avg = temp / (double)(array[0] - 1);
	pthread_exit(0);
}

int main(int argc, char const *argv[])
{
	pthread_t tid[3];
	pthread_attr_t attr;

	pthread_attr_init(&attr);

	int *num_array = malloc((argc + 1) * sizeof(int));
	num_array[0] = argc;
	for(int i = 1; i < argc; i++)
		num_array[i] = atoi(argv[i]);

	pthread_create(&tid[0], &attr, max_func, num_array);
	pthread_create(&tid[1], &attr, min_func, num_array);
	pthread_create(&tid[2], &attr, avg_func, num_array);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

	printf("the average value is %lf\n", avg);
	printf("the minimum value is %d\n", min);
	printf("the maximum value is %d\n", max);
	 
	return 0;
}
