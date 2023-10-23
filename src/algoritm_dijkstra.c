#include "../inc/pathfinder.h"

int **algoritm_dijkstra(int **matrix, int numberOfVert) {
    int **temp = (int **)malloc(numberOfVert * sizeof(int *));
    for (int i = 0; i < numberOfVert; i++) {
        temp[i] = (int *)malloc(numberOfVert * sizeof(int));
    }

    for (int start = 0; start < numberOfVert; start++) {
        
        Vertex *vertices = (Vertex *)malloc(numberOfVert * sizeof(Vertex));
        for (int i = 0; i < numberOfVert; i++) {
            vertices[i].distance = INT_MAX; 
            vertices[i].predecessor = -1;
        }
        vertices[start].distance = 0;
        
        int *visited = (int *)malloc(numberOfVert * sizeof(int));
        for (int i = 0; i < numberOfVert; i++) {
            visited[i] = 0;
        }

        
        for (int i = 0; i < numberOfVert; i++) {
            int minDistance = INT_MAX;
            int u = -1;

            for (int j = 0; j < numberOfVert; j++) {
                if (!visited[j] && vertices[j].distance < minDistance) {
                    minDistance = vertices[j].distance;
                    u = j;
                }
            }

            visited[u] = 1;

            for (int v = 0; v < numberOfVert; v++) {
                if (!visited[v] && matrix[u][v] != INFINITY_VALUE) {
                    int alt = vertices[u].distance + matrix[u][v];
                    if (alt < vertices[v].distance) {
                        vertices[v].distance = alt;
                        vertices[v].predecessor = u;
                    }
                }
            }
        }

        for (int i = 0; i < numberOfVert; i++) {
            temp[start][i] = vertices[i].distance;
        }

        free(vertices);
        free(visited);
    }

    return temp;
}
