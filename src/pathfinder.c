#include "../inc/pathfinder.h"

static void free_resources(PathfinderData *data) {
    mx_strdel(&(data->str_file));
    mx_del_strarr(&(data->file_lines));
    mx_del_strarr(&(data->islands));

    for (int i = 0; i < data->num_of_islands; i++) {
        free(data->adjacency_matrix[i]);
        free(data->shortest_paths_matrix[i]);
    }
    
    free(data->adjacency_matrix);
    free(data->shortest_paths_matrix);
    free(data->current_path);
}

void pathfinder(char *argv[]) {
    PathfinderData data = {0};

    if (open(argv[1], O_RDONLY) < 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        exit(1);
    }

    data.str_file = mx_file_to_str(argv[1]);
    check_print_errors(data.str_file, argv);

    data.file_lines = mx_strsplit(data.str_file, '\n');
    data.num_of_islands = mx_atoi(data.file_lines[0]);

    data.islands = parse_islands_data(data.str_file, data.num_of_islands);
    data.adjacency_matrix = create_bridge_matrix(data.file_lines, data.islands, data.num_of_islands);
    data.shortest_paths_matrix = algoritm_dijkstra(data.adjacency_matrix, data.num_of_islands);
    data.current_path = (int *)malloc((data.num_of_islands + 1) * sizeof(int));
    int num_of_steps = 1;

    for (int start = 0; start < data.num_of_islands; start++) {
        for (int end = start + 1; end < data.num_of_islands; end++) {
            data.current_path[1] = start;
            data.current_path[0] = end;
            print(data.islands, data.adjacency_matrix, data.shortest_paths_matrix, data.num_of_islands, data.current_path, num_of_steps);
        }
    }

    free_resources(&data);
}

