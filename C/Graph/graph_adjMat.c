// Non-directed, unweighted graph using Adjacency Matrix

#include <stdio.h>
#include <stdlib.h>
#define SIZE 25


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
	GNode *adjMat[SIZE][SIZE]; // 0-based indexing
	int *visited;
};

typedef struct Graph Graph;


// Graph functions
GNode* create_GNode(int vertex, int data);
Graph* createGraph(int numV);

void addEdge(Graph *graph, int v1, int d1, int v2, int d2);

void displayAdjMat(Graph* graph);

void BFS(Graph *graph, int startV_i, int startV_j);
void DFS(Graph *graph, int startV_i, int startV_j);

void resetVisits(Graph *graph);


// Queue functions
QNode* create_QNode(int vertex);
void enqueue(QNode **qNode, int vertex);
int dequeue(QNode **qNode);
void displayQueue(QNode *qNode);


int main() {
	printf("Non-directed, Unweighted Graph using Adjacency Matrix\n\n");

	int nGNodes;
	printf("Enter number of nodes : ");
	scanf("%d", &nGNodes);

	Graph *graph = createGraph(nGNodes);

	int cont;
	do {
		int op;
		do {
			printf("1. Add Edge\n");
			printf("2. Display Adjacency Matrix\n");
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
					displayAdjMat(graph);
					printf("\n");
					break;

			case 3:
					BFS(graph, 0, 1);
					resetVisits(graph);
					break;

			case 4: 
					DFS(graph, 0, 1);
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
	GNode *newNode = malloc(sizeof(GNode));
	newNode->vertex = vertex;
	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

Graph* createGraph(int numV) {
	Graph* graph = malloc(sizeof(Graph));
	graph->numV = numV;

	int i, j;
	for(i=0; i<numV; i++)
		for(j=0; j<numV; j++)
			graph->adjMat[i][j] = NULL; // Important

	graph->visited = malloc(numV * sizeof(int));
	for (i=0; i<numV; i++) 
		graph->visited[i] = 0; 

	return graph;
}

void addEdge(Graph *graph, int v1, int d1, int v2, int d2) {
	GNode *n1 = create_GNode(v1, d1);
	GNode *n2 = create_GNode(v2, d2);

	graph->adjMat[v1][v2] = n2;
	graph->adjMat[v2][v1] = n1;
}

void displayAdjMat(Graph* graph) {
	printf("Adjacency Matrix\n");

	int i, j;
	for(i=0; i<graph->numV; i++) {
		for(j=0; j<graph->numV; j++) {
			if (graph->adjMat[i][j] == NULL)
				// printf("X ");
				printf("0 ");
			else
				// printf("%d ", (graph->adjMat[i][j])->vertex);
				printf("1 ");
		}
		printf("\n");
	}

	printf("\n");
}

void BFS(Graph *graph, int startV_i, int startV_j) {
	printf("BFS : ");

	GNode *gNode = graph->adjMat[startV_i][startV_j];

	QNode *qNode = create_QNode(gNode->vertex);

	int vertex;
	while(qNode != NULL) {
		// displayQueue(qNode);

		vertex = dequeue(&qNode);
		graph->visited[vertex] = 1;
		printf("%d ", vertex);

		int i;
		GNode *temp;
		int adjVertex;

		for (i=0; i<graph->numV; i++) {
			temp = graph->adjMat[vertex][i];

			if (temp == NULL) {
				continue;
			}

			adjVertex = temp->vertex;
			if (graph->visited[adjVertex] == 0) {
				graph->visited[adjVertex] = 1;
				enqueue(&qNode, adjVertex);
			}
		}
	}

	printf("\n");
}

// void DFS(Graph *graph, int startV_i, int startV_j) {
// 	QNode *qNode = create_QNode(graph->adjMat[startV_i][startV_j]->vertex);

// 	if (qNode != NULL) {
// 		graph->visited[qNode->vertex] = 1;
// 		printf("%d ", qNode->vertex);

// 		int i;
// 		for (i=0; i<graph->numV; i++) {
// 			if (graph->visited[i] == 0) {
// 				DFS(graph, qNode->vertex, i);
// 			}
// 		}
// 	}
// }

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
	printf("\nQueue : ");

	if (qNode == NULL) {
		printf("Empty queue");
		return;
	}

	while(qNode != NULL) {
		printf("%d ", (qNode->vertex));
		qNode = qNode->next;
	}

	printf("\n");
}