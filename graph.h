#ifndef GRAPH_H
#define GRAPH_H

/* TODO create a type for vertices */

typedef struct node_t {
    char label;
    int n_neighbors;
    struct node_t **neighbors; /* list of pointers of adjacent nodes */
    /* TODO rename to distances */
    double *weights;
} Node;

typedef struct graph_t {
    int n_nodes;
    struct node_t **nodes; /* list of pointers of nodes */
} Graph;

void free_graph(struct graph_t *graph);
Node *create_node(char label);
void connect(Node *node1, Node *node2);
void connect_weighted(Node *node1, Node *node2, double weight);
Graph *init_graph();
void add_node(Graph *graph, Node *node);
int are_same_nodes(Node *node1, Node *node2);
void show_node(Node *node, int show_weight);
void show_graph(Graph *graph, int show_weight);

#endif
