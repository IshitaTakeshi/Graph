#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "search.h"


//append a single character to a string
char *append_char(char *string, char character) {
    int len = strlen(string);
    char *new_string = (char *)malloc(len+2);
    strncpy(new_string, string, len);
    new_string[len] = character;
    new_string[len+1] = '\0';
    return new_string;
}

char *depth_first_search_(Graph *graph, Node *start, Node *end, char *path_) {
    char *path = append_char(path_, start->label);

    if(start->label == end->label) {
        return path;
    }

    int i;
    for(i=0; i<start->n_neighbors; i++) {
        Node *node = start->neighbors[i];
        //do nothing if the node is already visited
        if(strchr(path, node->label) != NULL) {
            continue;
        }

        char *new_path = depth_first_search_(graph, node, end, path);
        if(new_path != NULL) {
            free(path);
            return new_path;
        }
    }

    free(path);
    return NULL;
}

char *depth_first_search(Graph *graph, Node *start, Node *end) {
    return depth_first_search_(graph, start, end, "");
}

void append_path(Paths *paths, char *path) {
    paths->paths = (char **)realloc(paths->paths, 
                                    (paths->n_paths+1)*sizeof(char *));
    paths->paths[paths->n_paths] = path;
    paths->n_paths += 1;
}

Paths *init_paths() {
    Paths *paths = (Paths *)malloc(sizeof(Paths));
    paths->n_paths = 0;
    return paths;
}

Paths *find_all_paths_(Graph *graph, Node *start, Node *end, char *path_) {
    char *path = append_char(path_, start->label);

    if(start->label == end->label) {
        Paths *p = init_paths();
        append_path(p, path);
        return p;
    }

    Paths *paths = init_paths();
    int i, j;
    for(i=0; i<start->n_neighbors; i++) {
        Node *node = start->neighbors[i];
        //do nothing if the node is already visited
        if(strchr(path, node->label) != NULL) {
            continue;
        }

        Paths *new_paths = find_all_paths_(graph, node, end, path);
        for(j=0; j<new_paths->n_paths; j++) {
            append_path(paths, new_paths->paths[j]);
        }
    }

    free(path);
    return paths;
}

Paths *find_all_paths(Graph *graph, Node *start, Node *end) {
    return find_all_paths_(graph, start, end, "");
}

void show_path(char *path) {
    int i;
    printf("  ");
    for(i=0; i<strlen(path); i++) {
        printf("%c ", path[i]);
    }
    printf("\n\n");
}

void show_paths(Paths *paths) {
    int i;
    printf("n_paths:%d\n", paths->n_paths);
    for(i=0; i<paths->n_paths; i++) {
        show_path(paths->paths[i]);
    }
}

void free_path(char* path) {
    free(path);
}

void free_paths(Paths *paths) {
    int i;
    for(i=0; i<paths->n_paths; i++) {
        free_path(paths->paths[i]);
    }
    free(paths);
}
