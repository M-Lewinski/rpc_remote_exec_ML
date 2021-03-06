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
//		printf("INPUT_START\n");
		addToList(argp->ID); // Dodaj Id do listy dwukierunkowej
		list* node= searchInList(argp->ID); // Pobierz informacje dotyczące wykonywanego zadaina
		node->bufSize=argp->dataSize; // Określenie jakiej wielkości buforem będzie prowadzona komunikacja
		result->lastCorrectPackageNR=0; // Ostatni numer odebranej paczki po stronie servera

		// usuwanie plików jeżeli istnieją
		if(fileExists(node->inputFilename) && remove(node->inputFilename) == -1)
        perror("No input file to remove");
		if(fileExists(node->functionFilename) && remove(node->functionFilename) == -1)
        perror("No function file to remove");
		if(fileExists(node->outputFilename) && remove(node->outputFilename) == -1)
        perror("No output file to remove");
		if(fileExists(node->errorFilename) && remove(node->errorFilename) == -1)
        perror("No error file to remove");
	
}
void saveToFileInput(runExecStructRequest *argp,runExecStructResponse  *result,int filenameType){
		list* node;
		FILE *pFile;
		char *filename;
//		printf("INPUT_FUNCTION\n");
		node = searchInList(argp->ID); 
		// sprawdzenie czy zapisywane dane są wykonywaną funkcją lub strumieniem wejściowym
		filename=filenameType==0?node->functionFilename:node->inputFilename; 
		
		// Sprawdzenie czy wysłana paczka jest kolejną oczekiwaną przez serwer
		if(node->packetnr==argp->packageNR-1){
			node->packetnr=argp->packageNR;
			pFile = fopen(filename, "a"); // Dodawanie na końcu pliku
			fprintf(pFile,"%s", argp->data);
			fclose(pFile);
		}

		result->lastCorrectPackageNR=node->packetnr;
}
void caseINPUT_FUNCTION(runExecStructRequest *argp,runExecStructResponse  *result){
		saveToFileInput(argp,result,0);
}
void caseINPUT_INPUT(runExecStructRequest *argp,runExecStructResponse  *result){

		saveToFileInput(argp,result,1);
}

void run(list* node){
	FILE *functionfile;
	int inputfile;
	int outputfile;
	int errorfile;
	

	functionfile = fopen( node->functionFilename , "r");
	outputfile = open( node->outputFilename, O_WRONLY | O_CREAT, 0644);
	errorfile = open( node->errorFilename, O_WRONLY | O_CREAT, 0644);


	if (functionfile) {
		// Obliczenie wielkości znaków potrzbenych na funkcję
		fseek(, 0, SEEK_END);
		int fileSize = ftell(f);
		fseek(f, 0, SEEK_SET);
		char* functionToRun = (char*)malloc(fileSize +1);
		fgets(functionToRun, fileSize, functionfile);
		functionToRun[fileSize] = 0;
		dup2(outputfile,1); // Duplikacja deskryptora plików
		dup2(errorfile,2);

		if(fileExists(node->inputFilename)){
			inputfile = open( node->inputFilename, O_RDONLY);
			dup2(inputfile,0);
		}
		system(functionToRun);


		fclose(functionfile);
	}

	
	exit(1);
}

void caseINPUT_END(runExecStructRequest *argp,runExecStructResponse  *result){
		list* node;

//		printf("INPUT_END\n");
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