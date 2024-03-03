#include <stdio.h>

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
	int arr[] = {12, 11, 13, 5, 6, 7, 80, 43};
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Original array: ");
	print_array(arr, n);

	build_max_heap(arr, n);

	printf("Max heap: ");
	print_array(arr, n);

	return (0);
}
