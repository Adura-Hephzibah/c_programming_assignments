#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * swap - Swap two integers.
 * @a: Pointer to the first integer.
 * @b: Pointer to the second integer.
 */
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * heapify - Maintain min heap property starting from a given index.
 * @arr: Array representing the heap.
 * @n: Size of the heap.
 * @i: Index to start heapifying from.
 */
void heapify(int arr[], int n, int i)
{
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	/*Find the smallest element among root, left child, and right child*/
	if (left < n && arr[left] < arr[smallest])
		smallest = left;

	if (right < n && arr[right] < arr[smallest])
		smallest = right;

	/*If smallest is not root, swap it with the root and recursively heapify*/
	if (smallest != i)
	{
		swap(&arr[i], &arr[smallest]);
		heapify(arr, n, smallest);
	}
}

/**
 * build_min_heap - Build a min heap from an array.
 * @arr: Array of integers.
 * @n: Size of the array.
 */
void build_min_heap(int arr[], int n)
{
	/* Build min heap from the last non-leaf node */
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}
}

/**
 * print_array - Print the elements of an array.
 * @arr: Array of integers.
 * @n: Size of the array.
 */
void print_array(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	/* Seed for random number generation */
	srand(time(NULL));

	/* Generate a random array */
	int n = 10; /* Size of the array */
	int arr[n];

	printf("Random array: ");
	for (int i = 0; i < n; ++i)
	{
		arr[i] = rand() % 100; /* Random integers between 0 and 99 */
		printf("%d ", arr[i]);
	}
	printf("\n");

	build_min_heap(arr, n);

	printf("Min heap: ");
	print_array(arr, n);

	/*------------------------------------------*/

	int sorted_arr[] = {12, 11, 10, 8, 6, 5, 3};
	int n2 = sizeof(sorted_arr) / sizeof(sorted_arr[0]);

	printf("Original sorted array: ");
	print_array(sorted_arr, n2);
	build_min_heap(sorted_arr, n2);

	printf("Min heap: ");
	print_array(sorted_arr, n2);
	return (0);
}
