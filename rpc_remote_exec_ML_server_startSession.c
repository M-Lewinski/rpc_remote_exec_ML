#include "rpc_remote_exec_ML.h"
#include "rpc_remote_exec_ML_def.h"

u_long maxCurrentID=0;


u_long *
startsession_1_svc(void *argp, struct svc_req *rqstp)
{
	static u_long  result;

	maxCurrentID++;
	result=maxCurrentID;

	return &result;
}