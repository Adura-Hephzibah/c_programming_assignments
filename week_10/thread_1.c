/**
 * Q1.
 *
 * Sam has installed one big green house which was divided into four sections.
 * The intention to optimize resources in a sense that environmental
 * and water management are happening only in the required section instead
 * of unneeded controls that may waste some resources.
 *
 * In each section Sam is using 3 sensors which are temperature,
 * humidity and soil moisture.
 * Sam is designing one node with the three sensors for each section,
 * the three values returned in each section will be consolidated
 * in one structure such that values for all sections are presented
 * on Sam's big screen.
 *
 * Tasks to be completed
 * Write a C program that will be using threads to complete the work.
 * Collecting data for each section will be handled by a respective thread
 * but all threads will be running concurrently
 *
 * Your program will display values returned from different
 * sections of the green house in the following format:
 *
 * Section 1. Temp:[value], Hum: [value], Soil Mois:[value]
 * Section 2. Temp:[value], Hum: [value], Soil Mois:[value]
 * Section 3. Temp:[value], Hum: [value], Soil Mois:[value]
 * Section 4. Temp:[value], Hum: [value], Soil Mois:[value]
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

/**
 * SensorData - typedef for struct SensorData
 */
typedef struct SensorData SensorData;

/**
 * struct SensorData - struct for SensorData
 * @section: section
 * @temp: temperature
 * @hum: humidity
 * @soil_mois: Soil Moisture
 */
struct SensorData
{
	int section;
	int temp;
	int hum;
	int soil_mois;
};

/**
 * data_collection - function to run in each thread
 * @arg: argument pointer
 * Return: void
 */
void *data_collection(void *arg)
{
	SensorData *data = (SensorData *)arg;

	data->temp = rand() % 51;
	data->hum = rand() % 101;
	data->soil_mois = rand() % 1024;

	printf("Section %d. Temp:%d, Hum: %d, Soil Mois:%d\n",
			data->section, data->temp, data->hum, data->soil_mois);
	pthread_exit(NULL);
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	srand(time(NULL));
	pthread_t threads[NUM_THREADS];
	SensorData sensor_data_array[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++)
	{
		sensor_data_array[i].section = i + 1;
		int create_status = pthread_create(&threads[i], NULL,
									data_collection, (void *)&sensor_data_array[i]);

		if (create_status)
		{
			printf("Error: Unable to create thread, %d\n", create_status);
			exit(-1);
		}
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}

	return (0);
}
