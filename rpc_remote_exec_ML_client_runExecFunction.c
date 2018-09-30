#include "rpc_remote_exec_ML.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>



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
	return result_2->lastCorrectPackageNR;
}
int commandSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize,int curremtPackageNR){
	int result;
	runExecStructResponse  *result_2=(runExecStructResponse*)malloc(sizeof(runExecStructResponse));
	runExecStructRequest  runexecfunction_1_arg;
	int shortenBufSize=bufSize-1;
	int packetAmount = ceil(strlen(functionToRun)/(float)shortenBufSize);
	char buf[bufSize];


	printf("strlen -%d,shortenBufSize -%d,packetAmount - %d\n",strlen(functionToRun),shortenBufSize,packetAmount);

	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_FUNCTION;
	runexecfunction_1_arg.dataSize=bufSize;
	
	runexecfunction_1_arg.data=(char*)malloc(sizeof(char)* bufSize);
	result_2->lastCorrectPackageNR=curremtPackageNR;

	while((result_2->lastCorrectPackageNR)<(packetAmount)){
		runexecfunction_1_arg.packageNR=result_2->lastCorrectPackageNR+1;

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
	};
	
	result=result_2->lastCorrectPackageNR;
	free(runexecfunction_1_arg.data);
	return result;
}

int inputSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize,int curremtPackageNR){
	int result;
	runExecStructResponse  *result_2=(runExecStructResponse*)malloc(sizeof(runExecStructResponse));
	runExecStructRequest  runexecfunction_1_arg;
	char buf[bufSize];
	int readedchars;


	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_INPUT;
	runexecfunction_1_arg.dataSize=bufSize;
	
	runexecfunction_1_arg.data=(char*)malloc(sizeof(char)* bufSize);

	result_2->lastCorrectPackageNR=curremtPackageNR;

	while ((readedchars=read(stdin->_fileno,runexecfunction_1_arg.data,bufSize-1))>0){
		printf("readed %d\n",readedchars);
		runexecfunction_1_arg.packageNR=result_2->lastCorrectPackageNR+1;
		runexecfunction_1_arg.data[readedchars]=0;
		printf("--->sending %s\n",runexecfunction_1_arg.data);

		do{
		result_2 = runexecfunction_1(&runexecfunction_1_arg, clnt);
		if (result_2 == (runExecStructResponse *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		printf("otrzymałem %d nrpaczki%d\n",result_2->lastCorrectPackageNR,runexecfunction_1_arg.packageNR);
		if(result_2->lastCorrectPackageNR<runexecfunction_1_arg.packageNR-1 || result_2->lastCorrectPackageNR>runexecfunction_1_arg.packageNR){
			perror("zly numer paczki");
			exit(EXIT_FAILURE);
		}
		}while(result_2->lastCorrectPackageNR<runexecfunction_1_arg.packageNR);
		//readedchars=0;
	}
	result=result_2->lastCorrectPackageNR;
	free(runexecfunction_1_arg.data);
	return result;
}

int runSendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize,int curremtPackageNR){

	runExecStructResponse  *result_2;
	runExecStructRequest  runexecfunction_1_arg;

	//	printf("test2 - %s\n",clnt);

	runexecfunction_1_arg.ID=session_ID;
	runexecfunction_1_arg.packageType=INPUT_END;
	runexecfunction_1_arg.packageNR=curremtPackageNR+1;
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
	return result_2->lastCorrectPackageNR;
}

void sendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int bufSize){
	int packageNR=0;

	packageNR=initSendFunctionToRun(clnt,session_ID,functionToRun,bufSize);
	
	packageNR=commandSendFunctionToRun(clnt,session_ID,functionToRun,bufSize,packageNR);
	packageNR=commandSendFunctionToRun(clnt,session_ID,functionToRun,bufSize,packageNR);
	packageNR=inputSendFunctionToRun(clnt,session_ID,functionToRun,bufSize,packageNR);
	packageNR=runSendFunctionToRun(clnt,session_ID,functionToRun,bufSize,packageNR);

	printf("==============================%d\n",packageNR);
//	printf("test2 - %s\n",clnt);
}