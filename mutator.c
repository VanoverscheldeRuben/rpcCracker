#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "listmanager.h"
#include "mutator.h"

cList* createMutatedListOfWord(char *str) {
    cList * list = NULL;
    initList(&list);
    addToList(list, str); // Add original password to list as well

    firstCharCapitalRestLowercase(list, str);

    return list;
}

void firstCharCapitalRestLowercase(cList *list, char *str) {
    int length = strlen(str);

    char *newStr = malloc(length * sizeof(char));
    strcpy(newStr, str);

    if (length > 0) {
        if (length > 1) {
            for (int i = 0; newStr[i]; i++) {
                newStr[i] = tolower(newStr[i]);
            }
        }

        newStr[0] = toupper(newStr[0]);
    }

    addToList(list, newStr);
}
