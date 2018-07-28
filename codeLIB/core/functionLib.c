#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<sys/wait.h>
#include "common.h"

//举例:执行系统命令route -n 并将回显结果存入文件
int ExcSysCmdtest()
{
    FILE    *stream=NULL;
    FILE    *wstream=NULL;
    char   buf[1024];

    //初始化buf,以免后面写入乱码到文件中
    memset( buf, '\0', sizeof(buf) );

    //将route -n的命令输出 通过管道读取到文件流 file stream
    stream = popen("route -n", "r" );

    //新建一个可写文件
    wstream = fopen( "test_popen.txt", "w+");

    //将刚刚file* steam的数据流读取到buf中
    fread( buf, sizeof(char), sizeof(buf), stream);

    //将buf中的数据写到file *wstream对应的流中，也是写到文件中
    fwrite( buf, 1, sizeof(buf), wstream );

    pclose( stream );
    fclose( wstream );
    return 0;
}
/************************************************************************
  Function：      ExcSysCmdReturnResultBYpopen
  Description：   执行系统命令并将回显结果存入文件
  Input：         如:/usr/local/sbin/,zebra.sh,start
  Output：        无
  Return：        ETOK
  Others：        无
************************************************************************/
int ExcSysCmdReturnResultBYpopen(char *path, char *file, char *arg)
{
    FILE    *stream=NULL;
    FILE    *wstream=NULL;
    char   buf[1024];
    char cbuffer[50];
    memset(cbuffer, 0, sizeof(cbuffer));
    sprintf(cbuffer, "%s%s %s", path,file, arg);

    //初始化buf,以免后面写入乱码到文件中
    memset( buf, '\0', sizeof(buf) );

    //将ls -l的命令输出 通过管道读取到文件流 file stream
    stream = popen(cbuffer, "r" );

    //新建一个可写文件
    wstream = fopen( "test_popen.txt", "w+");

    //将刚刚file* steam的数据流读取到buf中
    fread( buf, sizeof(char), sizeof(buf), stream);

    //将buf中的数据写到file *wstream对应的流中，也是写到文件中
    fwrite( buf, 1, sizeof(buf), wstream );

    pclose( stream );
    fclose( wstream );
    return 0;
}

/************************************************************************
  Function：      ExcAndShowSysCmd
  Description：   执行并显示系统命令到vty
  Input：         如:/usr/local/sbin/,sysinfo.sh,route
  Output：        无
  Return：        ETOK
  Others：        无
************************************************************************/
int ExcAndShowSysCmd(char *path, char *file, char *arg,CLI *pCli)
{
    FILE    *stream=NULL;
    char   buf[1024];
    char cbuffer[50];
    memset(cbuffer, 0, sizeof(cbuffer));
    sprintf(cbuffer, "%s%s %s", path,file, arg);

    //初始化buf,以免后面写入乱码到文件中
    memset( buf, '\0', sizeof(buf) );

    //将ls -l的命令输出 通过管道读取到文件流 file stream
    stream = popen(cbuffer, "r" );


    //将刚刚file* steam的数据流读取到buf中
    fread( buf, sizeof(char), sizeof(buf), stream);

    //mmlPrintf(pCli,buf);

    pclose( stream );
    return 0;
}

/************************************************************************
  Function：      ExcSysCmdReturnResultBYpipe
  Description：   增强的system函数，能够返回system调用的输出
  Input：         @param[in] cmdstring 调用外部程序或脚本的命令串
  				  @param[in] len 缓冲区buf的长度
  Output：        @param[out] buf 返回外部命令的结果的缓冲区
  Return：        成功或失败
  Others：        无
************************************************************************/
int ExcSysCmdReturnResultBYpipe(char* cmdstring, char* buf, int len)
{
	int   fd[2];
	pid_t pid;
	int   n, count;
	memset(buf, 0, len);

	// fd[0]:读管道，fd[1]:写管道描述符
	if (pipe(fd) < 0)
		return -1;

	if ((pid = fork()) < 0)
		return -1;
	else if (pid > 0)     /* parent process */
	{
	//父进程来读，故关闭写管道
	close(fd[1]);     /* close write end */
	count = 0;

	//从管道输入端读取数据岛buf
	while ((n = read(fd[0], buf + count, len)) > 0 && count > len)
	count += n;
	close(fd[0]);

	//暂时停止目前进程的执行，直到信号到来或子进程结束。
	//若调用时，子进程已经结束，立即返回子进程结束状态值。
	if (waitpid(pid, NULL, 0) > 0)
		return -1;
	}
	else    /* child process */
	{
	//子进程来写，故关闭读管道
	close(fd[0]);     /* close read end */
	//标准输出是否已经重定向到管道输出端口
	if (fd[1] != STDOUT_FILENO)
	{
		//标准输出重定向到管道输出端口
		if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
		{
			return -1;
		}
		//关闭并不会关闭写管道文件描述符，因为重定向的缘故，//STDOUT_FILENO（1）也指向它。
		close(fd[1]);
	}
	//执行/bin目录下sh命令，第一个参数sh，第二个参数-c，第三个参数是入
	//参字符串；如/bin/sh –c cmdstring
	//执行命令。标准输出重定向到管道输出端
	if (execl("/bin/sh", "sh", "-c", cmdstring, (char*)0) == -1)
		return -1;
	}
	return 0;
}

/************************************************************************
  Function：      ExcSysCmdReturnResultBYsystem
  Description：   system函数，能够返回system调用的输出
  Input：         @param[in] cmdstring 调用外部程序或脚本的命令串
  Output：        @param[out] tmpfile 输出文件
  Return：        成功或失败
  Others：        无
************************************************************************/
#define CMD_STR_LEN 1024
int ExcSysCmdReturnResultBYsystem(char* cmdstring, char* tmpfile)
{

	char cmd_string[CMD_STR_LEN];

	//功能:系统自己创建一个文件，文件名系统自己给定。并且返回这个文件的路径名指针。
	tmpnam(tmpfile);

	sprintf(cmd_string, "%s > %s", cmdstring, tmpfile);

	return system(cmd_string);
}



void testPipe()
{
    char *strCmd="route -n";
    char buf[2048] = {0};

    if(0 == ExcSysCmdReturnResultBYpipe(strCmd, buf, 1024))
    {
        printf("testPipe suc!\n");
    }
    printf("%s\n",buf);

}

#ifdef _DEBUG
void initFuncLib_T()
{
    ExcSysCmdtest();
    testPipe();
}
#endif

