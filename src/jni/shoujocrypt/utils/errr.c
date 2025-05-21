#include <stdio.h>
#include <stdlib.h>

#include <errr.h>

void handle_err() {
    fprintf(stderr, "An error occurred!\\n");
    exit(EXIT_FAILURE);
}