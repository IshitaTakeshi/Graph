#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void free_graph(struct graph_t *graph) {
    int i;
    for(i=0; i<graph->n_nodes; i++) {
        free(graph->nodes[i]);
    }

    free(graph->nodes);
    free(graph);
}

//allocate memory for a node
Node *create_node(char label) {
    Node *node;
    node = (Node *)malloc(sizeof(Node));
    node->n_neighbors = 0;
    node->label = label;
    return node;
}

//connect node1 to node2 
void connect(Node *node1, Node *node2) {
    node1->neighbors = (Node **)realloc(node1->neighbors, 
                                        (node1->n_neighbors+1)*sizeof(Node *));
    node1->neighbors[node1->n_neighbors] = node2;
    node1->n_neighbors += 1;
}

//allocate memory for a graph and set default values
Graph *init_graph() {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->n_nodes = 0;
    return graph;
}

void add_node(Graph *graph, Node *node) {
    graph->nodes = (Node **)realloc(graph->nodes, 
                                    (graph->n_nodes+1)*sizeof(Node *));
    graph->nodes[graph->n_nodes] = node;
    graph->n_nodes += 1;
}

void show_node(Node *node) {
    int i;
    printf("%c: ", node->label);
    for(i=0; i<node->n_neighbors; i++) {
        printf("%c ", node->neighbors[i]->label);
    }
    printf("\n");
}

void show_graph(Graph *graph) {
    int i;
    printf("graph\n");
    for(i=0; i<graph->n_nodes; i++) {
        printf("  ");
        show_node(graph->nodes[i]);
    }
    printf("\n");
}
