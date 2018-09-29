#include "rpc_remote_exec_ML.h"
#include "rpc_remote_exec_ML_LL.h"

runExecStructResponse *
runexecfunction_1_svc(runExecStructRequest *argp, struct svc_req *rqstp)
{
	static runExecStructResponse  result;
	list* node;

	switch(argp->packageType){
		case INPUT_START:
		printf("INPUT_START\n");
		addToList(argp->ID);
		result.lastCorrectPackageNR=0;
		//usuwanie ewentualnie istenijacego pliku;
		break;
		case INPUT_FUNCTION:
		printf("INPUT_FUNCTION\n");
		node = searchInList(argp->ID);
		if(node->inputpacketnr==argp->packageNR-1){
			node->inputpacketnr=argp->packageNR;
			//zapisywanie do pliku?
			printf("tresc funkcji - %s\n",argp->data);
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