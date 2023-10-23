#include "../inc/pathfinder.h"

static int isFileEmpty(char *file) {
    return file == NULL;
}

static int isValidIslandNumber(char *line) {
    if (!mx_isdigit(line[0]) || line[0] == '0' || line[0] == '-') {
        return 0;
    }
    return 1;
}

static int isLineValid(const char *line, int lineNumber) {
    int i = 0;
    int temp = 0;

    while (mx_isalpha(line[i])) {
        i++;
    }

    if (i == 0 || line[i] != '-') {
        invalid_line(lineNumber);
        return 0;
    }

    i++;
    temp = i;

    while (mx_isalpha(line[i])) {
        i++;
    }

    if (i == temp || line[i] != ',') {
        invalid_line(lineNumber);
        return 0;
    }

    i++;
    temp = i;

    while (mx_isdigit(line[i])) {
        i++;
    }

    if (i == temp || line[i] != '\0') {
        invalid_line(lineNumber);
        return 0;
    }

    return 1;
}

static int hasDuplicateBridges(char **temp, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (temp[j][0] == '\0' || j == i) {
                continue;
            }
            if (mx_strcmp(temp[i], temp[j]) == 0) {
                mx_printerr("error: duplicate bridges\n");
                return 1;
            }
        }
    }
    return 0;
}

void check_print_errors(char *file, char *argv[]) {
   if (isFileEmpty(file)) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(0);
    }
    
 
    char **file_lines = mx_strsplit(file, '\n');
    int lines_count = 0;
    while (file_lines[lines_count]) {
        lines_count++;
    }

    if (!isValidIslandNumber(file_lines[0])) {
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }

    for (int i = 1; i < lines_count; i++) {
        if (!isLineValid(file_lines[i], i + 1)) {
            exit(0);
        }
    }

    char **temp = (char **)malloc((lines_count + 1) * sizeof(char *));
    for (int i = 0; i < lines_count; i++) {
        temp[i] = mx_strndup(file_lines[i], mx_get_char_index(file_lines[i], ','));
    }
    temp[lines_count] = NULL;

    if (hasDuplicateBridges(temp, lines_count)) {
        exit(0);
    }

    mx_del_strarr(&temp);
    mx_del_strarr(&file_lines);
}





