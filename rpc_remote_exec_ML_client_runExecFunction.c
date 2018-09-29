#include "rpc_remote_exec_ML.h"
#include <string.h>
#include <stdio.h>
#include <math.h>


int initSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize){

	runExecStructResponse  *result_2;
	runExecStructRequest  runexecfunction_1_arg;

//	printf("test2 - %s\n",clnt);

	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_START;
	runexecfunction_1_arg.packageNR=0;
	runexecfunction_1_arg.dataSize=0;
	runexecfunction_1_arg.packetAmount=0; // mozliwe ze niepotrzebne

	//runexecfunction_1_arg.data=NULL; -> tak nie dziala
	runexecfunction_1_arg.data=(char*)malloc(sizeof(char));
	runexecfunction_1_arg.data[0]=0;


	result_2 = runexecfunction_1(&runexecfunction_1_arg, clnt);
	if (result_2 == (runExecStructResponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	free(runexecfunction_1_arg.data);
	return result_2->lastCorrectPackageNR+1;
}
int commandSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize){
	int result;
	runExecStructResponse  *result_2=(runExecStructResponse*)malloc(sizeof(runExecStructResponse));
	runExecStructRequest  runexecfunction_1_arg;
	int shortenBufSize=bufSize-1;
	int packetAmount = ceil(strlen(functionToRun)/(float)shortenBufSize);
	char buf[bufSize];


	printf("strlen -%d,shortenBufSize -%d,packetAmount - %d\n",strlen(functionToRun),shortenBufSize,packetAmount);

	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_FUNCTION;

	result_2->lastCorrectPackageNR=0;

	do{
		runexecfunction_1_arg.packageNR=result_2->lastCorrectPackageNR+1;
		runexecfunction_1_arg.dataSize=bufSize;
		
		runexecfunction_1_arg.data=(char*)malloc(sizeof(char)* bufSize);
		sprintf(runexecfunction_1_arg.data,"%.*s", shortenBufSize, functionToRun + (shortenBufSize*(runexecfunction_1_arg.packageNR-1)));
		if(shortenBufSize*(runexecfunction_1_arg.packageNR)>strlen(functionToRun)){
			runexecfunction_1_arg.data[strlen(functionToRun)-(shortenBufSize*(runexecfunction_1_arg.packageNR-1))]=0;
		}else
		runexecfunction_1_arg.data[shortenBufSize]=0;


		printf("--->sending %s\n",runexecfunction_1_arg.data);

		result_2 = runexecfunction_1(&runexecfunction_1_arg, clnt);
		if (result_2 == (runExecStructResponse *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		printf("otrzymałem %d \n",result_2->lastCorrectPackageNR);
	}while(result_2->lastCorrectPackageNR<=(packetAmount-1));
	
	result=result_2->lastCorrectPackageNR+1;
	free(runexecfunction_1_arg.data);
	return result;
}

void sendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize){
	//printf("funkcja do uruchomienia %s - bufSize %d",functionToRun,bufSize);

	/*runExecStructResponse  *result_2;
	runExecStructRequest  runexecfunction_1_arg;


	result_2 = runexecfunction_1(&runexecfunction_1_arg, clnt);
	if (result_2 == (runExecStructResponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}*/

	initSendFunctionToRun(clnt,session_ID,functionToRun,bufSize);
	commandSendFunctionToRun(clnt,session_ID,functionToRun,bufSize);
//	printf("test2 - %s\n",clnt);
}