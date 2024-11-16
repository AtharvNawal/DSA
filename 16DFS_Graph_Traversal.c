#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    }
}

int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

// DFS using Adjacency Matrix
void DFS_AdjMatrix(int adjMatrix[MAX][MAX], int n, int startVertex) {
    int visited[MAX] = {0};
    Stack s;
    initStack(&s);
    
    push(&s, startVertex);
    visited[startVertex] = 1;
    
    printf("DFS Traversal using Adjacency Matrix: ");
    
    while (!isEmpty(&s)) {
        int current = pop(&s);
        printf("%d ", current);
        
        for (int i = 0; i < n; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                push(&s, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX]; // Adjacency list

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// DFS using Adjacency List
void DFS_AdjList(int startVertex, int n) {
    int visited[MAX] = {0};
    Stack s;
    initStack(&s);
    
    push(&s, startVertex);
    visited[startVertex] = 1;
    
    printf("DFS Traversal using Adjacency List: ");
    
    while (!isEmpty(&s)) {
        int current = pop(&s);
        printf("%d ", current);
        
        Node* temp = adjList[current];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                push(&s, adjVertex);
                visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    int n, edges;
    int adjMatrix[MAX][MAX] = {0};
    
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    
    for (int i = 0; i < n; i++) {
        adjList[i] = NULL;
    }
    
    for (int i = 0; i < edges; i++) {
        int u, v;
        printf("Enter the edge (u v): ");
        scanf("%d%d", &u, &v);
        
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
        
        Node* newNode = createNode(v);
        newNode->next = adjList[u];
        adjList[u] = newNode;

        newNode = createNode(u);
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }
    
    int startVertex;
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);
    
    DFS_AdjMatrix(adjMatrix, n, startVertex);
    
    DFS_AdjList(startVertex, n);
    
    return 0;
}
