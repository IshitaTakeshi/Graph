#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search.h"
#include "graph.h"
#include "error.h"

int get_int_from_stdin() {
    int n = 3;
    char s[n];
    fgets(s, n, stdin);
    return atoi(s);
}

int main() {
    Node *A, *B, *C, *D, *E, *F, *G, *H, *I, *J, *K, *L, *M;
    Graph *graph;
    int i;

    graph = init_graph();

    char *labels[] = {
        "Tokyo",
        "Saitama",
        "Gunma",
        "Chiba",
        "Ibaraki",
        "Tochigi",
        "Fukushima",
        "Niigata",
        "Yamagata",
        "Miyagi",
        "Akita",
        "Iwate",
        "Aomori"
    };

    int n_labels = 13;

    A = create_node('A'); B = create_node('B'); C = create_node('C');
    D = create_node('D'); E = create_node('E'); F = create_node('F');
    G = create_node('G'); H = create_node('H'); I = create_node('I');
    J = create_node('J'); K = create_node('K'); L = create_node('L');
    M = create_node('M');

    wconnect(A, B,  30); wconnect(A, D,  40);
    wconnect(B, C,  90); wconnect(B, D,  60); wconnect(B, E, 140); wconnect(B, F, 80);
    wconnect(C, F, 110); wconnect(C, G, 330); wconnect(C, H, 240);
    wconnect(D, E, 130);
    wconnect(E, F, 100); wconnect(E, G, 260);
    wconnect(F, G, 170);
    wconnect(G, H, 550); wconnect(G, I,  80); wconnect(G, J, 90);
    wconnect(H, I, 630);
    wconnect(I, J,  60); wconnect(I, K, 190);
    wconnect(J, K, 290); wconnect(J, L, 180);
    wconnect(K, L, 110); wconnect(K, M, 300);
    wconnect(L, M, 190);

    add_node(graph, A); add_node(graph, B); add_node(graph, C); add_node(graph, D);
    add_node(graph, E); add_node(graph, F); add_node(graph, G); add_node(graph, H);
    add_node(graph, I); add_node(graph, J); add_node(graph, K); add_node(graph, L);
    add_node(graph, M);

    show_graph(graph, 0);

    printf("\n");
    for(i = 0; i < n_labels; i++) {
        printf("%2d: %s\n", i, labels[i]);
    }
    printf("\n");

    char label;
    Node *source;
    Node *destination;

    printf("input source=>");
    label = 65 + get_int_from_stdin();
    if(!node_exists(graph, label)) {
        printf("Error: Node %c doesn't exist\n", label);
        exit(0);
    }
    source = get_node(graph, label);

    printf("input destination=>");
    label = 65 + get_int_from_stdin();
    if(!node_exists(graph, label)) {
        printf("Error: Node %c doesn't exist\n", label);
        exit(0);
    }
    destination = get_node(graph, label);

    Path *path = dijkstra(graph, source, destination);
    int length = strlen(path->path);
    for(i = 0; i < length-1; i++) {
        printf("[%s] -> ", labels[path->path[i]-65]);
    }
    printf("[%s] ", labels[path->path[length-1]-65]);
    printf("cost: %lf", path->cost);
    printf("\n");

    free_path(path);
    free_graph(graph);

    return 0;
}
