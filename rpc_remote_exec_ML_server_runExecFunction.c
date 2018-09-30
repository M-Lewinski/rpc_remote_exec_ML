#include "rpc_remote_exec_ML.h"
#include "rpc_remote_exec_ML_LL.h"
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>

int fileExists(const char *filename)
{

   FILE *fp = fopen (filename, "r");
   if (fp!=NULL) fclose (fp);

   return (fp!=NULL);
}

void caseINPUT_START(runExecStructRequest *argp,runExecStructResponse  *result){
		printf("INPUT_START\n");
		addToList(argp->ID);
		result->lastCorrectPackageNR=0;
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

		if(node->inputpacketnr==argp->packageNR-1){
			node->inputpacketnr=argp->packageNR;
			pFile = fopen(filename, "a");
			//zapisywanie do pliku?
			printf("tresc funkcji - %s\n",argp->data);
			fprintf(pFile, argp->data);
			fclose(pFile);
		}else{
			printf("zly numer\n");
		}
		result->lastCorrectPackageNR=node->inputpacketnr;
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
	exit(1);
}

void caseINPUT_END(runExecStructRequest *argp,runExecStructResponse  *result){
		list* node;

		printf("INPUT_END\n");
		node = searchInList(argp->ID);
		if(node->inputpacketnr==argp->packageNR-1){
			node->inputpacketnr=argp->packageNR;
			if ((node->pid = fork()) == 0){
				run(node);
			}		
		
		
		}
		result->lastCorrectPackageNR=node->inputpacketnr;
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