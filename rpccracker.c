#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumenthandler.h"
#include "help.h"
#include "cmd.h"

#define ARG_USER "-u"
#define ARG_PASSWD "-p"
#define ARG_IP "-i"
#define ARG_HELP "-h"

int main(int argc, char **argv)
{
    char * user_file_path = NULL;
    char * pass_file_path = NULL;
    char * ip = NULL;
    int help;
	
    int argCheck;

    char command[100];

    /***** Handle arguments *****/
    /*** Load arguments ***/
    for (int i = 1; i < argc; i++) { // i = 1 because the first arg = the name of the exe
        if (argv[i][0] == '-') {
            if (strcmp(ARG_USER, argv[i]) == 0) {
                i++;
                setStrArgument(&user_file_path, argv[i]);
            }
            else if (strcmp(ARG_PASSWD, argv[i]) == 0) {
                i++;
                setStrArgument(&pass_file_path, argv[i]);
            }
            else if (strcmp(ARG_IP, argv[i]) == 0) {
                i++;
                setStrArgument(&ip, argv[i]);
            }
		else if (strcmp(ARG_HELP, argv[i]) == 0) {
                help = 1;
            }
            else {
                printf("Error: argument %s not recognised\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    }
	
    /*** Check if the user requested the help screen ***/
     if (help == 1) {
        displayHelpScreen();
        exit(EXIT_SUCCESS); // It's either using the app, or getting help
    }
	
    /*** Check arguments for errors ***/
    /** Check if minimal arguments are set **/
    argCheck = checkArguments(user_file_path, pass_file_path, ip);
    if (argCheck != 0)
        argExitError(argCheck);


    /***** Read user and password lists *****/
    FILE *user_fp;
    char *user_line = NULL;
    size_t user_len = 0;
    ssize_t user_read;

    user_fp = fopen(user_file_path, "r");

    if (user_fp == NULL) {
        printf("Error: user list %s does not exist", user_file_path);
        exit(EXIT_FAILURE);
    }

    while ((user_read = getline(&user_line, &user_len, user_fp)) != -1) {
        FILE *pass_fp;
        char *pass_line = NULL;
        size_t pass_len = 0;
        ssize_t pass_read;
		
	pass_fp = fopen(pass_file_path, "r");
	if (pass_fp == NULL) {
	    printf("Error: password list %s does not exist", pass_file_path);
            exit(EXIT_FAILURE);
	}

        printf("\n");
        printf("Trying user %s\n", user_line);

        user_line[strcspn(user_line, "\n")] = 0; // Remove trailing newline
        
        while ((pass_read = getline(&pass_line, &pass_len, pass_fp)) != -1) {
            int output;
            pass_line[strcspn(pass_line, "\n")] = 0; // Remove trailing newline

            output = executeRcpClientTestmeCmd(command, user_line, pass_line, ip);
            if (output == 0) {
                printf("\n");
                printf("Valid credentials for host %s:\n", ip);
                printf("\tUsername:\t%s\n", user_line);
                printf("\tPassword:\t%s\n", pass_line);
            }
        }
    
        if (pass_line)
            free(pass_line);

        if (pass_fp)
            fclose(pass_fp);
    }

    if (user_line)
        free(user_line);

    puts(""); // Add extra line to cleanly separate the output at the end
    exit(EXIT_SUCCESS);
}
