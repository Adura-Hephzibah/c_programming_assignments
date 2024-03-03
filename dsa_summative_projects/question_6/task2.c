#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * swap - Swaps two integers.
 *
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
 * heapify - Maintains the heap property at a given index in the array.
 *
 * @arr: Array representing the heap.
 * @n: Size of the heap.
 * @i: Index to start heapify from.
 */
void heapify(int arr[], int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	/* Find the largest element among root, left child, and right child */
	if (left < n && arr[left] > arr[largest])
		largest = left;

	if (right < n && arr[right] > arr[largest])
		largest = right;

	/*If largest is not root, swap it with the root and recursively heapify*/
	if (largest != i)
	{
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

/**
 * build_max_heap - Builds a max heap from an array of elements.
 *
 * @arr: Array of elements.
 * @n: Size of the array.
 */
void build_max_heap(int arr[], int n)
{
	/* Build max heap from the last non-leaf node */
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}
}

/**
 * print_array - Prints the elements of an array
 * @arr: Array to be printed.
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
		arr[i] = rand() % 100; /*Random integers between 0 and 99*/
		printf("%d ", arr[i]);
	}
	printf("\n");

	build_max_heap(arr, n);

	printf("Max heap: ");
	print_array(arr, n);

	/*------------------------------------------*/

	int sorted_arr[] = {3, 5, 6, 8, 10, 11, 12};
	int n2 = sizeof(sorted_arr) / sizeof(sorted_arr[0]);

	printf("Sorted array: ");
	print_array(sorted_arr, n2);

	build_max_heap(sorted_arr, n2);

	printf("Max heap: ");
	print_array(sorted_arr, n2);

	return (0);
}
