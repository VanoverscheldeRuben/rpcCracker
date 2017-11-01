#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumenthandler.h"
#include "help.h"
#include "cmd.h"
#include "listmanager.h"
#include "filereader.h"

#define ARG_USER "-u"
#define ARG_PASSWD "-p"
#define ARG_IP "-i"
#define ARG_HELP "-h"

int main(int argc, char **argv)
{
    char * username = NULL;
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
                setStrArgument(&username, argv[i]);
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
    argCheck = checkArguments(username, pass_file_path, ip);
    if (argCheck != 0)
        argExitError(argCheck);

    
    /***** Password guess code *****/
    applyPasswordFileDirectly(ip, username, pass_file_path);


    puts(""); // Add extra line to cleanly separate the output at the end
    exit(EXIT_SUCCESS);
}
