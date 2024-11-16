#include <stdio.h>
#include <stdlib.h>

#define max_queue_size 20 
#define max 10

/* 
Sample input for adjacency matrix (for testing):
4
0 1 1 0
1 0 0 1
1 0 0 1
0 1 1 0

Sample input for adjacency list:
4
1, 2, -1
0, 3, -1
0, 3, -1
1, 2, -1
*/

struct Queue {
    int data[max_queue_size];
    int front, rear;
};

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    int vertices;
    struct AdjList* array;
};

void init(struct Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

int is_queue_empty(struct Queue* queue) {
    return queue->front == -1;
}

void enter_queue(struct Queue* queue, int vertex_name) {
    if (queue->rear == -1) {  // First element
        queue->front = queue->rear = 0;
    } else {
        queue->rear++;
    }
    queue->data[queue->rear] = vertex_name;
}

int delete_queue(struct Queue* queue) {
    if (is_queue_empty(queue)) {
        return -1;
    }
    int vertex_name = queue->data[queue->front];
    if (queue->front == queue->rear) {  // Only one element left
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return vertex_name;
}

// BFS Using Adjacency Matrix
void input_adjacency_matrix(int* vertex, int a[max][max]) {
    printf("How many vertices does your matrix contain? : ");
    scanf("%d", vertex);
    for (int i = 0; i < *vertex; i++) {
        for (int j = 0; j < *vertex; j++) {
            printf("Is there any connection between vertex %d and vertex %d? Enter weight or 0: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

void bfs_matrix(int vertex, int a[max][max]) {
    struct Queue queue;
    init(&queue);
    int visited[max], start_vertex, v;
    for (int i = 0; i < vertex; i++) {
        visited[i] = 0;
    }

    printf("Enter start vertex for BFS: ");
    scanf("%d", &start_vertex);

    visited[start_vertex] = 1;
    enter_queue(&queue, start_vertex);
    while (!is_queue_empty(&queue)) {
        v = delete_queue(&queue);
        printf("%d ", v);
        for (int i = 0; i < vertex; i++) {
            if (a[v][i] == 1 && visited[i] == 0) {
                enter_queue(&queue, i);
                visited[i] = 1;
            }
        }
    }
}

// BFS Using Adjacency List
struct AdjListNode* create_adj_list_node(int dest) {
    struct AdjListNode* new_node = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}

struct Graph* create_graph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->array = (struct AdjList*)malloc(vertices * sizeof(struct AdjList));
    for (int i = 0; i < vertices; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

void add_edge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* new_node = create_adj_list_node(dest);
    new_node->next = graph->array[src].head;
    graph->array[src].head = new_node;

    new_node = create_adj_list_node(src);
    new_node->next = graph->array[dest].head;
    graph->array[dest].head = new_node;
}

void input_adjacency_list(struct Graph* graph) {
    int src, dest;
    for (int i = 0; i < graph->vertices; i++) {
        printf("Enter edges for vertex %d (enter -1 to end): ", i);
        while (1) {
            scanf("%d", &dest);
            if (dest == -1) break;
            add_edge(graph, i, dest);
        }
    }
}

void bfs_list(struct Graph* graph, int start_vertex) {
    struct Queue queue;
    init(&queue);

    int visited[graph->vertices];
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }

    visited[start_vertex] = 1;
    enter_queue(&queue, start_vertex);

    printf("BFS traversal starting from vertex %d:\n", start_vertex);

    while (!is_queue_empty(&queue)) {
        int current_vertex = delete_queue(&queue);
        printf("%d ", current_vertex);

        struct AdjListNode* temp = graph->array[current_vertex].head;
        while (temp) {
            int adj_vertex = temp->dest;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = 1;
                enter_queue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    int option, vertices;
    printf("Choose graph representation:\n");
    printf("1. Adjacency Matrix\n");
    printf("2. Adjacency List\n");
    scanf("%d", &option);

    if (option == 1) {
        int a[max][max];
        input_adjacency_matrix(&vertices, a);
        bfs_matrix(vertices, a);
    } else if (option == 2) {
        printf("Enter number of vertices: ");
        scanf("%d", &vertices);
        struct Graph* graph = create_graph(vertices);
        input_adjacency_list(graph);
        bfs_list(graph, 0); // Assuming BFS starts at vertex 0
    } else {
        printf("Invalid option!\n");
    }

    return 0;
}
