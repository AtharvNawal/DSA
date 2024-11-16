#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100 

struct node {
    int v;
    int weight;
    struct node* next;
};

struct node* A[MAX];

void init(struct node* A[], int v) {
    for (int i = 0; i < v; i++) A[i] = NULL;
}

void addEdge(struct node** curr, int v, int weight) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->v = v;
    newNode->weight = weight;
    newNode->next = NULL;

    if (*curr == NULL) {
        *curr = newNode;
    } else {
        struct node* temp = *curr;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void createGraph(struct node* A[], int v) {
    int n;
    printf("Enter the number of edges: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int u, v, w;
        printf("Enter edge (u, v) and weight: ");
        scanf("%d %d %d", &u, &v, &w);
        if (u >= 0 && u < MAX && v >= 0 && v < MAX) {
            addEdge(&A[u], v, w);
            addEdge(&A[v], u, w);  // For undirected graph
        } else {
            printf("Invalid input: %d %d\n", u, v);
        }
    }
}

void displayGraph(struct node* A[], int v) {
    for (int i = 0; i < v; i++) {
        struct node* p = A[i];
        printf("Vertex %d:", i);
        while (p) {
            printf(" -> (%d, %d)", p->v, p->weight);
            p = p->next;
        }
        printf("\n");
    }
}


void primMST(struct node* A[], int v) {
    int parent[MAX];  
    int key[MAX];    
    bool inMST[MAX]; 

    for (int i = 0; i < v; i++) {
        key[i] = MAX;
        inMST[i] = false;
    }

    key[0] = 0;     
    parent[0] = -1;   

    for (int count = 0; count < v - 1; count++) {
        int min = MAX, u;

        for (int i = 0; i < v; i++) {
            if (!inMST[i] && key[i] < min) {
                min = key[i];
                u = i;
            }
        }

        inMST[u] = true;  

        struct node* p = A[u];
        while (p) {
            int vertex = p->v;
            int weight = p->weight;

            if (!inMST[vertex] && weight < key[vertex]) {
                key[vertex] = weight;
                parent[vertex] = u;
            }
            p = p->next;
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < v; i++)
        printf("%d - %d \t%d\n", parent[i], i, key[i]);
}



int main() {
    int v;
    int visited[MAX] = {0};

    printf("Enter the number of vertices: ");
    scanf("%d", &v);

    init(A, v);
    createGraph(A, v);
    displayGraph(A, v);

    printf("Running Prim's Algorithm to find MST...\n");
    primMST(A, v);

    return 0;
}

