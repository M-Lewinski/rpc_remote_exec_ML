#include "rpc_remote_exec_ML.h"
#include "rpc_remote_exec_ML_LL.h"

void caseINPUT_START(runExecStructRequest *argp,runExecStructResponse  *result){
		printf("INPUT_START\n");
		addToList(argp->ID);
		result->lastCorrectPackageNR=0;
		//usuwanie ewentualnie istenijacego pliku;

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
		/*list* node;
		FILE *pFile;
		char filename[180];
		char IDstring[80];
		printf("INPUT_FUNCTION\n");
		node = searchInList(argp->ID);
		//printListNode(node);

		sprintf(IDstring,"%lu",argp->ID);
		strcpy(filename,"data/");
		strcat(filename,IDstring);
		strcat(filename,"_function.txt");

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
		result->lastCorrectPackageNR=node->inputpacketnr;*/
		saveToFileInput(argp,result,"_function.txt");
}
void caseINPUT_INPUT(runExecStructRequest *argp,runExecStructResponse  *result){
		list* node;
		printf("INPUT_INPUT\n");
		node = searchInList(argp->ID);
		if(node->inputpacketnr==argp->packageNR-1){
			node->inputpacketnr=argp->packageNR;
			//zapisywanie do pliku?
		}
		result->lastCorrectPackageNR=node->inputpacketnr;
}
void caseINPUT_END(runExecStructRequest *argp,runExecStructResponse  *result){
		list* node;

		printf("INPUT_END\n");
		node = searchInList(argp->ID);
		if(node->inputpacketnr==argp->packageNR-1){
			node->inputpacketnr=argp->packageNR;
			//zapisywanie do pliku?
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