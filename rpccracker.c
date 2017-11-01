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

    /***** Read data lists  *****/
    /*** Read password list  ***/
    cList * passList = NULL;
    initList(&passList);
    cList *passLoader = passList;

    loadFileIntoList(passLoader, pass_file_path);
    //displayList(passList);

    /*** Read user list  ***/
    cList * userList = NULL;
    initList(&userList);
    cList *userLoader = userList;

    loadFileIntoList(userLoader, user_file_path);
    //displayList(userList);


    /***** Password guess code *****/
    cList * currUser = userList;
    while (currUser != NULL) {
        int found_pass = 0;

        printf("Trying user %s\n", currUser->str);

        cList * currPass = passList; 
        while (currPass!= NULL && found_pass == 0) {
            int output = 1;

            output = executeRcpClientTestmeCmd(command, currUser->str, currPass->str, ip);
            if (output == 0) {
                printf("Valid credentials for host %s:\n", ip);
                printf("\tUsername:\t%s\n", currUser->str);
                printf("\tPassword:\t%s\n", currPass->str);
                printf("\n");

                found_pass = 1;
            }

            currPass = currPass->nextEntry;
        }

        if (found_pass == 0) {
            printf("No password match for user %s...\n", currUser->str);
            printf("\n");
        }

        currUser = currUser->nextEntry;
    }


    /*** Free allocated memory ***/
    freeList(userList);
    freeList(passList);


    puts(""); // Add extra line to cleanly separate the output at the end
    exit(EXIT_SUCCESS);
}
