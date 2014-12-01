#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "search.h"

//void show_path(char *path) {
//    int i;
//    printf("  ");
//    for(i=0; i<strlen(path); i++) {
//        printf("%c ", path[i]);
//    }
//    printf("\n");
//}

int main(void) {
    Graph *graph;
    graph = init_graph();

    Node *A, *B, *C, *D, *E, *F;
    A = create_node('A');
    B = create_node('B');
    C = create_node('C');
    D = create_node('D');
    E = create_node('E');
    F = create_node('F');

    connect(A, B);
    connect(A, C);
    connect(B, C);
    connect(B, D);
    connect(C, D);
    connect(D, C);
    connect(E, F);
    connect(F, C);

    add_node(graph, A);
    add_node(graph, B);
    add_node(graph, C);
    add_node(graph, D);
    add_node(graph, E);
    add_node(graph, F);

    show_graph(graph);
    char *path = depth_first_search(graph, A, D);
    show_path(path);
    
    Paths *paths = find_all_paths(graph, A, D);
    show_paths(paths);
    free_paths(paths);

    free_graph(graph);
    return 0;
}
