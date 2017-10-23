#include <cmd.h>

/**
 * @brief This function creates a command to execute the rpcclient testme command
 * @param command
 * @param user_line
 * @param pass_line
 * @param ip
 */
void createRcpClientTestmeCmd(char * command, char * user_line, char * pass_line, char * ip) {
	sprintf(command, "rpcclient -U \"%s\"%\"%s\" -c \"testme\" %s > /dev/null 2>&1", user_line, pass_line, ip);
}

/**
 * @brief This function executes a command to execute the rpcclient testme command
 * @param command
 * @param user_line
 * @param pass_line
 * @param ip
 * @return The result code of rpcclient. 0 means that the cmd was successful
 */
int executeRcpClientTestmeCmd(char * command, char * user_line, char * pass_line, char * ip) {
	createRcpClientTestmeCmd(char * command, char * user_line, char * pass_line, char * ip)
	
	return system(command); // Execute command
}