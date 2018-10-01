#include "rpc_remote_exec_ML.h"

void sendFunctionToRun(CLIENT *clnt,u_long session_ID,char* functionToRun,int* packetNR,int bufSize);