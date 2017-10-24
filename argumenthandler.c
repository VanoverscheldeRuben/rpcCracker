#include <stdio.h>
#include <stdlib.h>

#include "argumenthandler.h"

void setStrArgument(char ** variable, char * arg) {
    *variable = arg;
}

/**
 * @brief Check if the software has received enough information to work properly.
 * @param user_file_path
 * @param pass_file_path
 * @param ip
 * @return -1 if failed, 0 if succes
 */
int checkArguments(char * user_file_path, char * pass_file_path, char * ip) {
	if (user_file_path == NULL) {
		return 1;
	}
	else if (pass_file_path == NULL) {
		return 2;
	}
	else if (ip == NULL) {
		return 3;
        }
	
	return 0;
}

/**
 * @brief This function stops the program if the minimal arguments are not set.
 * @param argStatus
 */
void argExitError(int argStatus) {
	if (argStatus == 1) {
		printf("Error: exited with error code %d, path to userlist not set (-u)\n", argStatus);
		exit(EXIT_FAILURE);
	}
	else if (argStatus == 2) {
		printf("Error: exited with error code %d, path to passwordlist not set (-p)\n", argStatus);
		exit(EXIT_FAILURE);
	}
	else if (argStatus == 3) {
		printf("Error: exited with error code %d, ip not set (-i)\n", argStatus);
		exit(EXIT_FAILURE);
	}
	else {
		printf("Error: exited with unknown error code %d\n", argStatus);
		exit(EXIT_FAILURE);
	}
}
