typedef struct cList cList;
struct cList {
    char * str;
    cList * nextEntry;
};

void initList(cList **list);
void initEntry(cList *list);
void addEntry(cList *list);
void addToList(cList *list, char *str);
void displayList(cList *list);
void freeList(cList *head);
