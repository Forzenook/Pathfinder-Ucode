#include "../inc/pathfinder.h"

static void printRoute(char **islands, int **adjacency_matrix, int **shortest_paths_matrix, int *current_path, int num_of_steps) {
    mx_printstr("========================================\n");
    mx_printstr("Path: ");
    mx_printstr(islands[current_path[1]]);
    mx_printstr(" -> ");
    mx_printstr(islands[current_path[0]]);
    mx_printstr("\nRoute: ");
    
    if (num_of_steps > 2) {
        for (int i = 1; i < num_of_steps + 1; i++) {
            mx_printstr(islands[current_path[i]]);
            if (i < num_of_steps) {
                mx_printstr(" -> ");
            }
        }
    } else {
        mx_printstr(islands[current_path[1]]);
        mx_printstr(" -> ");
        mx_printstr(islands[current_path[0]]);
    }
    
    mx_printstr("\nDistance: ");
    
    if (num_of_steps > 2) {
        for (int i = 1; i < num_of_steps; i++) {
            int distance = adjacency_matrix[current_path[i]][current_path[i + 1]];
            mx_printint(distance);
            if (i < num_of_steps - 1) {
                mx_printstr(" + ");
            }
        }
        mx_printstr(" = ");
        mx_printint(shortest_paths_matrix[current_path[0]][current_path[1]]);
    } else {
        mx_printint(shortest_paths_matrix[current_path[0]][current_path[1]]);
    }
    
    mx_printstr("\n========================================\n");
}

static void printPaths(char **islands, int **adjacency_matrix, int **shortest_paths_matrix, int num_of_islands, int *current_path, int num_of_steps, int start) {
    int end = current_path[num_of_steps];
    for (int i = 0; i < num_of_islands; i++) {
        if ((adjacency_matrix[end][i] == shortest_paths_matrix[end][start] - shortest_paths_matrix[i][start])
            && i != current_path[num_of_steps]) {
            current_path[num_of_steps + 1] = i;
            printPaths(islands, adjacency_matrix, shortest_paths_matrix, num_of_islands, current_path, num_of_steps + 1, start);
        }
    }
    if (current_path[num_of_steps] == start) {
        printRoute(islands, adjacency_matrix, shortest_paths_matrix, current_path, num_of_steps);
    }
}

void print(char **islands, int **adjacency_matrix, int **shortest_paths_matrix, int num_of_islands, int *current_path, int num_of_steps) {
    int start = current_path[0];
    printPaths(islands, adjacency_matrix, shortest_paths_matrix, num_of_islands, current_path, num_of_steps, start);
}


