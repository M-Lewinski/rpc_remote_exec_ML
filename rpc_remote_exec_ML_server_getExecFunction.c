#include "rpc_remote_exec_ML.h"

#ifndef ML_LL
#define ML_LL
#include "rpc_remote_exec_ML_LL.h"
#endif

#include "rpc_remote_exec_ML_def.h"

#include <sys/wait.h>

void getOUTPUT_START(getExecStructRequest *argp,getExecStructResponse  *result){
        list* node;
        int status=0;
        int waitpidstatus;
//        printf("OUTPUT_START\n");
		node = searchInList(argp->ID);
        result->packageType=argp->packageType;

        if(node->packetnr==argp->packageNR-1){
			node->packetnr=argp->packageNR;
            waitpidstatus=waitpid(node->pid, &status, WNOHANG); // Jeżeli funkcja wciąż jest wykonywana to zwraca 0 
            result->end=(waitpidstatus!=0);
		}else{
			result->end=0;
		}
        result->packageNR=node->packetnr;
        result->data=(char*)malloc(sizeof(char));
        result->data[0]=0;
        result->dataSize=status;
}
void readFromFile(getExecStructRequest *argp,getExecStructResponse  *result,char *filename){
    FILE *fileToOpen;
        list* node=NULL;
        int tmp=-1;
		node = searchInList(argp->ID);
        result->packageType=argp->packageType;


        if(node!=NULL && node->packetnr==argp->packageNR-1){
            result->data=(char*)malloc(sizeof(char)*(node->bufSize));
			node->packetnr=argp->packageNR;
            fileToOpen=fopen(filename,"r");
            if(fileToOpen!=NULL){
            tmp=fseek(fileToOpen,node->bufSize*argp->packageNRFromType,SEEK_SET);
            result->dataSize=fread(result->data,1,node->bufSize,fileToOpen);
            fclose(fileToOpen);
            }else{
                result->dataSize=0;
                result->data[0]=0;
            }
            // Określenie zakończenia pliku na podstawie liczbie wczytanych znaków
            result->end=result->dataSize<node->bufSize;
            result->packageNR=node->packetnr;
		}else{
            if(node==NULL){
            result->packageNR=0;
            }else
            result->packageNR=node->packetnr;
            result->data=(char*)malloc(sizeof(char));
            result->data[0]=0;
            result->dataSize=0;     
			result->end=0;
		}
}

void getOUTPUT_OUTPUT(getExecStructRequest *argp,getExecStructResponse  *result){
        list* node;
        //printf("OUTPUT_OUTPUT\n");
		node = searchInList(argp->ID);
        readFromFile(argp,result,node->outputFilename);
        
}
void getOUTPUT_ERROROUTPUT(getExecStructRequest *argp,getExecStructResponse  *result){
        list* node;
        //printf("OUTPUT_ERROROUTPUT\n");
		node = searchInList(argp->ID);
        readFromFile(argp,result,node->errorFilename);
}


void getOUTPUT_END(getExecStructRequest *argp,getExecStructResponse  *result){
        list* node;
        //printf("OUTPUT_END\n");
		node = searchInList(argp->ID);
        if(node!=NULL){
        
// przydaje sie tego ifa zacommitowac by miec podglad na to co sie dzieje


		if(fileExists(node->inputFilename) && remove(node->inputFilename) == -1)
        perror("No input file to remove");
		if(fileExists(node->functionFilename) && remove(node->functionFilename) == -1)
        perror("No function file to remove");
		if(fileExists(node->outputFilename) && remove(node->outputFilename) == -1)
        perror("No output file to remove");
		if(fileExists(node->errorFilename) && remove(node->errorFilename) == -1)
        perror("No error file to remove");
        }
        result->packageType=argp->packageType;
        result->end=1;
        result->packageNR=argp->packageNR;
        result->data=(char*)malloc(sizeof(char));
        result->data[0]=0;
        result->dataSize=0;
        removeFromList(argp->ID);
}

getExecStructResponse *
getexecfunction_1_svc(getExecStructRequest *argp, struct svc_req *rqstp)
{
	static getExecStructResponse  result;

    switch(argp->packageType){
        case OUTPUT_START:
        getOUTPUT_START(argp,&result);
        break;
        case OUTPUT_OUTPUT:
        getOUTPUT_OUTPUT(argp,&result);
        break;
        case OUTPUT_ERROROUTPUT:
        getOUTPUT_ERROROUTPUT(argp,&result);
        break;
        case OUTPUT_END:
        getOUTPUT_END(argp,&result);
        break;
    }

	/*
	 * insert server code here
	 */

	return &result;
}