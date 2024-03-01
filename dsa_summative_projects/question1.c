#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * merge - function to merge two sub arrays
 * @arr: array
 * @left: left indice
 * @middle: middle indice
 * @right: right index
 * Return:
 */
void merge(char **arr, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	char **L = (char **)malloc(n1 * sizeof(char *));
	char **R = (char **)malloc(n2 * sizeof(char *));

	for (i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2)
	{
		if (strcmp(L[i], R[j]) <= 0)
		{
			arr[k] = L[i];
			i++;
		} else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	/* Free memory */
	free(L);
	free(R);
}

/**
 * mergeSort - function to recursively sort the array
 * @arr: array
 * @left: left indice
 * @right: right index
 * Return:
 */
void mergeSort(char **arr, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

/**
 * bubbleSort - Bubble sort algorithm
 * @arr: array
 * @n: integer
 * Return: A
 */
void bubbleSort(char **arr, int n)
{
	int i, j;
	for (i = 0; i < n-1; i++)
	{
		for (j = 0; j < n-i-1; j++)
		{
			if (strcmp(arr[j], arr[j+1]) > 0)
			{
				char *temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *usernames[] = {"john", "xavier", "abissa", "ricardo",
										"chris", "almarat", "kolade", "lisa", "abib", "lex"};
	int num_usernames = sizeof(usernames) / sizeof(usernames[0]);

	// Measure merge sort running time
	clock_t start = clock();
	mergeSort(usernames, 0, num_usernames - 1);
	clock_t end = clock();
	double merge_sort_time = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Sorted usernames using Merge Sort:\n");
	for (int i = 0; i < num_usernames; i++)
	{
		printf("%s\n", usernames[i]);
	}
	printf("Merge Sort Running Time: %.6f seconds\n\n", merge_sort_time);

	/* Generate 10,000 random usernames (for bubble sort comparison) */
	const int num_usernames_10000 = 10000;
	char *usernames_10000[num_usernames_10000];
	srand(time(NULL)); /* Seed the random number generator */
	for (int i = 0; i < num_usernames_10000; i++) {
		char buffer[10];
		snprintf(buffer, sizeof(buffer), "user%d", rand() % 10000);
		usernames_10000[i] = strdup(buffer);
	}

	/* Measure bubble sort running time for 10,000 usernames */
	start = clock();
	bubbleSort(usernames_10000, num_usernames_10000);
	end = clock();
	double bubble_sort_time = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Bubble Sort Running Time for 10,000 usernames: %.6f seconds\n", bubble_sort_time);

	/* Free memory for 10,000 usernames */
	for (int i = 0; i < num_usernames_10000; i++) {
		free(usernames_10000[i]);
	}


	return (0);
}
