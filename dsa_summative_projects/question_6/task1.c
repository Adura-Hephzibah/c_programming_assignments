#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

/**
 * struct Heap - struct to represent a student
 * @elements: data
 * @size: data
 */
typedef struct Heap
{
	int elements[MAX_HEAP_SIZE];
	int size;
} Heap;

/**
 * swap - Function to swap
 * @a: argument
 * @b: argument
 *
 * Return: void
 */
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * heapify_up - Function to heapify up
 * @heap: The heap
 * @index: index
 *
 * Return: void
 */
void heapify_up(Heap *heap, int index)
{
	int parent = (index - 1) / 2;

	if (index > 0 && heap->elements[index] < heap->elements[parent])
	{
		swap(&heap->elements[index], &heap->elements[parent]);
		heapify_up(heap, parent);
	}
}

/**
 * insert - Function to insert node
 * @heap: The heap
 * @value: value to insert
 *
 * Return: void
 */
void insert(Heap *heap, int value)
{
	if (heap->size >= MAX_HEAP_SIZE)
	{
		printf("Heap is full\n");
		return;
	}
	heap->elements[heap->size++] = value;
	heapify_up(heap, heap->size - 1);
}

/**
 * heapify_down - Function to heapify down
 * @heap: The heap
 * @index: index
 *
 * Return: void
 */
void heapify_down(Heap *heap, int index)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int smallest = index;

	if (left < heap->size && heap->elements[left] < heap->elements[smallest])
	{
		smallest = left;
	}
	if (right < heap->size && heap->elements[right] < heap->elements[smallest])
	{
		smallest = right;
	}
	if (smallest != index)
	{
		swap(&heap->elements[index], &heap->elements[smallest]);
		heapify_down(heap, smallest);
	}
}

/**
 * delete_root - Function to delete
 * @heap: The heap
 *
 * Return: void
 */
void delete_root(Heap *heap)
{
	if (heap->size == 0)
	{
		printf("Heap is empty\n");
		return;
	}
	heap->elements[0] = heap->elements[--heap->size];
	heapify_down(heap, 0);
}

/**
 * display - Function to display heap
 * @heap: The heap
 *
 * Return: print the heap
 */
void display(Heap *heap)
{
	printf("Heap: ");
	for (int i = 0; i < heap->size; ++i)
	{
		printf("%d ", heap->elements[i]);
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
	Heap heap = { .size = 0 };

	insert(&heap, 10);
	insert(&heap, 20);
	insert(&heap, 15);
	insert(&heap, 30);
	insert(&heap, 25);
	insert(&heap, 5);

	display(&heap);

	insert(&heap, 2);

	display(&heap);

	delete_root(&heap);

	display(&heap);

	return (0);
}
