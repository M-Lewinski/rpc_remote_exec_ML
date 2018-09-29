#include "rpc_remote_exec_ML.h"

typedef struct LLnode {
    u_long ID;
    int inputpacketnr;
    int pid;
    struct LLnode * next;
    struct LLnode * prev;
} list;

typedef struct LLnode list;


void addToList(u_long ID);
void removeFromList(u_long ID);
list* searchInList(u_long ID);