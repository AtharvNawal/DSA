#include <stdio.h>
#include<stdlib.h>
#define MAX 999
#define MAX_VERTICES 10
struct node
{
    int v,w;
    struct node* next;
};
struct node* A[MAX_VERTICES];
void addEdge(struct node** curr, int v,int w) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->v = v;
    newNode->next = NULL;
    newNode->w=w;
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
    int n,w;
    printf("Enter the number of edges: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d %d %d", &u, &v,&w);
        if (u >= 0 && u < MAX && v >= 0 && v < MAX) {
            addEdge(&A[u], v,w);
            addEdge(&A[v], u,w);
        } else {
            printf("Invalid input: %d %d\n", u, v);
        }
    }
}

int Findmin(int dist[], int visited[], int v) {
    int min = MAX, u;
    for (int i = 0; i < v; i++) {
        if (visited[i] == 0 && dist[i] < min) {
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
        struct node* p=A[u];
        while(p!=NULL) {

            if (visited[p->v] == 0 && (dist[u] + p->w < dist[p->v])) {
                dist[p->v] = dist[u] + p->w;
            }
            p=p->next;
        }
    }
    display(dist, v);
}

int main() {
    int v,s;

    printf("Enter the number of vertices: ");
    scanf("%d", &v);
    createGraph(A, v);
 printf("Enter the starting vertex");
 scanf("%d",&s);
    dijkstras(A,v,s);
    return 0;
}
