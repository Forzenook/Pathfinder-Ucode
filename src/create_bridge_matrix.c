#include "../inc/pathfinder.h"

static char **parsePath(const char *line) {
    char **strarr = (char **)malloc(4 * sizeof(char *));
    for (int i = 0; i <= 3; i++) {
        strarr[i] = NULL;
    }

    char *token;
    int index = 0;
    char delim = '-';

    while ((token = mx_strndup(line, mx_get_char_index(line, delim))) != NULL) {
        strarr[index] = token;
        line += mx_get_char_index(line, delim) + 1;
        index++;

        if (index == 3) {
            break;
        }

        delim = (index == 1) ? ',' : '\n';
    }

    return strarr;
}

int **create_bridge_matrix(char **lines, char **vertices, int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            matrix[i][j] = INFINITY_VALUE;
        }
    }

    for (int i = 1; lines[i]; i++) {
        char **temp = parsePath(lines[i]);

        if (mx_atoi(temp[2]) >= INT_MAX) {
            mx_printerr("error: sum of bridges lengths is too big\n");
            exit(0);
        }

        int index1 = mx_get_index(vertices, temp[0]);
        int index2 = mx_get_index(vertices, temp[1]);
        matrix[index1][index2] = mx_atoi(temp[2]);
        matrix[index2][index1] = mx_atoi(temp[2]);

        mx_del_strarr(&temp);
    }

    return matrix;
}

