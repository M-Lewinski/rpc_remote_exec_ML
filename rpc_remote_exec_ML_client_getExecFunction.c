#include "rpc_remote_exec_ML.h"
#include "rpc_remote_exec_ML_def.h"
#include <unistd.h>

int sentOUTPUT_START(CLIENT *clnt,u_long session_ID,int *packetNR){
	getExecStructResponse  *result_3;
	getExecStructRequest  getexecfunction_1_arg;
    int sleepTime=1;


    getexecfunction_1_arg.ID=session_ID;
    getexecfunction_1_arg.packageNR=(*packetNR);
    getexecfunction_1_arg.packageNRFromType=1;
    getexecfunction_1_arg.packageType=OUTPUT_START;


    while(TRUE){
    (*packetNR)++;
    getexecfunction_1_arg.packageNR=(*packetNR);
    do{
    result_3 = getexecfunction_1(&getexecfunction_1_arg, clnt);
	if (result_3 == (getExecStructResponse *) NULL) {
		clnt_perror (clnt, "call failed");
    }
    }while(result_3->packageNR<getexecfunction_1_arg.packageNR);

    if(result_3->end)
        return  result_3->dataSize;;
    sleep(sleepTime);
    sleepTime+=1;
    }
    return result_3->dataSize;

}


void printResult(CLIENT *clnt,u_long session_ID,int *packetNR,int packageType,int printType){
	getExecStructResponse  *result_3;
	getExecStructRequest  getexecfunction_1_arg;


    getexecfunction_1_arg.ID=session_ID;
    getexecfunction_1_arg.packageNRFromType=-1;
    getexecfunction_1_arg.packageType=packageType;


    do{
        (*packetNR)++;
        getexecfunction_1_arg.packageNR=(*packetNR);
        getexecfunction_1_arg.packageNRFromType++;

        do{
            result_3 = getexecfunction_1(&getexecfunction_1_arg, clnt);
            if (result_3 == (getExecStructResponse *) NULL) {
                clnt_perror (clnt, "call failed");
            }
        }while(result_3->packageNR<getexecfunction_1_arg.packageNR);
        write(printType,result_3->data,result_3->dataSize);

    }while(!(result_3->end));
}


void sentOUTPUT_OUTPUT(CLIENT *clnt,u_long session_ID,int *packetNR){
    printResult(clnt,session_ID,packetNR,OUTPUT_OUTPUT,1);
}

void sentOUTPUT_ERROROUTPUT(CLIENT *clnt,u_long session_ID,int *packetNR){
    printResult(clnt,session_ID,packetNR,OUTPUT_ERROROUTPUT,2);
}


void sentOUTPUT_END(CLIENT *clnt,u_long session_ID,int *packetNR){
    getExecStructResponse  *result_3;
	getExecStructRequest  getexecfunction_1_arg;


    getexecfunction_1_arg.ID=session_ID;
    getexecfunction_1_arg.packageNRFromType=0;
    getexecfunction_1_arg.packageType=OUTPUT_END;


        (*packetNR)++;
        getexecfunction_1_arg.packageNR=(*packetNR);

        do{
            result_3 = getexecfunction_1(&getexecfunction_1_arg, clnt);
            if (result_3 == (getExecStructResponse *) NULL) {
                clnt_perror (clnt, "call failed");
            }
        }while(result_3->packageNR<getexecfunction_1_arg.packageNR);


}

int getresultFromRemoteFuntion(CLIENT *clnt,u_long session_ID,int *packetNR){

    int returnCode;

    returnCode=sentOUTPUT_START(clnt,session_ID,packetNR);
    sentOUTPUT_OUTPUT(clnt,session_ID,packetNR);
    sentOUTPUT_ERROROUTPUT(clnt,session_ID,packetNR);
    sentOUTPUT_END(clnt,session_ID,packetNR);
    return returnCode;
}