#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure to represent a country node
typedef struct CountryNode {
    char name[50];
    struct CountryNode* next;
} CountryNode;

// Structure to represent the graph
typedef struct Graph {
    int numVertices;
    CountryNode** adjacencyLists;
} Graph;

// Function to create a new country node
CountryNode* createCountryNode(const char* name) {
    CountryNode* newNode = (CountryNode*)malloc(sizeof(CountryNode));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// Function to create the graph
Graph createGraph(int numVertices) {
    Graph graph;
    graph.numVertices = numVertices;
    graph.adjacencyLists = (CountryNode**)malloc(numVertices * sizeof(CountryNode*));
    for (int i = 0; i < numVertices; ++i) {
        graph.adjacencyLists[i] = NULL;
    }
    return graph;
}

// Function to add an edge between two vertices
void addEdge(Graph* graph, const char* source, const char* destination) {
    int sourceIndex = -1, destinationIndex = -1;
    // Find index of source and destination vertices
    for (int i = 0; i < graph->numVertices; ++i) {
        if (strcmp(graph->adjacencyLists[i]->name, source) == 0) {
            sourceIndex = i;
        }
        if (strcmp(graph->adjacencyLists[i]->name, destination) == 0) {
            destinationIndex = i;
        }
    }
    // If both source and destination exist, add an edge
    if (sourceIndex != -1 && destinationIndex != -1) {
        // Add destination to the adjacency list of source
        CountryNode* newNode = createCountryNode(destination);
        newNode->next = graph->adjacencyLists[sourceIndex]->next;
        graph->adjacencyLists[sourceIndex]->next = newNode;
        // Add source to the adjacency list of destination (assuming undirected graph)
        newNode = createCountryNode(source);
        newNode->next = graph->adjacencyLists[destinationIndex]->next;
        graph->adjacencyLists[destinationIndex]->next = newNode;
    }
}

// Function to print the graph in adjacency list representation
void printGraph(const Graph* graph) {
    printf("Adjacency List Representation:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        printf("%s -> ", graph->adjacencyLists[i]->name);
        CountryNode* current = graph->adjacencyLists[i]->next;
        while (current != NULL) {
            printf("%s ", current->name);
            current = current->next;
        }
        printf("\n");
    }
}

// Queue implementation for BFS
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isQueueFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isQueueEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    ++queue->size;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    --queue->size;
    return item;
}

void BFS(const Graph* graph, const char* startCountry) {
    int startIndex = -1;
    for (int i = 0; i < graph->numVertices; ++i) {
        if (strcmp(graph->adjacencyLists[i]->name, startCountry) == 0) {
            startIndex = i;
            break;
        }
    }
    if (startIndex == -1) {
        printf("Country %s not found in the graph.\n", startCountry);
        return;
    }

    printf("BFS starting from %s:\n", startCountry);

    Queue* queue = createQueue(graph->numVertices);
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = false;
    }

    enqueue(queue, startIndex);
    visited[startIndex] = true;

    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        printf("%s ", graph->adjacencyLists[current]->name);

        CountryNode* temp = graph->adjacencyLists[current]->next;
        while (temp != NULL) {
            int index = -1;
            for (int i = 0; i < graph->numVertices; ++i) {
                if (strcmp(graph->adjacencyLists[i]->name, temp->name) == 0) {
                    index = i;
                    break;
                }
            }
            if (index != -1 && !visited[index]) {
                enqueue(queue, index);
                visited[index] = true;
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(queue->array);
    free(queue);
    printf("\n");
}

// Function for Depth First Search (DFS)
void DFSUtil(const Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%s ", graph->adjacencyLists[vertex]->name);

    CountryNode* temp = graph->adjacencyLists[vertex]->next;
    while (temp != NULL) {
        int index = -1;
        for (int i = 0; i < graph->numVertices; ++i) {
            if (strcmp(graph->adjacencyLists[i]->name, temp->name) == 0) {
                index = i;
                break;
            }
        }
        if (index != -1 && !visited[index]) {
            DFSUtil(graph, index, visited);
        }
        temp = temp->next;
    }
}

void DFS(const Graph* graph, const char* startCountry) {
    int startIndex = -1;
    for (int i = 0; i < graph->numVertices; ++i) {
        if (strcmp(graph->adjacencyLists[i]->name, startCountry) == 0) {
            startIndex = i;
            break;
        }
    }
    if (startIndex == -1) {
        printf("Country %s not found in the graph.\n", startCountry);
        return;
    }

    printf("DFS starting from %s:\n", startCountry);

    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = false;
    }

    DFSUtil(graph, startIndex, visited);

    free(visited);
    printf("\n");
}

void deleteGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        CountryNode* current = graph->adjacencyLists[i];
        while (current != NULL) {
            CountryNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjacencyLists);
    graph->numVertices = 0;
}

// Main function
int main() {
    // Create the graph with 7 vertices (countries)
    Graph africaMap = createGraph(7);

    // Initialize country names
    const char* countryNames[] = {"Nigeria", "Ghana", "Cameroon", "Chad", "Niger", "Mali", "Senegal"};
    for (int i = 0; i < africaMap.numVertices; ++i) {
        africaMap.adjacencyLists[i] = createCountryNode(countryNames[i]);
    }

    // Add edges (connections) between vertices (countries)
    addEdge(&africaMap, "Nigeria", "Ghana");
    addEdge(&africaMap, "Nigeria", "Cameroon");
    addEdge(&africaMap, "Ghana", "Cameroon");
    addEdge(&africaMap, "Ghana", "Mali");
    addEdge(&africaMap, "Cameroon", "Chad");
    addEdge(&africaMap, "Chad", "Niger");
    addEdge(&africaMap, "Chad", "Mali");
    addEdge(&africaMap, "Niger", "Mali");
    addEdge(&africaMap, "Niger", "Senegal");
    addEdge(&africaMap, "Mali", "Senegal");

    // Print the graph
    printGraph(&africaMap);

    // Perform BFS starting from Nigeria
    BFS(&africaMap, "Nigeria");

    // Perform DFS starting from Nigeria
    DFS(&africaMap, "Nigeria");

    // Delete the graph to free memory
    deleteGraph(&africaMap);

    return 0;
}
