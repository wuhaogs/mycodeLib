#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<sys/wait.h>
#include "common.h"

//����:ִ��ϵͳ����route -n �������Խ�������ļ�
int ExcSysCmdtest()
{
    FILE    *stream=NULL;
    FILE    *wstream=NULL;
    char   buf[1024];

    //��ʼ��buf,�������д�����뵽�ļ���
    memset( buf, '\0', sizeof(buf) );

    //��route -n��������� ͨ���ܵ���ȡ���ļ��� file stream
    stream = popen("route -n", "r" );

    //�½�һ����д�ļ�
    wstream = fopen( "test_popen.txt", "w+");

    //���ո�file* steam����������ȡ��buf��
    fread( buf, sizeof(char), sizeof(buf), stream);

    //��buf�е�����д��file *wstream��Ӧ�����У�Ҳ��д���ļ���
    fwrite( buf, 1, sizeof(buf), wstream );

    pclose( stream );
    fclose( wstream );
    return 0;
}
/************************************************************************
  Function��      ExcSysCmdReturnResultBYpopen
  Description��   ִ��ϵͳ��������Խ�������ļ�
  Input��         ��:/usr/local/sbin/,zebra.sh,start
  Output��        ��
  Return��        ETOK
  Others��        ��
************************************************************************/
int ExcSysCmdReturnResultBYpopen(char *path, char *file, char *arg)
{
    FILE    *stream=NULL;
    FILE    *wstream=NULL;
    char   buf[1024];
    char cbuffer[50];
    memset(cbuffer, 0, sizeof(cbuffer));
    sprintf(cbuffer, "%s%s %s", path,file, arg);

    //��ʼ��buf,�������д�����뵽�ļ���
    memset( buf, '\0', sizeof(buf) );

    //��ls -l��������� ͨ���ܵ���ȡ���ļ��� file stream
    stream = popen(cbuffer, "r" );

    //�½�һ����д�ļ�
    wstream = fopen( "test_popen.txt", "w+");

    //���ո�file* steam����������ȡ��buf��
    fread( buf, sizeof(char), sizeof(buf), stream);

    //��buf�е�����д��file *wstream��Ӧ�����У�Ҳ��д���ļ���
    fwrite( buf, 1, sizeof(buf), wstream );

    pclose( stream );
    fclose( wstream );
    return 0;
}

/************************************************************************
  Function��      ExcAndShowSysCmd
  Description��   ִ�в���ʾϵͳ���vty
  Input��         ��:/usr/local/sbin/,sysinfo.sh,route
  Output��        ��
  Return��        ETOK
  Others��        ��
************************************************************************/
int ExcAndShowSysCmd(char *path, char *file, char *arg,CLI *pCli)
{
    FILE    *stream=NULL;
    char   buf[1024];
    char cbuffer[50];
    memset(cbuffer, 0, sizeof(cbuffer));
    sprintf(cbuffer, "%s%s %s", path,file, arg);

    //��ʼ��buf,�������д�����뵽�ļ���
    memset( buf, '\0', sizeof(buf) );

    //��ls -l��������� ͨ���ܵ���ȡ���ļ��� file stream
    stream = popen(cbuffer, "r" );


    //���ո�file* steam����������ȡ��buf��
    fread( buf, sizeof(char), sizeof(buf), stream);

    //mmlPrintf(pCli,buf);

    pclose( stream );
    return 0;
}

/************************************************************************
  Function��      ExcSysCmdReturnResultBYpipe
  Description��   ��ǿ��system�������ܹ�����system���õ����
  Input��         @param[in] cmdstring �����ⲿ�����ű������
  				  @param[in] len ������buf�ĳ���
  Output��        @param[out] buf �����ⲿ����Ľ���Ļ�����
  Return��        �ɹ���ʧ��
  Others��        ��
************************************************************************/
int ExcSysCmdReturnResultBYpipe(char* cmdstring, char* buf, int len)
{
	int   fd[2];
	pid_t pid;
	int   n, count;
	memset(buf, 0, len);

	// fd[0]:���ܵ���fd[1]:д�ܵ�������
	if (pipe(fd) < 0)
		return -1;

	if ((pid = fork()) < 0)
		return -1;
	else if (pid > 0)     /* parent process */
	{
	//�������������ʹر�д�ܵ�
	close(fd[1]);     /* close write end */
	count = 0;

	//�ӹܵ�����˶�ȡ���ݵ�buf
	while ((n = read(fd[0], buf + count, len)) > 0 && count > len)
	count += n;
	close(fd[0]);

	//��ʱֹͣĿǰ���̵�ִ�У�ֱ���źŵ������ӽ��̽�����
	//������ʱ���ӽ����Ѿ����������������ӽ��̽���״ֵ̬��
	if (waitpid(pid, NULL, 0) > 0)
		return -1;
	}
	else    /* child process */
	{
	//�ӽ�����д���ʹرն��ܵ�
	close(fd[0]);     /* close read end */
	//��׼����Ƿ��Ѿ��ض��򵽹ܵ�����˿�
	if (fd[1] != STDOUT_FILENO)
	{
		//��׼����ض��򵽹ܵ�����˿�
		if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
		{
			return -1;
		}
		//�رղ�����ر�д�ܵ��ļ�����������Ϊ�ض����Ե�ʣ�//STDOUT_FILENO��1��Ҳָ������
		close(fd[1]);
	}
	//ִ��/binĿ¼��sh�����һ������sh���ڶ�������-c����������������
	//���ַ�������/bin/sh �Cc cmdstring
	//ִ�������׼����ض��򵽹ܵ������
	if (execl("/bin/sh", "sh", "-c", cmdstring, (char*)0) == -1)
		return -1;
	}
	return 0;
}

/************************************************************************
  Function��      ExcSysCmdReturnResultBYsystem
  Description��   system�������ܹ�����system���õ����
  Input��         @param[in] cmdstring �����ⲿ�����ű������
  Output��        @param[out] tmpfile ����ļ�
  Return��        �ɹ���ʧ��
  Others��        ��
************************************************************************/
#define CMD_STR_LEN 1024
int ExcSysCmdReturnResultBYsystem(char* cmdstring, char* tmpfile)
{

	char cmd_string[CMD_STR_LEN];

	//����:ϵͳ�Լ�����һ���ļ����ļ���ϵͳ�Լ����������ҷ�������ļ���·����ָ�롣
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

