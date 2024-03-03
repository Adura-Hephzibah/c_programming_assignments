#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_ROUTERS 7

// Structure to represent an edge
/**
 * struct Edge - struct to represent a edge
 * @dest: name router
 * @weight: edges of the node
 */
struct Edge
{
	char dest;
	int weight;
};


/**
 * struct Node - struct to represent a node
 * @name: name router
 * @edges: edges of the node
 * @num_edges: num of edges the node has
 */
struct Node
{
	char name;
	struct Edge *edges;
	int num_edges;
};

// Structure to represent a graph
struct Graph
{
	struct Node *nodes[NUM_ROUTERS];
	int num_nodes;
};


/**
 * createNode - Function to create a new node
 * @name: argument
 * @num_edges: argument
 *
 * Return: p
 */
struct Node *createNode(char name, int num_edges)
{
	struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
	newNode->name = name;
	newNode->edges = (struct Edge *)malloc(num_edges * sizeof(struct Edge)); // Allocate memory for edges
	newNode->num_edges = 0;													 // Initialize num_edges to 0
	return newNode;
}

/**
 * addEdge - Function to add an edge to a node
 * @node: argument
 * @dest: argument
 * @weight: argument
 *
 * Return: p
 */
void addEdge(struct Node *node, char dest, int weight)
{
	node->edges[node->num_edges].dest = dest;
	node->edges[node->num_edges].weight = weight;
	node->num_edges++;
}


/**
 * createGraph - Function to create a new graph
 *
 * Return: Always 0 (Success)
 */
struct Graph *createGraph()
{
	struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
	graph->num_nodes = 0;
	return graph;
}


/**
 * addNode - Function to add a node to the graph
 * @graph: argument
 * @name: argument
 * @num_edges: argument
 * @destinations: argument
 * @weights: argument
 *
 * Return: p
 */
void addNode(struct Graph *graph, char name, int num_edges,
			 char *destinations, int *weights)
{
	struct Node *newNode = createNode(name, num_edges);

	graph->nodes[graph->num_nodes++] = newNode;
	for (int i = 0; i < num_edges; i++)
	{
		addEdge(newNode, destinations[i], weights[i]);
	}
}

/**
 * findNodeIndex - Function to find the index of a node in the graph
 * @graph: The graph
 * @name: argument
 *
 * Return: p
 */
int findNodeIndex(struct Graph *graph, char name)
{
	for (int i = 0; i < graph->num_nodes; i++)
	{
		if (graph->nodes[i]->name == name)
		{
			return (i);
		}
	}
	return (-1);
}

/**
 * dijkstra - Function to perform Dijkstra's algorithm
 * @graph: The graph
 * @start: the router to start from
 * @end: the router to end at
 *
 * Return: print the path
 */
void dijkstra(struct Graph *graph, char start, char end)
{
	int distances[NUM_ROUTERS];
	int visited[NUM_ROUTERS];

	/* Initialize distances and visited array */
	for (int i = 0; i < NUM_ROUTERS; i++)
	{
		distances[i] = INT_MAX;
		visited[i] = 0;
	}

	/* Find the index of the start node */
	int startIdx = findNodeIndex(graph, start);

	distances[startIdx] = 0;

	/* Dijkstra's algorithm */
	for (int count = 0; count < NUM_ROUTERS - 1; count++)
	{
		/* Find the node with the minimum distance */
		int minDist = INT_MAX;
		int minIdx;

		for (int i = 0; i < NUM_ROUTERS; i++)
		{
			if (!visited[i] && distances[i] < minDist)
			{
				minDist = distances[i];
				minIdx = i;
			}
		}

		/* Mark the selected node as visited */
		visited[minIdx] = 1;

		/* Stop when the shortest path to the end router is found */
		if (graph->nodes[minIdx]->name == end)
		{
			printf("Shortest path from %c to %c is %d\n",
				   start, end, distances[minIdx]);
			return;
		}

		/* Update distances for adjacent nodes */
		for (int i = 0; i < graph->nodes[minIdx]->num_edges; i++)
		{
			int neighborIdx = findNodeIndex(graph, graph->nodes[minIdx]->edges[i].dest);

			if (!visited[neighborIdx] && distances[minIdx] != INT_MAX &&
				distances[minIdx] + graph->nodes[minIdx]->edges[i].weight <
					distances[neighborIdx])
			{
				distances[neighborIdx] = distances[minIdx] +
										 graph->nodes[minIdx]->edges[i].weight;
			}
		}
	}

	printf("No path from %c to %c\n", start, end);
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	struct Graph *graph = createGraph();

	/* Add nodes and edges to the graph */
	addNode(graph, 'A', 3, (char[]){'B', 'C', 'D'}, (int[]){4, 2, 8});
	addNode(graph, 'B', 2, (char[]){'A', 'F'}, (int[]){4, 3});
	addNode(graph, 'C', 3, (char[]){'A', 'E', 'G'}, (int[]){2, 3, 6});
	addNode(graph, 'D', 3, (char[]){'A', 'F', 'G'}, (int[]){8, 1, 3});
	addNode(graph, 'E', 2, (char[]){'E', 'G'}, (int[]){3, 2});
	addNode(graph, 'F', 3, (char[]){'B', 'D', 'G'}, (int[]){3, 1, 4});
	addNode(graph, 'G', 4, (char[]){'C', 'D', 'E', 'F'}, (int[]){6, 3, 2, 4});

	/* Print adjacency list representation of the graph */
	printf("Adjacency List Representation of the Graph:\n");
	for (int i = 0; i < graph->num_nodes; i++)
	{
		printf("%c -> ", graph->nodes[i]->name);
		for (int j = 0; j < graph->nodes[i]->num_edges; j++)
		{
			printf("(%c, %d) ", graph->nodes[i]->edges[j].dest,
				   graph->nodes[i]->edges[j].weight);
		}
		printf("\n");
	}

	/* Perform Dijkstra's algorithm */
	dijkstra(graph, 'A', 'G');

	return (0);
}
