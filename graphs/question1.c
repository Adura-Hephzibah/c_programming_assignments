#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure to represent a country node */
typedef struct CountryNode
{
	char name[50];
	struct CountryNode *next;
} CountryNode;

/* Structure to represent the graph */
typedef struct Graph
{
	int numVertices;
	CountryNode **adjacencyLists;
} Graph;

/* Function to create a new country node */
CountryNode *createCountryNode(const char *name)
{
	CountryNode *newNode = (CountryNode *)malloc(sizeof(CountryNode));

	strcpy(newNode->name, name);
	newNode->next = NULL;
	return (newNode);
}


/**
 * createGraph - function to create the graph
 * @numVertices: argument
 * Return: graph
 */
Graph createGraph(int numVertices)
{
	Graph graph;

	graph.numVertices = numVertices;

	graph.adjacencyLists = (CountryNode **)malloc(
			numVertices * sizeof(CountryNode *));
	for (int i = 0; i < numVertices; ++i)
	{
		graph.adjacencyLists[i] = NULL;
	}
	return (graph);
}

/**
 * findIndex - function to find the index of a country node in adjacency lists
 * @graph: argument pointer
 * @name: argument pointer
 * Return: i or 1
 */
int findIndex(const Graph *graph, const char *name)
{
	for (int i = 0; i < graph->numVertices; ++i)
	{
		if (strcmp(graph->adjacencyLists[i]->name, name) == 0)
		{
			return (i);
		}
	}
	return (-1);
}

/**
 * addEdge - function to add an edge between two vertices
 * @graph: argument pointer
 * @source: argument pointer
 * @destination: argument pointer
 * Return:
 */
void addEdge(Graph *graph, const char *source, const char *destination)
{
	int sourceIndex = findIndex(graph, source);
	int destinationIndex = findIndex(graph, destination);
	/* If both source and destination exist, add an edge */
	if (sourceIndex != -1 && destinationIndex != -1)
	{
		/* Add destination to the adjacency list of source */
		CountryNode *newNode = createCountryNode(destination);

		newNode->next = graph->adjacencyLists[sourceIndex]->next;
		graph->adjacencyLists[sourceIndex]->next = newNode;
		/*Add source to the adjacency list of destinatn (assuming undirected graph)*/
		newNode = createCountryNode(source);
		newNode->next = graph->adjacencyLists[destinationIndex]->next;
		graph->adjacencyLists[destinationIndex]->next = newNode;
	}
}

/**
 * printGraph - function to print the graph in adjacency list representation
 * @graph: argument pointer
 * Return:
 */
void printGraph(const Graph *graph)
{
	printf("Adjacency List Representation:\n");
	for (int i = 0; i < graph->numVertices; ++i)
	{
		printf("%s -> ", graph->adjacencyLists[i]->name);
		CountryNode *current = graph->adjacencyLists[i]->next;

		while (current != NULL)
		{
			printf("%s ", current->name);
			current = current->next;
		}
		printf("\n");
	}
}

/* Function to delete the graph */
void deleteGraph(Graph *graph)
{
	for (int i = 0; i < graph->numVertices; ++i)
	{
		CountryNode *current = graph->adjacencyLists[i];

		while (current != NULL)
		{
			CountryNode *temp = current;

			current = current->next;
			free(temp);
		}
	}
	free(graph->adjacencyLists);
	graph->numVertices = 0;
	printf("The graph has been deleted\n");
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	/* Create the graph with 12 vertices (countries) */
	Graph africaMap = createGraph(12);

	/* Initialize country names */
	const char *countryNames[] = {"DRC", "Uganda", "Rwanda",
		"Burundi", "Kenya", "Tanzania", "Brazzaville",
								  "Angola", "Zambia", "Zimbabwe", "Malawi", "Mozambique"};
	for (int i = 0; i < africaMap.numVertices; ++i)
	{
		africaMap.adjacencyLists[i] = createCountryNode(countryNames[i]);
	}

	/* Add edges (connections) between vertices (countries) */
	addEdge(&africaMap, "DRC", "Tanzania");
	addEdge(&africaMap, "DRC", "Angola");
	addEdge(&africaMap, "DRC", "Brazzaville");
	addEdge(&africaMap, "DRC", "Burundi");
	addEdge(&africaMap, "DRC", "Rwanda");
	addEdge(&africaMap, "Uganda", "Kenya");
	addEdge(&africaMap, "Uganda", "Tanzania");
	addEdge(&africaMap, "Rwanda", "Tanzania");
	addEdge(&africaMap, "Burundi", "Tanzania");
	addEdge(&africaMap, "Kenya", "Tanzania");
	addEdge(&africaMap, "Tanzania", "Mozambique");
	addEdge(&africaMap, "Angola", "Zambia");
	addEdge(&africaMap, "Zambia", "Malawi");
	addEdge(&africaMap, "Zambia", "Mozambique");
	addEdge(&africaMap, "Zambia", "Zimbabwe");
	addEdge(&africaMap, "Zimbabwe", "Mozambique");

	/*Print the graph*/
	printGraph(&africaMap);

	/*Delete the graph to free memory*/
	deleteGraph(&africaMap);

	return (0);
}
