#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "search.h"

int main(void) {
    Graph *graph;
    graph = init_graph();

    Node *A, *B, *C, *D, *E, *F, *G, *H, *I, *J, *K;

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

    //connect(A, B); connect(A, C);
    //connect(B, C); connect(B, D);
    //connect(C, D); 
    //connect(D, C);
    //connect(E, F); 
    //connect(F, C);

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
    
    printf("\n");

    char *path = depth_first_search(graph, A, K);
    printf("The result of Depth-first search\n");
    show_path(path);
    free_path(path);
    
    printf("\n");
    
    Paths *paths = find_all_paths(graph, A, K);
    printf("The list of all paths\n");
    show_paths(paths);
    free_paths(paths);

    free_graph(graph);
    return 0;
}
