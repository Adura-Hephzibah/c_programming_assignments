#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

Node* createNode(int v);
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void bfs(Graph* graph, int startVertex);
void dfs(Graph* graph, int vertex);

int main() {
    Graph* graph = createGraph(10); // 10 vertices numbered from 0 to 9
    addEdge(graph, 1, 5);
    addEdge(graph, 5, 4);
    addEdge(graph, 5, 8);
    addEdge(graph, 8, 3);
    addEdge(graph, 1, 6);
    addEdge(graph, 6, 9);

   // Add more edges as needed

   printf("Breadth First Search (starting from vertex two):\n");
   bfs(graph, 2);

   printf("\nDepth First Search (starting from vertex two):\n");
   dfs(graph ,2);

   return 0;
}

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(bool));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void bfs(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex];
    Node* temp = adjList;

    graph->visited[startVertex] = true;
    printf("Visited %d\n", startVertex);

    while(temp != NULL) {
        int connectedVertex = temp->vertex;

        if(graph->visited[connectedVertex] == false) {
            bfs(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void dfs(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = true;
    printf("Visited %d\n", vertex);

    while(temp != NULL) {
        int connectedVertex = temp->vertex;

        if(graph->visited[connectedVertex] == false) {
            dfs(graph, connectedVertex);
        }
        temp = temp->next;
    }
}
