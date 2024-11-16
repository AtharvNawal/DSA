#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 999  

int minKey(int key[], bool mstSet[], int V) {
    int min = MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[MAX][MAX], int V) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

void primMST(int graph[MAX][MAX], int V) {
    int *parent = (int *)malloc(V * sizeof(int));  
    int *key = (int *)malloc(V * sizeof(int));     
    bool *mstSet = (bool *)malloc(V * sizeof(bool)); 

    for (int i = 0; i < V; i++) {
        key[i] = MAX;
        mstSet[i] = false;
    }

    key[0] = 0;    
    parent[0] = -1; 

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true; 

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u; 
                key[v] = graph[u][v]; 
            }
        }
    }
    printMST(parent, graph, V); 

    free(parent);
    free(key);
    free(mstSet);
}

int main() {
    int V, graph[MAX][MAX];
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix for the graph:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nMinimum Spanning Tree using Prim's Algorithm:\n");
    primMST(graph, V);

    return 0;
}