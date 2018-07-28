//ѭ����a����ÿ�η���200���ֽڳ��ȣ�����ǹ̶��ģ���buffer,
//a��������Ҫ��ѭ����������buffer�����240�ֽڣ�Ҳ�ǹ̶��ģ�����buffer���д���
//�ڴ����ʱ��ÿ�δ���buffer��ȡ�����ֽڴ�ӡ
/*
�κ��շ������ٶȲ�һ�µ�ͨѶ������Ҫ������֮��ʹ��һ���㹻���FIFO��������
���κ�FIFO��������ʹ�ã�����Ҫ��ϸ���ǽ��ն˽���ʱ��ʱ�����ݺͷ��Ͷ˷���ʱFIFO��������������������¸��������
��Щ�������ξ���������������֡�
��ξ�����뻹�������±��뿼�ǵ����أ�
����Windows��Linuxƽ̨
�����߳���
�����߳���־
����־�ļ�ռ�õĴ��̿ռ�ɿ�
����־�е�ʱ���������
����������ݶ�Ӧ��ÿ���ֽڵ����Ǽ�
������˳����̳߳���
*/
#ifdef _MSC_VER
    #pragma warning(disable:4996)
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
    #include <windows.h>
    #include <process.h>
    #include <io.h>
    #define  MYVOID             void
    #define  vsnprintf          _vsnprintf
#else
    #include <unistd.h>
    #include <sys/time.h>
    #include <pthread.h>
    #define  CRITICAL_SECTION   pthread_mutex_t
    #define  MYVOID             void *
#endif
//Log{
#define MAXLOGSIZE 20000000
#define MAXLINSIZE 16000
#include <time.h>
#include <sys/timeb.h>
#include <stdarg.h>
char logfilename1[]="MyLog1.log";
char logfilename2[]="MyLog2.log";
static char logstr[MAXLINSIZE+1];
char datestr[16];
char timestr[16];
char mss[4];
CRITICAL_SECTION cs_log;
FILE *flog;
#ifdef _MSC_VER
void Lock(CRITICAL_SECTION *l) {
    EnterCriticalSection(l);
}
void Unlock(CRITICAL_SECTION *l) {
    LeaveCriticalSection(l);
}
void sleep_ms(int ms) {
    Sleep(ms);
}
#else
void Lock(CRITICAL_SECTION *l) {
    pthread_mutex_lock(l);
}
void Unlock(CRITICAL_SECTION *l) {
    pthread_mutex_unlock(l);
}
void sleep_ms(int ms) {
    usleep(ms*1000);
}
#endif
void LogV(const char *pszFmt,va_list argp) {
    struct tm *now;
    struct timeb tb;

    if (NULL==pszFmt||0==pszFmt[0]) return;
    vsnprintf(logstr,MAXLINSIZE,pszFmt,argp);
    ftime(&tb);
    now=localtime(&tb.time);
    sprintf(datestr,"%04d-%02d-%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday);
    sprintf(timestr,"%02d:%02d:%02d",now->tm_hour     ,now->tm_min  ,now->tm_sec );
    sprintf(mss,"%03d",tb.millitm);
    printf("%s %s.%s %s",datestr,timestr,mss,logstr);
    flog=fopen(logfilename1,"a");
    if (NULL!=flog) {
        fprintf(flog,"%s %s.%s %s",datestr,timestr,mss,logstr);
        if (ftell(flog)>MAXLOGSIZE) {
            fclose(flog);
            if (rename(logfilename1,logfilename2)) {
                remove(logfilename2);
                rename(logfilename1,logfilename2);
            }
        } else {
            fclose(flog);
        }
    }
}
void Log(const char *pszFmt,...) {
    va_list argp;

    Lock(&cs_log);
    va_start(argp,pszFmt);
    LogV(pszFmt,argp);
    va_end(argp);
    Unlock(&cs_log);
}
//Log}
#define ASIZE    200
#define BSIZE    240
#define CSIZE      2
char Abuf[ASIZE];
char Cbuf[CSIZE];
CRITICAL_SECTION cs_HEX;
CRITICAL_SECTION cs_BBB;
struct FIFO_BUFFER {
    int  head;
    int  tail;
    int  size;
    char data[BSIZE];
} BBB;
int No_Loop=0;
void HexDump(int cn,char *buf,int len) {
    int i,j,k;
    char binstr[80];

    Lock(&cs_HEX);
    for (i=0;i<len;i++) {
        if (0==(i%16)) {
            sprintf(binstr,"%03d %04x -",cn,i);
            sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);
        } else if (15==(i%16)) {
            sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);
            sprintf(binstr,"%s  ",binstr);
            for (j=i-15;j<=i;j++) {
                sprintf(binstr,"%s%c",binstr,('!'<buf[j]&&buf[j]<='~')?buf[j]:'.');
            }
            Log("%s\n",binstr);
        } else {
            sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);
        }
    }
    if (0!=(i%16)) {
        k=16-(i%16);
        for (j=0;j<k;j++) {
            sprintf(binstr,"%s   ",binstr);
        }
        sprintf(binstr,"%s  ",binstr);
        k=16-k;
        for (j=i-k;j<i;j++) {
            sprintf(binstr,"%s%c",binstr,('!'<buf[j]&&buf[j]<='~')?buf[j]:'.');
        }
        Log("%s\n",binstr);
    }
    Unlock(&cs_HEX);
}
int GetFromRBuf(int cn,CRITICAL_SECTION *cs,struct FIFO_BUFFER *fbuf,char *buf,int len) {
    int lent,len1,len2;

    lent=0;
    Lock(cs);
    if (fbuf->size>=len) {
        lent=len;
        if (fbuf->head+lent>BSIZE) {
            len1=BSIZE-fbuf->head;
            memcpy(buf     ,fbuf->data+fbuf->head,len1);
            len2=lent-len1;
            memcpy(buf+len1,fbuf->data           ,len2);
            fbuf->head=len2;
        } else {
            memcpy(buf     ,fbuf->data+fbuf->head,lent);
            fbuf->head+=lent;
        }
        fbuf->size-=lent;
    }
    Unlock(cs);
    return lent;
}
MYVOID thdB(void *pcn) {
    char        *recv_buf;
    int          recv_nbytes;
    int          cn;
    int          wc;
    int          pb;

    cn=(int)pcn;
    Log("%03d thdB              thread begin...\n",cn);
    while (1) {
        sleep_ms(10);
        recv_buf=(char *)Cbuf;
        recv_nbytes=CSIZE;
        wc=0;
        while (1) {
            pb=GetFromRBuf(cn,&cs_BBB,&BBB,recv_buf,recv_nbytes);
            if (pb) {
                Log("%03d recv %d bytes\n",cn,pb);
                HexDump(cn,recv_buf,pb);
                sleep_ms(1);
            } else {
                sleep_ms(1000);
            }
            if (No_Loop) break;//
            wc++;
            if (wc>3600) Log("%03d %d==wc>3600!\n",cn,wc);
        }
        if (No_Loop) break;//
    }
#ifndef _MSC_VER
    pthread_exit(NULL);
#endif
}
int PutToRBuf(int cn,CRITICAL_SECTION *cs,struct FIFO_BUFFER *fbuf,char *buf,int len) {
    int lent,len1,len2;

    Lock(cs);
    lent=len;
    if (fbuf->size+lent>BSIZE) {
        lent=BSIZE-fbuf->size;
    }
    if (fbuf->tail+lent>BSIZE) {
        len1=BSIZE-fbuf->tail;
        memcpy(fbuf->data+fbuf->tail,buf     ,len1);
        len2=lent-len1;
        memcpy(fbuf->data           ,buf+len1,len2);
        fbuf->tail=len2;
    } else {
        memcpy(fbuf->data+fbuf->tail,buf     ,lent);
        fbuf->tail+=lent;
    }
    fbuf->size+=lent;
    Unlock(cs);
    return lent;
}
MYVOID thdA(void *pcn) {
    char        *send_buf;
    int          send_nbytes;
    int          cn;
    int          wc;
    int           a;
    int          pa;

    cn=(int)pcn;
    Log("%03d thdA              thread begin...\n",cn);
    a=0;
    while (1) {
        sleep_ms(100);
        memset(Abuf,a,ASIZE);
        a=(a+1)%256;
        if (16==a) {No_Loop=1;break;}//ȥ���������ó���һֱѭ��ֱ����Ctrl+C��Ctrl+Break��ǰĿ¼�´����ļ�No_Loop
        send_buf=(char *)Abuf;
        send_nbytes=ASIZE;
        Log("%03d sending %d bytes\n",cn,send_nbytes);
        HexDump(cn,send_buf,send_nbytes);
        wc=0;
        while (1) {
            pa=PutToRBuf(cn,&cs_BBB,&BBB,send_buf,send_nbytes);
            Log("%03d sent %d bytes\n",cn,pa);
            HexDump(cn,send_buf,pa);
            send_buf+=pa;
            send_nbytes-=pa;
            if (send_nbytes<=0) break;//
            sleep_ms(1000);
            if (No_Loop) break;//
            wc++;
            if (wc>3600) Log("%03d %d==wc>3600!\n",cn,wc);
        }
        if (No_Loop) break;//
    }
#ifndef _MSC_VER
    pthread_exit(NULL);
#endif
}
int mainSocket()
{
#ifdef _MSC_VER
    InitializeCriticalSection(&cs_log);
    InitializeCriticalSection(&cs_HEX);
    InitializeCriticalSection(&cs_BBB);
#else
    pthread_t threads[2];
    int threadsN;
    int rc;
    pthread_mutex_init(&cs_log,NULL);
    pthread_mutex_init(&cs_HEX,NULL);
    pthread_mutex_init(&cs_BBB,NULL);
#endif
    Log("Start===========================================================\n");

    BBB.head=0;
    BBB.tail=0;
    BBB.size=0;

#ifdef _MSC_VER
    _beginthread((void(__cdecl *)(void *))thdA,0,(void *)1);
    _beginthread((void(__cdecl *)(void *))thdB,0,(void *)2);
#else
    threadsN=0;
    rc=pthread_create(&(threads[threadsN++]),NULL,thdA,(void *)1);if (rc) Log("%d=pthread_create %d error!\n",rc,threadsN-1);
    rc=pthread_create(&(threads[threadsN++]),NULL,thdB,(void *)2);if (rc) Log("%d=pthread_create %d error!\n",rc,threadsN-1);
#endif

    if (!access("No_Loop",0)) {
        remove("No_Loop");
        if (!access("No_Loop",0)) {
            No_Loop=1;
        }
    }
    while (1) {
        sleep_ms(1000);
        if (No_Loop) break;//
        if (!access("No_Loop",0)) {
            No_Loop=1;
        }
    }
    sleep_ms(3000);
    Log("End=============================================================\n");
#ifdef _MSC_VER
    DeleteCriticalSection(&cs_BBB);
    DeleteCriticalSection(&cs_HEX);
    DeleteCriticalSection(&cs_log);
#else
    pthread_mutex_destroy(&cs_BBB);
    pthread_mutex_destroy(&cs_HEX);
    pthread_mutex_destroy(&cs_log);
#endif
    return 0;
}

void initSocket_T()
{
    mainSocket();
}

