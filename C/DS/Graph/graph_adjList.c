// Non-directed, Unweighted Graph using Adjacency Lists

#include <stdio.h>
#include <stdlib.h>


// Queue block
struct QNode {
	int vertex;
	struct QNode *next; 
};

typedef struct QNode QNode;


// Graph block
struct GNode {
	int vertex;
	int data;
	struct GNode *next;
};

typedef struct GNode GNode;

struct Graph {
	int numV;
	GNode **adjLists; // 0-based indexing
	int *visited;
};

typedef struct Graph Graph;


// Queue functions
QNode* create_QNode(int vertex);
void enqueue(QNode **qNode, int vertex);
int dequeue(QNode **qNode);
void displayQueue(QNode *qNode);


// Graph functions
GNode* create_GNode(int vertex, int data);
Graph* createGraph(int numV);

void addEdge(Graph *graph, int v1, int d1, int v2, int d2);

void displayAdjLists(Graph *graph);

void BFS(Graph *graph, int startV);
void DFS(Graph *graph, int startV);

void resetVisits(Graph *graph);


int main() {
	printf("Non-directed, Unweighted Graph\n\n");

	int nGNodes;
	printf("Enter number of nodes : ");
	scanf("%d", &nGNodes);

	Graph *graph = createGraph(nGNodes);

	int cont;
	do {
		int op;
		do {
			printf("1. Add Edge\n");
			printf("2. Display Adjacency Lists array\n");
			printf("3. Breadth First Search\n");
			printf("4. Depth First Search\n");
			printf("5. Exit\n\n");

			scanf("%d", &op);

			switch (op) {
			case 1:	
					printf("Enter edge vertices :\n");
					int v1, d1, v2, d2;
					int ch;

					do {
						printf("Enter 1st vertex number and data : ");
						scanf("%d", &v1, &d1);
						printf("Enter 2nd vertex number and data : ");
						scanf("%d", &v2, &d2);
						addEdge(graph, v1, d1, v2, d2);

						printf("Do you want to add more edges? (1/0) : ");
						scanf(&ch);
					} while(ch == 1);

					break;	

			case 2:
					displayAdjLists(graph);
					printf("\n");
					break;

			case 3:
					BFS(graph, 0);
					resetVisits(graph);
					break;

			case 4: 
					DFS(graph, 0);
					resetVisits(graph);
					printf("\n");
					break;

			case 5:
					exit(0);
			}
		} while(op = 1);
	} while (cont == 1);

	return 0;
}


GNode* create_GNode(int vertex, int data) {
	GNode *newGNode = malloc(sizeof(GNode));
	newGNode->vertex = vertex;
	newGNode->data = data;
	newGNode->next = NULL;

	return newGNode;
}

Graph* createGraph(int numV) {
	Graph *graph = malloc(sizeof(Graph));
	graph->numV = numV;
	graph->adjLists = malloc(numV * sizeof(GNode));

	int i;
	for(i=0; i<numV; i++) 
		graph->adjLists[i] = NULL; // Important

	graph->visited = malloc(numV * sizeof(int));
	for(i=0; i<numV; i++)
		graph->visited[i] = 0;

	return graph;
}

void addEdge(Graph* graph, int v1, 
			int d1, int v2, int d2) {
	GNode *newGNode = create_GNode(v2, d2);
	newGNode->next = graph->adjLists[v1];
	graph->adjLists[v1] = newGNode;

	newGNode = create_GNode(v1, d1);
	newGNode->next = graph->adjLists[v2];
	graph->adjLists[v2] = newGNode;
}

void displayAdjLists(Graph *graph) {
	printf("Adjacency List");

	int i;
	for(i=0; i<graph->numV; i++) {
		GNode *temp = graph->adjLists[i];

		printf("\n%d : ", i);
		while(temp != NULL) {
			printf("%d=>%d, ", temp->vertex, temp->data);
			temp = temp->next;
		}
	}

	printf("\n");
}

void BFS(Graph *graph, int startV) {
	printf("BFS traversal : ");

	QNode *qNode = create_QNode(startV);

	graph->visited[startV] = 1;

	int vertex;
	while(qNode != NULL) {
		// displayQueue(qNode);

		vertex = dequeue(&qNode);
		// printf("%d\n", vertex);
		printf("%d ", vertex);

		GNode *temp = graph->adjLists[vertex];

		while(temp != NULL) {
			if (graph->visited[temp->vertex] == 0) {
				graph->visited[temp->vertex] = 1;
				enqueue(&qNode, temp->vertex);
			}
			temp = temp->next;
		}
	}

	printf("\n");
}

void DFS(Graph *graph, int vertex) {
	// Recursive

	GNode *temp = graph->adjLists[vertex];

	printf("%d ", vertex);
	graph->visited[vertex] = 1;

	int adjV;
	while (temp != NULL) {
		adjV = temp->vertex;

		if (graph->visited[adjV] == 0)
			DFS(graph, adjV);

		temp = temp->next;
	}
}

void resetVisits(Graph *graph) {
	int i;
	for (i=0; i<graph->numV; i++)
		graph->visited[i] = 0;
}


QNode* create_QNode(int vertex) {
	QNode *qNode = malloc(sizeof(QNode));
	qNode->vertex = vertex;
	qNode->next = NULL;

	return qNode;
}

void enqueue(QNode **qNode, int vertex) {
	if (*qNode == NULL) {
		*qNode = create_QNode(vertex);
		return;
	}

	QNode *holdQNode = *qNode;

	QNode *newQNode = create_QNode(vertex);

	while ((*qNode)->next != NULL)
		*qNode = (*qNode)->next;

	(*qNode)->next = newQNode;

	*qNode = holdQNode;
}

int dequeue(QNode **qNode) {
	if (*qNode == NULL)
		return -1;

	QNode *t = *qNode;
	int vertex = (*qNode)->vertex;
	*qNode = (*qNode)->next;
	free(t);

	return vertex;
}

void displayQueue(QNode *qNode) {
	if (qNode == NULL) {
		printf("\nEmpty queue\n");
		return;
	}

	printf("\nQueue : ");
	while(qNode != NULL) {
		printf("%d ", qNode->vertex);
		qNode = qNode->next;
	}

	printf("\n");
}