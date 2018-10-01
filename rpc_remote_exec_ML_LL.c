#include <stdlib.h>
#include "rpc_remote_exec_ML.h"
#include "rpc_remote_exec_ML_LL.h"

/*
typedef struct LLnode {
    u_long ID;
    int inputpacketnr;
    int pid;
    struct LLnode * next;
    struct LLnode * prev;
} list;*/

list * head = NULL;
list * end = NULL;


int fileExists(const char *filename)
{

   FILE *fp = fopen (filename, "r");
   if (fp!=NULL) fclose (fp);

   return (fp!=NULL);
}
void printListNode(list* node){
                printf("ID - %ld | packnr - %d | pid - %d | bufsize %d | inputFilename %s| functionFilename %s| outputFilename %s| errorFilename %s\n",node->ID,node->packetnr,node->pid,node->bufSize,node->inputFilename,node->functionFilename,node->outputFilename,node->errorFilename);

}

void printList(){
        list * iterator = head;
        while(iterator!=NULL){
            printListNode(iterator);
            iterator=iterator->next;
        }
}

void addToList(u_long ID){
    list * tmp = malloc(sizeof(list));
    list * iterator = end;



    tmp->ID=ID;
    tmp->packetnr=0;
    tmp->pid=0;
    tmp->next=NULL;
    tmp->prev=NULL;
    
    
    tmp->inputFilename=malloc(sizeof(char)*180);
    tmp->functionFilename=malloc(sizeof(char)*180);
    tmp->outputFilename=malloc(sizeof(char)*180);
    tmp->errorFilename=malloc(sizeof(char)*180);
    sprintf(tmp->inputFilename,"data/%lu%s",ID,"_input.txt");
    sprintf(tmp->functionFilename,"data/%lu%s",ID,"_function.txt");
    sprintf(tmp->outputFilename,"data/%lu%s",ID,"_output.txt");
    sprintf(tmp->errorFilename,"data/%lu%s",ID,"_error.txt");

    if(iterator==NULL && head==NULL){
        head=tmp;
        end=head;
        tmp->next=NULL;
        tmp->prev=NULL;
    }else{
        if(iterator->prev==NULL){
            iterator->next=tmp;
            tmp->prev=iterator;
            tmp->next=NULL;
            end=tmp;
        }else{
            end->next=tmp;
            tmp->prev=end;
            tmp->next=NULL;
        }
    }
}



list* searchInList(u_long ID){
    list * iterator = head;
    while(TRUE){
        if(iterator==NULL){
            return NULL;
        }
        if(iterator->ID==ID){
            return iterator;
        }else{
            iterator=iterator->next;
        }
    }
}

void removeFromList(u_long ID){
    list * curElement = searchInList(ID);
    if(curElement==NULL)
        return;

    if(head==curElement){
        head=head->next;
    }
    if(end=curElement){
        end=end->prev;
    }
    if(curElement->prev!=NULL){
        curElement->prev->next=curElement->next;
    }
    if(curElement->next!=NULL){
        curElement->next->prev=curElement->prev;
    }
    free(curElement);
}
