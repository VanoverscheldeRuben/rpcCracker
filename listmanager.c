#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listmanager.h"

void initList(cList **list) {
    *list = malloc(sizeof(cList));
    initEntry(*list);
}

void initEntry(cList *list) {
    list->str = "";
    list->nextEntry = NULL;
}

void addEntry(cList *list) {
    list->nextEntry = malloc(sizeof(cList));
    list = list->nextEntry;
    initEntry(list);
}

void addToList(cList *head, char *str) {
    cList * current = head; // Go to the end of the list
    while (current->nextEntry != NULL)
        current = current->nextEntry;

    int length = strlen(str);
    if (current->str != NULL) // This entry is already filled. Create a new one
        addEntry(current); // Ptr is also changed to next entry
    
    current->str = malloc(length * sizeof(char));

    strcpy(current->str, str);
}

void displayList(cList *head) {
    cList * current = head;
    while (current != NULL) {
        puts(current->str);
        current = current->nextEntry;
    }
}
