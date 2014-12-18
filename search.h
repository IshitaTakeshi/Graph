#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"

typedef struct path_t {
    char *path; /* represent a path in string */
    double cost;
} Path;

typedef struct paths_t {
    int n_paths;
    Path **paths; /* a list of pointers to paths */
} Paths;

Path *depth_first_search(Graph *graph, Node *start, Node *end);
char *breath_first_search(Graph *graph, Node *start, Node *end);
Paths *find_all_paths(Graph *graph, Node *start, Node *end);
void show_path(Path *path, int show_cost);
void show_paths(Paths *paths, int show_cost);
void free_path(Path *path);
void free_paths(Paths *paths);
Path *dijkstra(Graph *graph, Node *start, Node *end);

#endif
