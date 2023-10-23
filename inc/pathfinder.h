#ifndef PATHFINDER_H
#define PATHFINDER_H

#define INFINITY_VALUE 3000000

#include <limits.h>
#include <stdio.h>
#include "../libmx/inc/libmx.h"

typedef struct {
    int distance;
    int predecessor;
} Vertex;

typedef struct {
    char *str_file;
    char **file_lines;
    char **islands;
    int **adjacency_matrix;
    int **shortest_paths_matrix;
    int *current_path;
    int num_of_islands;
} PathfinderData;


void check_print_errors(char *file, char *argv[]);
void invalid_line(int n);
char **parse_islands_data(char *str_file, int isl_nbr);
int **create_bridge_matrix(char **lines, char **vertices, int size);
int **algoritm_dijkstra(int **matrix, int numberOfVert);
void print(char **islands, int **adjacency_matrix, int **shortest_paths_matrix, int num_of_islands, int *current_path, int num_of_steps);
void pathfinder(char *argv[]);

#endif
