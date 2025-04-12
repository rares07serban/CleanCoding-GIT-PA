#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} Graph;

Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void read_edges(int vertex_count, int edge_count, Graph *graph) {
    int src, dest;
    printf("Adauga %d muchii (noduri de la 0 la %d):\n", edge_count, vertex_count - 1);
    for (int i = 0; i < edge_count; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *new_node = create_node(data);

    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void dfs(Graph *graph, int vertex) {
    Node *adj_list = graph->adjacency_lists[vertex];
    Node *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d -> ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            dfs(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void bfs(Graph *graph, int start_vertex) {
    Node *queue = NULL;

    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(queue)) {
        int current_vertex = dequeue(&queue);
        printf("%d -> ", current_vertex);

        Node *temp = graph->adjacency_lists[current_vertex];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Funcția principală
int main() {
    int vertex_count;
    int edge_count;
    int start_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &vertex_count);

    printf("Cate muchii are graful? ");
    scanf("%d", &edge_count);

    Graph *graph = create_graph(vertex_count);
    read_edges(vertex_count, edge_count, graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere cu DFS: ");
    dfs(graph, start_vertex);

    reset_visited(graph);
    printf("\n");

    printf("De unde plecam in BFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere cu BFS: ");
    bfs(graph, start_vertex);

    printf("\n");
    return 0;
}