#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

//Free the memory area that a graph used
void free_graph(struct graph_t *graph) {
    int i;
    for(i=0; i<graph->n_nodes; i++) {
        free(graph->nodes[i]);
    }

    free(graph->nodes);
    free(graph);
}

//Allocate memory for a node
Node *create_node(char label) {
    Node *node;
    node = (Node *)malloc(sizeof(Node));
    node->n_neighbors = 0;
    node->label = label;
    return node;
}

//Connect a to b
void connect_(Node *a, Node *b) {
    if(a->n_neighbors == 0) {
    	a->neighbors = (Node **)malloc((a->n_neighbors+1)*sizeof(Node *));
    } else {
    	a->neighbors = (Node **)realloc(a->neighbors,
        	                            (a->n_neighbors+1)*sizeof(Node *));
    }
    a->neighbors[a->n_neighbors] = b;
    a->n_neighbors += 1;
}

//Connect both to represent an undirected path
void connect(Node *node1, Node *node2) {
    connect_(node1, node2);
    connect_(node2, node1);
}

//Allocate memory for a graph and set default values
Graph *init_graph() {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->n_nodes = 0;
    return graph;
}

//Add a node to a graph
void add_node(Graph *graph, Node *node) {
    if(graph->n_nodes == 0) {
		graph->nodes = (Node **)malloc((graph->n_nodes+1)*sizeof(Node *));
	} else {
		graph->nodes = (Node **)realloc(graph->nodes,
                                        (graph->n_nodes+1)*sizeof(Node *));
	}
	graph->nodes[graph->n_nodes] = node;
    graph->n_nodes += 1;
}

//Show the label of a node
void show_node(Node *node) {
    int i;
    printf("%c: ", node->label);
    for(i=0; i<node->n_neighbors; i++) {
        printf("%c ", node->neighbors[i]->label);
    }
    printf("\n");
}

//Show a graph
void show_graph(Graph *graph) {
    int i;
    for(i=0; i<graph->n_nodes; i++) {
        printf("  ");
        show_node(graph->nodes[i]);
    }
}
