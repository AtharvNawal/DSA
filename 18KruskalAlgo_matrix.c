#include <stdio.h>
#include <stdlib.h>
 
#define MAX 999  
 
int parent[100];
 
int find(int i) {
   if (parent[i] == i)
       return i;
   return parent[i] = find(parent[i]);
}
 
void updateParents(int u, int v) {
   int p1 = find(u);
   int p2 = find(v);
   if (p1 != p2) {
       parent[p2] = p1;
   }
}
 
void kruskal(int G[100][100], int V) {
   int MST_weight = 0;
   int edges = 0;
 
   for (int i = 0; i < V; i++) {
       parent[i] = i;
   }
 
   while (edges < V - 1) {
       int min = MAX;
       int a = -1, b = -1;
 
 
       for (int i = 0; i < V; i++) {
           for (int j = 0; j < V; j++) {
               if (G[i][j] != 0 && find(i) != find(j) && G[i][j] < min) {
                   min = G[i][j];
                   a = i;
                   b = j;
               }
           }
       }
 
       if (a != -1 && b != -1) {
           printf("Edge (%d, %d) with weight %d\n", a, b, min);
           updateParents(a, b);  
           MST_weight += min;
           edges++;
       }
       G[a][b] = G[b][a] = MAX;
   }
 
   printf("Total weight of MST: %d\n", MST_weight);
}
 
int main() {
   int V;
   printf("Enter the number of vertices: ");
   scanf("%d", &V);
 
   int G[100][100];
 
   printf("Enter the adjacency matrix (use 0 for no edge):\n");
   for (int i = 0; i < V; i++) {
       for (int j = 0; j < V; j++) {
           scanf("%d", &G[i][j]);
       }
   }
 
   printf("Minimum Spanning Tree (MST) using Kruskal's Algorithm:\n");
   kruskal(G, V);
 
   return 0;
}