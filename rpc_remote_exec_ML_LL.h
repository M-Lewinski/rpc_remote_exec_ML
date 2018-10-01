#include "rpc_remote_exec_ML.h"

struct LLnode {
    u_long ID;
    int packetnr;
    int pid;
    int bufSize;
    char *inputFilename;
    char *functionFilename;
    char *outputFilename;
    char *errorFilename;
    struct LLnode * next;
    struct LLnode * prev;
};

typedef struct LLnode list;
int fileExists(const char *filename);
void addToList(u_long ID);
void removeFromList(u_long ID);
list* searchInList(u_long ID);
void printListNode(list* node);
void printList();