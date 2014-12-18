#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"

typedef struct paths_t {
    int n_paths;
    char **paths; /* represent path in string */
} Paths;

char *depth_first_search(Graph *graph, Node *start, Node *end);
char *breath_first_search(Graph *graph, Node *start, Node *end);
Paths *find_all_paths(Graph *graph, Node *start, Node *end);
void show_path(char *path);
void show_paths(Paths *paths);
void free_path(char* path);
void free_paths(Paths *paths);
char *dijkstra(Graph *graph, Node *start, Node *end);

#endif
