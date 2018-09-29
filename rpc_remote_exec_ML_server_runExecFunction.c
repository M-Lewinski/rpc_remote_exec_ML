#include "rpc_remote_exec_ML.h"
#include "rpc_remote_exec_ML_LL.h"

void caseINPUT_START(runExecStructRequest *argp,runExecStructResponse  *result){
		printf("INPUT_START\n");
		addToList(argp->ID);
		result->lastCorrectPackageNR=0;
		//usuwanie ewentualnie istenijacego pliku;

		//printList();
}

runExecStructResponse *
runexecfunction_1_svc(runExecStructRequest *argp, struct svc_req *rqstp)
{
	static runExecStructResponse  result;
	list* node;

	switch(argp->packageType){
		case INPUT_START:
		/*printf("INPUT_START\n");
		addToList(argp->ID);
		result.lastCorrectPackageNR=0;
		//usuwanie ewentualnie istenijacego pliku;

		//printList();*/
		caseINPUT_START(argp,&result);
		break;
		case INPUT_FUNCTION:
		printf("INPUT_FUNCTION\n");
		node = searchInList(argp->ID);
		//printListNode(node);
		if(node->inputpacketnr==argp->packageNR-1){
			node->inputpacketnr=argp->packageNR;
			//zapisywanie do pliku?
			printf("tresc funkcji - %s\n",argp->data);
		}else{
			printf("zly numer\n");
		}
		result.lastCorrectPackageNR=node->inputpacketnr;
		break;
		case INPUT_INPUT:
		printf("INPUT_INPUT\n");
		node = searchInList(argp->ID);
		if(node->inputpacketnr==argp->packageNR-1){
			node->inputpacketnr=argp->packageNR;
			//zapisywanie do pliku?
		}
		result.lastCorrectPackageNR=node->inputpacketnr;
		break;
		case INPUT_END:
		printf("INPUT_END\n");
		node = searchInList(argp->ID);
		if(node->inputpacketnr==argp->packageNR-1){
			node->inputpacketnr=argp->packageNR;
			//zapisywanie do pliku?
		}
		result.lastCorrectPackageNR=node->inputpacketnr;
		break;
	}

	/*
	 * insert server code here
	 */

	return &result;
}