#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "listmanager.h"
#include "mutator.h"

cList* createMutatedListOfWord(char *str) {
    int listLength = 0;
    cList * list = NULL;
    initList(&list);
    cList *head = NULL;
    addToList(list, str); // Add original password to list as well


    /***** Password mutation procedures *****/
    listLength += firstCharCapitalRestLowercase(list, str);

    head = list;
    int i = 0;
    int end = listLength;
    while (head != NULL && i <= end) {
        listLength += appendDigits(list, head->str, 3);

        head = head->nextEntry;
        i++;
    }


    return list;
}

int appendDigits(cList *list, char *str, int digits) {
    int nodesAdded = 0;
    int length = strlen(str);

    char *newStr = malloc((length + 1) * sizeof(char));

    int limit = round(pow(10, digits));
    for (int i = 0; i < limit; i++) {
        sprintf(newStr, "%s%d", str, i);
        addToList(list, newStr);
        nodesAdded++;
    }

    return nodesAdded;
}

int firstCharCapitalRestLowercase(cList *list, char *str) {
    int nodesAdded = 0;
    int length = strlen(str);

    if (length > 0) {
        char *newStr = malloc(length * sizeof(char));
        strcpy(newStr, str);

        if (length > 1) {
            for (int i = 0; newStr[i]; i++) {
                newStr[i] = tolower(newStr[i]);
            }
        }

        newStr[0] = toupper(newStr[0]);
        addToList(list, newStr);
        nodesAdded++;
    }

    return nodesAdded;
}
