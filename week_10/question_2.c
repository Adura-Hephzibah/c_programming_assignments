/**
 * Question 2.
 * You have an array of 100 elements which are required to be summed up
 * together while observing the system performance.
 * In order to maximize the performance,
 * your program will have 2 threads that are dividing the array
 * into two halves such that one thread handles one half and
 * then the second thread handles the remaining halve concurrently.
 *
 * Tasks to be completed
 * - Each thread will take part of the array and add all elements in it.
 * - The values computed by both threads will be added together
 * - to print the sum of the entire array.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
int array[SIZE];

/**
 * ThreadData - typedef for struct SensorData
 */
typedef struct ThreadData ThreadData;

/**
 * struct ThreadData - struct for ThreadData
 * @start: start of array
 * @end: end of array
 * @result: sum of array
 */
struct ThreadData
{
	int start;
	int end;
	int result;
};


/**
 * sum_of_array - function to run in each thread
 * @arg: argument pointer
 * Return: void
 */
void *sum_of_array(void *arg)
{
	ThreadData *data = (ThreadData *)arg;

	data->result = 0;

	for (int i = data->start; i < data->end; ++i)
	{
		data->result += array[i];
	}
	pthread_exit(NULL);
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	/* Initialize the random number generator */
	srand(time(NULL));

	/* Initialize the array with random numbers */
	for (int i = 0; i < SIZE; ++i)
	{
		array[i] = rand() % 100 + 1;  /* Generate a random number between 1 and 100*/
		/* printf("%d, ", array[i]); */
	}

	/* Create two threads */
	pthread_t t1, t2;
	ThreadData data1 = {0, SIZE / 2, 0};
	ThreadData data2 = {SIZE / 2, SIZE, 0};

	pthread_create(&t1, NULL, sum_of_array, &data1);
	pthread_create(&t2, NULL, sum_of_array, &data2);

	/* Wait for both threads to finish */
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	/* Print the sum of the individual threads and entire array*/
	printf("Sum of the first thread: %d\n", data1.result);
	printf("Sum of the second thread: %d\n", data2.result);
	printf("Sum of the entire array: %d\n", data1.result + data2.result);

	return (0);
}
