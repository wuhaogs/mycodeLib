//#include "common.h"
//#include "mycode.h"
//#include "mytest.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

/***************version info*****************************/
#define MYCODE_VER_MAJOR   "1."
#define MYCODE_VER_UPPER   "0."
#define MYCODE_VER_MIDDLE  "0."
#define MYCODE_VER_MINOR   "1_t"
void testfile();
int ExcSysCmdtest();
char *GetECNPrimCfgEthernet1()
{
	char *ip="10.10.10.10";
	return "0.0.0.0";
}
char *GetECNPrimCfgEthernet()
{
    static char ipstr[20] = {0};

    memcpy(ipstr,"11.11.11.11",sizeof("11.11.11.11"));

    return ipstr;
}

extern char *GetECNPrimCfgEthernet();


int main(int argc, char *argv[])
{
    printf("hello world!\n");


     //initMycode_T();

     //initError_T();

     //initFuncLib_T();

     //initEasttest_T();

     //initSocket_T();

     initMytest_T();

    return 0;


}
