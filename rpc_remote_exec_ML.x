struct runExecStructRequest{
int dataSize;
unsigned long ID;
int packageNR;
int packageType;
string data<>;
};

struct runExecStructResponse{
int lastCorrectPackageNR;
};


struct getExecStructRequest{
unsigned long ID;
int packageNR;
int packageNRFromType;
int packageType;
};

struct getExecStructResponse{
int dataSize;
int packageNR;
int packageType;
int end;
string data<>;
};

program rpcRemoteExecML{ 
version rpcRemoteExecMLVERS { 
unsigned long startSession(void) = 1; 
runExecStructResponse runExecFunction(runExecStructRequest) = 2;
getExecStructResponse getExecFunction(getExecStructRequest) = 3;
} = 1;
} = 0x22334455; 