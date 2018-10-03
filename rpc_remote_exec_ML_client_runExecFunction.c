#include "rpc_remote_exec_ML.h"
#include "rpc_remote_exec_ML_def.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>



void initSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize,int *packetNR){

	runExecStructResponse  *result_2;
	runExecStructRequest  runexecfunction_1_arg;

	//	printf("test2 - %s\n",clnt);

	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_START;
	runexecfunction_1_arg.packageNR=0;
	runexecfunction_1_arg.dataSize=bufSize;

	//runexecfunction_1_arg.data=NULL; -> tak nie dziala
	runexecfunction_1_arg.data=(char*)malloc(sizeof(char));
	runexecfunction_1_arg.data[0]=0;


	result_2 = runexecfunction_1(&runexecfunction_1_arg, clnt);
	if (result_2 == (runExecStructResponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	free(runexecfunction_1_arg.data);
	*packetNR=result_2->lastCorrectPackageNR;
}
void commandSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize,int *curremtPackageNR){
	int result;
	runExecStructResponse  *result_2=(runExecStructResponse*)malloc(sizeof(runExecStructResponse));
	runExecStructRequest  runexecfunction_1_arg;
	int shortenBufSize=bufSize-1;
	int packetAmount = ceil(strlen(functionToRun)/(float)shortenBufSize);
	char buf[bufSize];


	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_FUNCTION;
	runexecfunction_1_arg.dataSize=bufSize;
	
	runexecfunction_1_arg.data=(char*)malloc(sizeof(char)* bufSize);
	result_2->lastCorrectPackageNR=*curremtPackageNR;

	while((result_2->lastCorrectPackageNR)<(packetAmount)){
		runexecfunction_1_arg.packageNR=result_2->lastCorrectPackageNR+1;

		sprintf(runexecfunction_1_arg.data,"%.*s", shortenBufSize, functionToRun + (shortenBufSize*(runexecfunction_1_arg.packageNR-1)));
		if(shortenBufSize*(runexecfunction_1_arg.packageNR)>strlen(functionToRun)){
			runexecfunction_1_arg.data[strlen(functionToRun)-(shortenBufSize*(runexecfunction_1_arg.packageNR-1))]=0;
		}else
		runexecfunction_1_arg.data[shortenBufSize]=0;



		result_2 = runexecfunction_1(&runexecfunction_1_arg, clnt);
		if (result_2 == (runExecStructResponse *) NULL) {
			clnt_perror (clnt, "call failed");
		}
	};
	
	*curremtPackageNR=result_2->lastCorrectPackageNR;
	free(runexecfunction_1_arg.data);
}

void inputSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize,int *curremtPackageNR){
	runExecStructResponse  *result_2=(runExecStructResponse*)malloc(sizeof(runExecStructResponse));
	runExecStructRequest  runexecfunction_1_arg;
	char buf[bufSize];
	int readedchars;


	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_INPUT;
	runexecfunction_1_arg.dataSize=bufSize;
	
	runexecfunction_1_arg.data=(char*)malloc(sizeof(char)* bufSize);

	result_2->lastCorrectPackageNR=*curremtPackageNR;

	while ((readedchars=read(stdin->_fileno,runexecfunction_1_arg.data,bufSize-1))>0){
		runexecfunction_1_arg.packageNR=result_2->lastCorrectPackageNR+1;
		runexecfunction_1_arg.data[readedchars]=0;

		do{
		result_2 = runexecfunction_1(&runexecfunction_1_arg, clnt);
		if (result_2 == (runExecStructResponse *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		if(result_2->lastCorrectPackageNR<runexecfunction_1_arg.packageNR-1 || result_2->lastCorrectPackageNR>runexecfunction_1_arg.packageNR){
			perror("zly numer paczki");
			exit(EXIT_FAILURE);
		}
		}while(result_2->lastCorrectPackageNR<runexecfunction_1_arg.packageNR);
		//readedchars=0;
	}
	*curremtPackageNR=result_2->lastCorrectPackageNR;
	free(runexecfunction_1_arg.data);
}

void runSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize,int *curremtPackageNR){

	runExecStructResponse  *result_2;
	runExecStructRequest  runexecfunction_1_arg;

	//	printf("test2 - %s\n",clnt);

	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_END;
	runexecfunction_1_arg.packageNR=(*curremtPackageNR)+1;
	runexecfunction_1_arg.dataSize=0;

	//runexecfunction_1_arg.data=NULL; -> tak nie dziala
	runexecfunction_1_arg.data=(char*)malloc(sizeof(char));
	runexecfunction_1_arg.data[0]=0;


	result_2 = runexecfunction_1(&runexecfunction_1_arg, clnt);
	if (result_2 == (runExecStructResponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	if(result_2->lastCorrectPackageNR<runexecfunction_1_arg.packageNR-1 || result_2->lastCorrectPackageNR>runexecfunction_1_arg.packageNR){
			perror("zly numer paczki");
			exit(EXIT_FAILURE);
		}

	free(runexecfunction_1_arg.data);
	
	*curremtPackageNR=result_2->lastCorrectPackageNR;
}

void sendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int* packetNR,int bufSize){

	initSendFunctionToRun(clnt,session_ID,functionToRun,bufSize,packetNR);
	commandSendFunctionToRun(clnt,session_ID,functionToRun,bufSize,packetNR);
	inputSendFunctionToRun(clnt,session_ID,functionToRun,bufSize,packetNR);
	runSendFunctionToRun(clnt,session_ID,functionToRun,bufSize,packetNR);


}