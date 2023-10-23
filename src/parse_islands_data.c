#include "../inc/pathfinder.h"
  
char** parse_islands_data(char *str_file, int isl_nbr) {
    char *str = mx_strdup(str_file);
    int lines_count = 0;
    char **islands = (char **)malloc((isl_nbr + 1) * sizeof(char *));
    char **temp = mx_strsplit(str, '\n');
    
    if (temp[0] == NULL || mx_strlen(temp[0]) != 1 || !mx_isdigit(temp[0][0])) {
        invalid_line(1);
        exit(0);
    }
    
    for (int i = 0; i < mx_strlen(str); i++) {
        if (str[i] == '-' || str[i] == ',' || str[i] == '\n' || mx_isdigit(str[i])) {
            str[i] = ' ';
        }
    }

    char *str_no_spaces = mx_del_extra_spaces(str);
    char **temp1 = mx_strsplit(str_no_spaces, ' ');
    while (temp1[lines_count]) {
        lines_count++;
    }
    
    for (int i = 0, count = 1; i < lines_count; i += 2, count++) {
        if (mx_strcmp(temp1[i], temp1[i + 1]) == 0) {
            invalid_line(count + 1);
        }
    }
    
    int k = 0;
    for (int i = 0; i < lines_count; i++) {
        for (int j = 0; j < lines_count; j++) {
            if (temp1[j][0] == ' ' || j == i)
                continue;
            if (mx_strcmp(temp1[i], temp1[j]) == 0)
                temp1[j][0] = ' ';
        }
        if(mx_isalpha(temp1[i][0])) {
            islands[k] = mx_strdup(temp1[i]);
            k++;
        }
    }
    islands[isl_nbr] = NULL;

    int count = 0;
    for (int i = 0; i < lines_count; i++) {
        if (temp1[i][0] != ' ') {
            count++;
        }
    }
    if (count != isl_nbr) {
        mx_del_strarr(&temp1);
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }

    mx_strdel(&str);
    mx_strdel(&str_no_spaces);
    mx_del_strarr(&temp1);
    mx_del_strarr(&temp);

    return islands;
}

