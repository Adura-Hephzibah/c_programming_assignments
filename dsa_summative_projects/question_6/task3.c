#include <stdio.h>

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
	int arr[] = {12, 11, 13, 5, 6, 7, 3, 37};
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Original array: ");
	print_array(arr, n);

	build_min_heap(arr, n);

	printf("Min heap: ");
	print_array(arr, n);

	return (0);
}
