#include "../inc/pathfinder.h"

void invalid_line(int n) {
    mx_printerr("error: line ");
    mx_printerr(mx_itoa(n));
    mx_printerr(" is not valid\n");
    
    exit(0);
}

