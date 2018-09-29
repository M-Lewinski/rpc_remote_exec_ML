/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "rpc_remote_exec_ML.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

u_long *
startsession_1(void *argp, CLIENT *clnt)
{
	static u_long clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, startSession,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_u_long, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

runExecStructResponse *
runexecfunction_1(runExecStructRequest *argp, CLIENT *clnt)
{
	static runExecStructResponse clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, runExecFunction,
		(xdrproc_t) xdr_runExecStructRequest, (caddr_t) argp,
		(xdrproc_t) xdr_runExecStructResponse, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

getExecStructResponse *
getexecfunction_1(getExecStructRequest *argp, CLIENT *clnt)
{
	static getExecStructResponse clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, getExecFunction,
		(xdrproc_t) xdr_getExecStructRequest, (caddr_t) argp,
		(xdrproc_t) xdr_getExecStructResponse, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
