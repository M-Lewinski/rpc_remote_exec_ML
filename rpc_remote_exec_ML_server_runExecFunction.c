#include "rpc_remote_exec_ML.h"
#ifndef ML_LL
#define ML_LL
#include "rpc_remote_exec_ML_LL.h"
#endif
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include "rpc_remote_exec_ML_def.h"


void caseINPUT_START(runExecStructRequest *argp,runExecStructResponse  *result){
		printf("INPUT_START\n");
		addToList(argp->ID);
		list* node= searchInList(argp->ID);
		node->bufSize=argp->dataSize;
		result->lastCorrectPackageNR=0;


		if(fileExists(node->inputFilename) && remove(node->inputFilename) == -1)
        perror("No input file to remove");
		if(fileExists(node->functionFilename) && remove(node->functionFilename) == -1)
        perror("No function file to remove");
		if(fileExists(node->outputFilename) && remove(node->outputFilename) == -1)
        perror("No output file to remove");
		if(fileExists(node->errorFilename) && remove(node->errorFilename) == -1)
        perror("No error file to remove");
		/*		
		//usuwanie ewentualnie istenijacego pliku;
		char filenameWithoutEnd[180];
		char filenameWithEnd[180];

		char IDstring[80];

		sprintf(IDstring,"%lu",argp->ID);
		strcpy(filenameWithoutEnd,"data/");
		strcat(filenameWithoutEnd,IDstring);

		
		strcpy(filenameWithEnd,filenameWithoutEnd);	
		strcat(filenameWithEnd,"_input.txt");	
		if(fileExists(filenameWithEnd) && remove(filenameWithEnd) == -1)
        perror("No input file to remove");


		strcpy(filenameWithEnd,filenameWithoutEnd);	
		strcat(filenameWithEnd,"_function.txt");	
		if(fileExists(filenameWithEnd) && remove(filenameWithEnd) == -1)
        perror("No function file to remove");

		
		strcpy(filenameWithEnd,filenameWithoutEnd);	
		strcat(filenameWithEnd,"_output.txt");	
		if(fileExists(filenameWithEnd) && remove(filenameWithEnd) == -1)
        perror("No output file to remove");
		
		
		strcpy(filenameWithEnd,filenameWithoutEnd);	
		strcat(filenameWithEnd,"_error.txt");	
		if(fileExists(filenameWithEnd) && remove(filenameWithEnd) == -1)
        perror("No error file to remove");
		*/
		//printList();
}
void saveToFileInput(runExecStructRequest *argp,runExecStructResponse  *result,char *fileNameEnd){
		list* node;
		FILE *pFile;
		char filename[180];
		char IDstring[80];
		printf("INPUT_FUNCTION\n");
		node = searchInList(argp->ID);
		//printListNode(node);

		sprintf(IDstring,"%lu",argp->ID);
		strcpy(filename,"data/");
		strcat(filename,IDstring);
		strcat(filename,fileNameEnd);

		if(node->packetnr==argp->packageNR-1){
			node->packetnr=argp->packageNR;
			pFile = fopen(filename, "a");
			//zapisywanie do pliku?
			printf("tresc funkcji - %s\n",argp->data);
			fprintf(pFile,"%s", argp->data);
			fclose(pFile);
		}else{
			printf("zly numer\n");
		}
		result->lastCorrectPackageNR=node->packetnr;
}
void caseINPUT_FUNCTION(runExecStructRequest *argp,runExecStructResponse  *result){
		saveToFileInput(argp,result,"_function.txt");
}
void caseINPUT_INPUT(runExecStructRequest *argp,runExecStructResponse  *result){

		saveToFileInput(argp,result,"_input.txt");
}

void run(list* node){
	FILE *functionfile;
	int inputfile;
	int outputfile;
	int errorfile;

	char filenameWithoutEnd[180];
	char filenamefunctionfile[180];
	char filenameInputfile[180];
	char filenameOutputfile[180];
	char filenameErrorfile[180];


	char functionToRun[1024];

	char IDstring[80];

	sprintf(IDstring,"%lu",node->ID);
	strcpy(filenameWithoutEnd,"data/");
	strcat(filenameWithoutEnd,IDstring);
	strcpy(filenamefunctionfile,filenameWithoutEnd);	
	strcat(filenamefunctionfile,"_function.txt");
	strcpy(filenameInputfile,filenameWithoutEnd);	
	strcat(filenameInputfile,"_input.txt");
	strcpy(filenameOutputfile,filenameWithoutEnd);	
	strcat(filenameOutputfile,"_output.txt");
	strcpy(filenameErrorfile,filenameWithoutEnd);	
	strcat(filenameErrorfile,"_error.txt");
		
	/*if(fileExists(filenameInputfile)){

	}*/

	functionfile = fopen( filenamefunctionfile , "r");
	outputfile = open( filenameOutputfile, O_WRONLY | O_CREAT, 0644);
	errorfile = open( filenameErrorfile, O_WRONLY | O_CREAT, 0644);
	if (functionfile) {
		fgets(functionToRun, 180, functionfile);
		dup2(outputfile,1);
		dup2(errorfile,2);

		if(fileExists(filenameInputfile)){
			inputfile = open( filenameInputfile, O_RDONLY);
			dup2(inputfile,0);
		}
		printf("uruchomienie funkcji: %s\n",functionToRun);
		system(functionToRun);


		fclose(functionfile);
	}
	printf("zakonczenie funkcji\n");
	
	exit(1);
}

void caseINPUT_END(runExecStructRequest *argp,runExecStructResponse  *result){
		list* node;

		printf("INPUT_END\n");
		node = searchInList(argp->ID);
		if(node->packetnr==argp->packageNR-1){
			node->packetnr=argp->packageNR;
			if ((node->pid = fork()) == 0){
				run(node);
			}		
		
		
		}
		result->lastCorrectPackageNR=node->packetnr;
}

runExecStructResponse *
runexecfunction_1_svc(runExecStructRequest *argp, struct svc_req *rqstp)
{
	static runExecStructResponse  result;

	switch(argp->packageType){
		case INPUT_START:
		caseINPUT_START(argp,&result);
		break;
		case INPUT_FUNCTION:
		caseINPUT_FUNCTION(argp,&result);
		break;
		case INPUT_INPUT:
		caseINPUT_INPUT(argp,&result);
		break;
		case INPUT_END:
		caseINPUT_END(argp,&result);		
		break;
	}

	/*
	 * insert server code here
	 */

	return &result;
}