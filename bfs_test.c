#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "search.h"

int main(void) {
    Graph *graph;
    Node *A, *B, *C, *D, *E, *F, *G, *H, *I, *J, *K;
    char *path;

    graph = init_graph();

    A = create_node('A');
    B = create_node('B');
    C = create_node('C');
    D = create_node('D');
    E = create_node('E');
    F = create_node('F');
    G = create_node('G');
    H = create_node('H');
    I = create_node('I');
    J = create_node('J');
    K = create_node('K');

    connect(A, C); connect(A, I);
    connect(B, D); connect(B, G); connect(B, H);
    connect(C, D); connect(C, G);
    connect(D, H); connect(D, I); connect(D, J);
    connect(E, F); connect(E, H); connect(E, J);
    connect(F, G); connect(F, K); 
    connect(H, J); 
    connect(J, K);  
    
    add_node(graph, A);
    add_node(graph, B);
    add_node(graph, C);
    add_node(graph, D);
    add_node(graph, E);
    add_node(graph, F);
    add_node(graph, G);
    add_node(graph, H);
    add_node(graph, I);
    add_node(graph, J);
    add_node(graph, K);

    printf("graph\n");
    show_graph(graph);

    path = breath_first_search(graph, A, K);
    printf("path:%s\n", path);
    free(path);

    free_graph(graph);
    return 0;
}
