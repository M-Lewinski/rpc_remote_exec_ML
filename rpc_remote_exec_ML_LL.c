#include <stdlib.h>
#include "rpc_remote_exec_ML.h"


typedef struct LLnode {
    u_long ID;
    int inputpacketnr;
    int pid;
    struct LLnode * next;
    struct LLnode * prev;
} list;

list * head = NULL;
list * end = NULL;

void printListNode(list* node){
                printf("ID - %ld | packnr - %d | pid - %d\n",node->ID,node->inputpacketnr,node->pid);

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
    tmp->inputpacketnr=0;
    tmp->pid=0;
    tmp->next=NULL;
    tmp->prev=NULL;
    
    

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
