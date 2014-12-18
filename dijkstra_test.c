#include "search.h"
#include "graph.h"
#include <stdio.h>

int main() {
    Node *A, *B, *C, *D, *E; //, *F, *G, *H, *I, *J, *K, *L, *M;
    Graph *graph;

    graph = init_graph();

    A = create_node('A'); B = create_node('B'); C = create_node('C');
    D = create_node('D'); E = create_node('E'); /*F = create_node('F');
    G = create_node('G'); H = create_node('H'); I = create_node('I');
    J = create_node('J'); K = create_node('K'); L = create_node('L');
    M = create_node('M'); */

    connect_weighted(A, B, 2); connect_weighted(A, D, 3);
    connect_weighted(B, C, 4);
    connect_weighted(C, D, 1); connect_weighted(C, E, 6);
    connect_weighted(D, E, 8);

    add_node(graph, A);
    add_node(graph, B);
    add_node(graph, C);
    add_node(graph, D);
    add_node(graph, E);

    show_graph(graph, 1);

    char *path = dijkstra(graph, A, E);
    printf("path: %s\n", path);
    free_path(path);
    free_graph(graph);

    /*
    connect_weighted(A, B,  30); connect_weighted(A, D,  40);
    connect_weighted(B, C,  90); connect_weighted(B, D,  60); connect_weighted(B, E, 140); connect_weighted(B, F, 80);
    connect_weighted(C, F, 110); connect_weighted(C, G, 330); connect_weighted(C, H, 240);
    connect_weighted(D, E, 130);
    connect_weighted(E, F, 100); connect_weighted(E, G, 260);
    connect_weighted(F, G, 170);
    connect_weighted(G, H, 550); connect_weighted(G, I,  80); connect_weighted(G, J, 90);
    connect_weighted(H, I, 630);
    connect_weighted(I, J,  60); connect_weighted(I, K, 190);
    connect_weighted(J, K, 290); connect_weighted(J, L, 180);
    connect_weighted(K, L, 110); connect_weighted(K, M, 300);
    connect_weighted(L, M, 190);

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
    add_node(graph, L);
    add_node(graph, M);

    show_graph(graph);

    dijkstra(graph, A, K);

    free_graph(graph);

    */
    //A: Tokyo
    //B: Saitama
    //C: Gunma
    //D: Chiba
    //E: Ibaraki
    //F: Tochigi
    //G: Fukushima
    //H: Niigata
    //I: Yamagata
    //J: Miyagi
    //K: Akita
    //L: Iwate
    //M: Aomori
    return 0;
}
