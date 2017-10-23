#include <help.h>

void displayHelpScreen() {
	puts("Usage: rpccracker [OPTIONS...] [-u userlist] [-p passwordlist] [-i ipaddress]");
	puts("");
	puts("\t-u\t\tpath to the file that contains all the usernames to enumerate");
	puts("\t-p\t\tpath to the password table");
	puts("\t-i\t\tip address of the target");
	puts("");
	puts("");
}