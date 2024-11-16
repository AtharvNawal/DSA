#include <stdio.h>
#include <stdlib.h>
#define MAX 100
 
struct node {
   int v, weight;
   struct node* next;
};
 
struct node* A[MAX];  
 
int parent[MAX];
 
 
void init(struct node* A[], int v) {
   for (int i = 0; i < v; i++) {
       A[i] = NULL;
   }
}
 
 
int find(int i) {
   if (parent[i] == i) return i;
   return parent[i] = find(parent[i]);
}
 
void updateParents(int u, int v) {
   int p1 = find(u);
   int p2 = find(v);
   if (p1 != p2) {
       parent[p2] = p1;
   }
}
 
void addEdge(struct node** curr, int v, int weight) {
   struct node* newNode = (struct node*)malloc(sizeof(struct node));
   newNode->v = v;
   newNode->weight = weight;
   newNode->next = *curr;
   *curr = newNode;
}
 
void createGraph(struct node* A[], int v) {
   int n;
   printf("Enter the number of edges: ");
   scanf("%d", &n);
   for (int i = 0; i < n; i++) {
       int u, v, weight;
       printf("Enter edge (u, v) and weight: ");
       scanf("%d %d %d", &u, &v, &weight);
       addEdge(&A[u], v, weight);
       addEdge(&A[v], u, weight);
   }
}
 
void kruskal(struct node* A[], int v) {
   int mst_weight = 0;
   int edges_in_mst = 0;
 
   for (int i = 0; i < v; i++) {
       parent[i] = i;
   }
 
   printf("Edges in the MST:\n");
 
   while (edges_in_mst < v - 1) {
       int min_weight = 99999;
       int u = -1, v = -1;
 
       for (int i = 0; i < v; i++) {
           struct node* p = A[i];
           while (p) {
               if (find(i) != find(p->v) && p->weight < min_weight) {
                   min_weight = p->weight;
                   u = i;
                   v = p->v;
               }
               p = p->next;
           }
       }
 
       if (u != -1 && v != -1) {
           printf("Edge (%d, %d) with weight %d\n", u, v, min_weight);
           updateParents(u, v);
           mst_weight += min_weight;
           edges_in_mst++;
       }
   }
 
   printf("Total weight of MST: %d\n", mst_weight);
}
 
int main() {
   int v;
   printf("Enter the number of vertices: ");
   scanf("%d", &v);
 
   init(A, v);  
   createGraph(A, v);  
 
   kruskal(A, v);
 
   return 0;
}