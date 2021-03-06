#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include "graph.h"
#include "search.h"
#include "queue.h"
#include "error.h"


Path *depth_first_search_(
    Graph *graph, Node *start, Node *end, char *path, int path_index) {
    int i;

    path[path_index] = start->label;
    path[path_index+1] = '\0';

    if(start->label == end->label) {
        Path *p = (Path *)malloc(sizeof(Path));
        p->path = path;
        return p;
    }

    for(i=0; i<start->n_neighbors; i++) {
        Node *node = start->neighbors[i];
        /* do nothing if the node is already visited */
        if(strchr(path, node->label) != NULL) {
            continue;
        }

        Path *new_path = depth_first_search_(graph, node, end, path,
                                             path_index+1);
        if(new_path != NULL) {
            return new_path;
        }
    }
    free(path);
    return NULL;
}

/* search the path from start to end */
Path *depth_first_search(Graph *graph, Node *start, Node *end) {
    /* +1 for '\0' */
    char *path = (char *)malloc(graph->n_nodes+1);
    return depth_first_search_(graph, start, end, path, 0);
}

void append_path(Paths *paths, Path *path) {
    paths->paths = (Path **)realloc(paths->paths,
                                    (paths->n_paths+1)*sizeof(Path *));
    paths->paths[paths->n_paths] = path;
    paths->n_paths += 1;
}

Paths *init_paths() {
    Paths *paths = (Paths *)malloc(sizeof(Paths));
    paths->n_paths = 0;
    paths->paths = (Path **)malloc(paths->n_paths * sizeof(Path *));
    return paths;
}

Paths *find_all_paths_(
        Graph *graph, Node *start, Node *end, char *path_, int depth) {
    char *path = (char *)malloc(graph->n_nodes);
    strncpy(path, path_, depth+1);
    path[depth] = start->label;
    path[depth+1] = '\0';

    if(start->label == end->label) {
        Paths *ps = init_paths();
        Path *p = (Path *)malloc(sizeof(Path));
        p->path = path;
        append_path(ps, p);
        return ps;
    }

    Paths *paths = init_paths();
    int i, j;
    for(i=0; i<start->n_neighbors; i++) {
        Node *node = start->neighbors[i];
        /* do nothing if the node is already visited */
        if(strchr(path, node->label) != NULL) {
            continue;
        }

        Paths *new_paths = find_all_paths_(graph, node, end, path, depth+1);
        for(j=0; j<new_paths->n_paths; j++) {
            append_path(paths, new_paths->paths[j]);
        }
    }

    free(path);
    return paths;
}

/* search all paths from start to end */
Paths *find_all_paths(Graph *graph, Node *start, Node *end) {
    return find_all_paths_(graph, start, end, "", 0);
}

char *breath_first_search(Graph *graph, Node *start, Node *end) {
    Node *neighbor;
    Node *node;

    char visited[graph->n_nodes+1];
    int visited_index = 0;
    visited[0] = '\0';

    char *path = (char *)malloc(graph->n_nodes+1);  /* +1 for '\0' */
    int path_index = 0;

    int i;

    init_queue(graph->n_nodes);
    enqueue(start);

    while(!queue_is_empty()) {
        node = (Node *)dequeue();

        if(strchr(path, node->label) == NULL) {
            path[path_index] = node->label;
            path_index += 1;
        }

        if(node->label == end->label) {
            path[path_index] = '\0';
            return path;
        }

        for(i=0; i<node->n_neighbors; i++) {
            neighbor = node->neighbors[i];

            /* do nothing if the node is already visited */
            if(strchr(visited, neighbor->label) != NULL) {
                continue;
            }

            visited[visited_index] = neighbor->label;
            visited[visited_index+1] = '\0';
            visited_index += 1;

            enqueue(neighbor);
        }
    }

    free_queue();
    return NULL;
}

typedef struct node_pair_t {
    int index;
    Node *node;
} NodePair;

int search_v_index(Graph *graph, Node *v) {
    int v_index;
    Node *node;
    for(v_index = 0; v_index < graph->n_nodes; v_index++) {
        node = graph->nodes[v_index];
        if(node->label == v->label) {
            return v_index;
        }
    }
    return -1;
}


/*TODO slow. use dictionary to accelerate */
int get_node_index(Graph *graph, Node *node) {
    int i;
    Node *n;
    for(i = 0; i < graph->n_nodes; i++) {
        n = graph->nodes[i];
        if(n->label == node->label) {
            return i;
        }
    }
    printf("label : %c\n", node->label);
    fatal_error("Invalid label detected.\n");
    return -1;
}

/*
 * search by Dijkstra's algorithm
 * explanation is here
 * http://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Pseudocode
 */
Path *dijkstra(Graph *graph, Node *start, Node *end) {
    int i;
    Node *neighbor;
    Node *node;
    Node *current;
    double distances[graph->n_nodes];
    double alternative;
    double shortest;
    int previous[graph->n_nodes];
    int visited[graph->n_nodes];
    int path_indices[graph->n_nodes];
    int n_visited, index, shortest_index, path_length, u;

    for(i = 0; i < graph->n_nodes; i++) {
        node = graph->nodes[i];

        if(node->label == start->label) {
            distances[i] = 0;
        } else {
            distances[i] = DBL_MAX;
        }

        previous[i] = -1;
        visited[i] = 0; /* set ith node as unvisited */
    }

    n_visited = 0;
    while(n_visited < graph->n_nodes) {
        shortest = DBL_MAX;
        shortest_index = 0;
        for(i = 0; i < graph->n_nodes; i++) {
            if(distances[i] < shortest && !visited[i]) {
                shortest_index = i;
                shortest = distances[i];
            }
        }

        current = graph->nodes[shortest_index];
        visited[shortest_index] = 1;
        n_visited += 1;

        if(are_same_nodes(current, end)) {
            break;
        }

        for(i = 0; i < current->n_neighbors; i++) {
            neighbor = current->neighbors[i];
            index = get_node_index(graph, neighbor);
            alternative = distances[shortest_index] + current->weights[i];

            if(distances[index] > alternative) {
                distances[index] = alternative;
                previous[index] = shortest_index;
            }
        }
    }

    path_length = 0;
    u = get_node_index(graph, end);
    while(u != -1) {
        path_indices[path_length] = u;
        u = previous[u];
        path_length += 1;
    }

    Path *path = (Path *)malloc(sizeof(Path));
    char *p = (char *)malloc(path_length+1);
    for(i = 0; i < path_length; i++) {
        index = path_indices[path_length-i-1];
        p[i] = graph->nodes[index]->label;
    }
    p[path_length] = '\0';

    i = get_node_index(graph, end);
    path->path = p;
    path->cost = distances[i];
    return path;
}

void show_path(Path *path, int show_cost) {
    int i;
    printf("  path: ");
    for(i=0; i<strlen(path->path); i++) {
        printf("%c ", path->path[i]);
    }
    if(show_cost) {
        printf("cost: %lf", path->cost);
    }
    printf("\n");
}

void show_paths(Paths *paths, int show_cost) {
    int i;
    for(i=0; i<paths->n_paths; i++) {
        show_path(paths->paths[i], show_cost);
    }
}

void free_path(Path *path) {
    free(path->path);
    free(path);
}

void free_paths(Paths *paths) {
    int i;
    for(i=0; i<paths->n_paths; i++) {
        free_path(paths->paths[i]);
    }
    free(paths);
}
