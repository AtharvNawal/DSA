#include <stdio.h>
#include <stdlib.h>

#define MAX 999
#define MAX_VERTICES 10

struct node {
    int v, w;
    struct node* next;
};

struct node* A[MAX_VERTICES];
int adjMatrix[MAX_VERTICES][MAX_VERTICES];

void addEdge(struct node** curr, int v, int w) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->v = v;
    newNode->w = w;
    newNode->next = NULL;

    if (*curr == NULL) {
        *curr = newNode;
    } else {
        struct node* temp = *curr;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void createGraph(struct node* A[], int v) {
    int n, w;
    printf("Enter the number of edges: ");
    scanf("%d", &n);

    printf("Enter edges in format: u v w\n");
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d %d %d", &u, &v, &w);
        if (u >= 0 && u < MAX_VERTICES && v >= 0 && v < MAX_VERTICES) {
            addEdge(&A[u], v, w);
            addEdge(&A[v], u, w);
            adjMatrix[u][v] = w;
            adjMatrix[v][u] = w;
        } else {
            printf("Invalid input: %d %d\n", u, v);
        }
    }
}

void createGraphFromMatrix(int v) {
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &adjMatrix[i][j]);
            if (adjMatrix[i][j] != 0 && i != j) {
                addEdge(&A[i], j, adjMatrix[i][j]);
            }
        }
    }
}

int Findmin(int dist[], int visited[], int v) {
    int min = MAX, u;
    for (int i = 0; i < v; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            u = i;
        }
    }
    return u;
}

void display(int dist[], int v) {
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < v; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

void dijkstras(struct node* A[], int v, int src) {
    int visited[MAX_VERTICES] = {0}, dist[MAX_VERTICES];
    for (int i = 0; i < v; i++) {
        visited[i] = 0;
        dist[i] = MAX;
    }
    dist[src] = 0;

    for (int i = 0; i < v - 1; i++) {
        int u = Findmin(dist, visited, v);
        visited[u] = 1;

        struct node* p = A[u];
        while (p != NULL) {
            if (!visited[p->v] && (dist[u] + p->w < dist[p->v])) {
                dist[p->v] = dist[u] + p->w;
            }
            p = p->next;
        }
    }
    display(dist, v);
}

int main() {
    int v, s, choice;

    printf("Enter the number of vertices: ");
    scanf("%d", &v);

    printf("Choose graph input method:\n1. Enter edges manually\n2. Enter adjacency matrix\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        createGraph(A, v);
    } else if (choice == 2) {
        createGraphFromMatrix(v);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    printf("Enter the starting vertex: ");
    scanf("%d", &s);

    dijkstras(A, v, s);

    return 0;
}