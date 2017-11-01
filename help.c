#include <stdio.h>
#include <stdlib.h>

#include "help.h"

void displayHelpScreen() {
	puts("Usage: rpccracker [OPTIONS...] [-u username] [-p passwordlist] [-i ipaddress]");
	puts("");
	
	puts("Minimal main usage options");
	puts("\t-u\t\tname of user to enumerate");
	puts("\t-p\t\tpath to the password table");
	puts("\t-i\t\tip address of the target");
	puts("");
	
	puts("Help options");
	puts("\t-h\t\tdisplay help screen (this one)");
	puts("");
	
	puts("");
}
