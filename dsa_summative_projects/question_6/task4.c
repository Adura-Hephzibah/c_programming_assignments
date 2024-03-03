#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

/**
 * struct Priority_Queue - struct to represent a student
 * @heap: data
 * @size: data
 */
typedef struct Priority_Queue
{
	int heap[MAX_HEAP_SIZE];
	int size;
} Priority_Queue;

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
 * heapify_up - Maintain heap property by moving a node up the heap.
 * @pq: Pointer to the priority queue.
 * @index: Index of the node to heapify.
 */
void heapify_up(Priority_Queue *pq, int index)
{
	int parent = (index - 1) / 2;

	if (index > 0 && pq->heap[index] > pq->heap[parent])
	{
		swap(&pq->heap[index], &pq->heap[parent]);
		heapify_up(pq, parent);
	}
}

/**
 * enqueue - Insert an element into the priority queue.
 * @pq: Pointer to the priority queue.
 * @value: Value to be inserted.
 */
void enqueue(Priority_Queue *pq, int value)
{
	if (pq->size >= MAX_HEAP_SIZE)
	{
		printf("Priority Queue is full\n");
		return;
	}
	pq->heap[pq->size++] = value;
	heapify_up(pq, pq->size - 1);
}

/**
 * heapify_down - Maintain heap property by moving a node down the heap.
 * @pq: Pointer to the priority queue.
 * @index: Index of the node to heapify.
 */
void heapify_down(Priority_Queue *pq, int index)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int largest = index;

	if (left < pq->size && pq->heap[left] > pq->heap[largest])
		largest = left;

	if (right < pq->size && pq->heap[right] > pq->heap[largest])
		largest = right;

	if (largest != index)
	{
		swap(&pq->heap[index], &pq->heap[largest]);
		heapify_down(pq, largest);
	}
}

/**
 * dequeue - Remove and return the maximum element from the priority queue.
 * @pq: Pointer to the priority queue.
 *
 * Return: Maximum element in the priority queue.
 */
int dequeue(Priority_Queue *pq)
{
	if (pq->size == 0)
	{
		printf("Priority Queue is empty\n");
		return (-1);
	}
	int max = pq->heap[0];

	pq->heap[0] = pq->heap[--pq->size];
	heapify_down(pq, 0);
	return (max);
}

/**
 * display - Display the elements of the priority queue.
 * @pq: Pointer to the priority queue.
 */
void display(Priority_Queue *pq)
{

	if (pq->size == 0)
	{
		printf("Empty Queue\n");
	} else
	{
	printf("Priority Queue: ");
	for (int i = 0; i < pq->size; ++i)
	{
		printf("%d ", pq->heap[i]);
	}
	printf("\n");
	}

}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	Priority_Queue pq = { .size = 0 };

	display(&pq);

	enqueue(&pq, 10);
	enqueue(&pq, 20);
	enqueue(&pq, 15);
	enqueue(&pq, 30);
	enqueue(&pq, 25);
	enqueue(&pq, 5);

	display(&pq);

	printf("Dequeue: %d\n", dequeue(&pq));

	display(&pq);

	printf("Dequeue: %d\n", dequeue(&pq));
	display(&pq);

	enqueue(&pq, 80);
	display(&pq);

	return (0);
}
