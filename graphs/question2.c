#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Define maximum number of vertices in the graph */
#define MAX_VERTICES 10

/**
 * struct Node - struct to represent a node in the adjacency list
 * @data: data
 * @next: pointer to next node
 */
struct Node
{
	int data;
	struct Node *next;
};


/**
 * struct Graph - struct to represent the graph
 * @numVertices: number of vertices
 * @adjList: adjancency Lists
 */
struct Graph
{
	int numVertices;
	/* Increase array size to accommodate vertices starting from 1*/
	struct Node *adjList[MAX_VERTICES + 1];
};


/**
 * createNode - function to create a new node
 * @data: argument
 * Return: value
 */
struct Node *createNode(int data)
{
	struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

	newNode->data = data;
	newNode->next = NULL;
	return (newNode);
}

/**
 * createGraph - function to create a graph with the specified
 * number of vertices
 * @vertices: argument
 * Return: value
 */
struct Graph *createGraph(int vertices)
{
	struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));

	graph->numVertices = vertices;

	/* Initialize adjacency list for all vertices */
	for (int i = 1; i <= vertices; ++i)
		graph->adjList[i] = NULL;

	return (graph);
}


/**
 * addEdge - function to add an edge to the graph
 * @graph: argument pointer
 * @src: argument
 * @dest: argument
 * Return:
 */
void addEdge(struct Graph *graph, int src, int dest)
{
	struct Node *newNode = createNode(dest);

	newNode->next = graph->adjList[src];
	graph->adjList[src] = newNode;

	/* Since the graph is undirected, add an edge from dest to src as well*/
	newNode = createNode(src);
	newNode->next = graph->adjList[dest];
	graph->adjList[dest] = newNode;
}

/**
 * BFS - function to perform Breadth First Search (BFS)
 * @graph: argument pointer
 * @startVertex: argument pointer
 * Return:
 */
void BFS(struct Graph *graph, int startVertex)
{
	bool visited[MAX_VERTICES + 1] = { false }; /* Initialize visited array */
	int queue[MAX_VERTICES]; /* Queue for BFS */
	int front = 0, rear = 0; /* Front and rear pointers for the queue */

	visited[startVertex] = true; /* Mark the start vertex as visited */
	queue[rear++] = startVertex; /* Enqueue the start vertex */

	printf("BFS Traversal: ");

	while (front < rear)
	{
		int currentVertex = queue[front++];

		printf("%d ", currentVertex);

		/* Traverse all the adjacent vertices of the current vertex*/
		struct Node *temp = graph->adjList[currentVertex];

		while (temp)
		{
			int adjVertex = temp->data;

			if (!visited[adjVertex])
			{
				visited[adjVertex] = true;
				queue[rear++] = adjVertex;
			}
			temp = temp->next;
		}
	}
}

/**
 * DFSUtil - function to perform Depth First Search (DFS)
 * @graph: argument pointer
 * @vertex: argument
 * @visited: argument
 * Return:
 */
void DFSUtil(struct Graph *graph, int vertex, bool visited[])
{
	visited[vertex] = true;
	printf("%d ", vertex);

	/* Traverse all the adjacent vertices of the current vertex */
	struct Node *temp = graph->adjList[vertex];

	while (temp)
	{
		int adjVertex = temp->data;

		if (!visited[adjVertex])
		{
			DFSUtil(graph, adjVertex, visited);
		}
		temp = temp->next;
	}
}

/**
 * DFS - function to do DFS
 * @graph: argument pointer
 * @startVertex: argument pointer
 * Return:
 */
void DFS(struct Graph *graph, int startVertex)
{
	bool visited[MAX_VERTICES + 1] = { false };

	printf("DFS Traversal: ");
	DFSUtil(graph, startVertex, visited);
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int vertices = 10;

	/* Create a graph with 6 vertices */
	struct Graph *graph = createGraph(vertices);

	/* Add edges */
	addEdge(graph, 1, 3);
	addEdge(graph, 1, 4);
	addEdge(graph, 1, 5);
	addEdge(graph, 1, 8);
	addEdge(graph, 2, 8);
	addEdge(graph, 3, 7);
	addEdge(graph, 5, 6);
	addEdge(graph, 6, 9);

	/* Perform BFS starting from vertex 1 */
	BFS(graph, 1);
	printf("\n");

	/* Perform DFS starting from vertex 1*/
	DFS(graph, 1);
	printf("\n");

	return (0);
}
