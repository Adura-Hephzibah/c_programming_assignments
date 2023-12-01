#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * compareAscend - Comparison function for ascending order
 * @a: argument pointer
 * @b: argument pointer
 * Return: void
 */
int compareAscend(const void *a, const void *b)
{
	return ((*(int *)a - *(int *)b));
}

/**
 * compareDescend - Comparison function for descending order
 * @a: argument pointer
 * @b: argument pointer
 * Return: void
 */
int compareDescend(const void *a, const void *b)
{
	return ((*(int *)b - *(int *)a));
}


/* Function pointer type for ascending comparison function*/
int (*ascendingOrder)(const void *, const void *) = compareAscend;

/* Function pointer type for descending comparison function*/
int (*descendingOrder)(const void *, const void *) = compareDescend;

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int grades[] = {23, 45, 31, 36, 32, 26, 29, 30, 33, 35, 28, 37, 19, 20};
	int size = sizeof(grades) / sizeof(grades[0]);

	char orderChoice[4];

	/* Get user input for order choice */
	printf("Enter order choice (asc for ascending, desc for descending): ");
	scanf("%s", orderChoice);

	/* index for array of pointer functions */
	int index;

	if (strcmp(orderChoice, "asc") == 0)
		index = 0;

	if (strcmp(orderChoice, "desc") == 0)
		index = 1;

	if (strcmp(orderChoice, "asc") != 0 && strcmp(orderChoice, "desc") != 0)
	{
		printf("Invalid order choice\n");
		return (1);
	}

	int (*fun_ptr_arr[])(const void *, const void *) = {ascendingOrder,
															descendingOrder};

	qsort(grades, size, sizeof(int), fun_ptr_arr[index]);

	/* Display the sorted array */
	printf("Sorted grades: ");
	for (int i = 0; i < size; i++)
		printf("%d ", grades[i]);

	printf("\n");

	return (0);
}
