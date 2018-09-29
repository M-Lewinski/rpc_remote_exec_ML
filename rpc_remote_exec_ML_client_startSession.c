#include "rpc_remote_exec_ML.h"

u_long startsession(CLIENT *clnt){
	u_long  *result_1;
	char *startsession_1_arg;

	result_1 = startsession_1((void*)&startsession_1_arg, clnt);
	if (result_1 == (u_long *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	printf("otrzymany id - %lu\n",*result_1);
	return *result_1;
}