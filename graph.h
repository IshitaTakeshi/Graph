typedef struct node_t {
    char label;
    int n_neighbors;
    struct node_t **neighbors; //list of pointers of adjacent nodes
} Node;

typedef struct graph_t {
    int n_nodes;
    struct node_t **nodes; //list of pointers of nodes
} Graph;

void free_graph(struct graph_t *graph);
Node *create_node(char label);
void connect(Node *node1, Node *node2);
Graph *init_graph();
void add_node(Graph *graph, Node *node);
void show_node(Node *node);
void show_graph(Graph *graph);
