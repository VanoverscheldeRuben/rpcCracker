#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listmanager.h"
#include "filereader.h"

void loadFileIntoList(cList *list, char *path) {
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t entry_read;

    fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error: list %s does not exist", path);
        exit(EXIT_FAILURE);
    }

    while ((entry_read = getline(&line, &length, fp)) != -1) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline
        addToList(list, line);   
    }
}
