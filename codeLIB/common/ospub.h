/******************************************************************************
Copyright(C),2009-, Eastcom
Author:zhuyanpeng
Date:2009-7-20
Description:this file describes interfaces that operation subsystem provides to application.
modification history:
2009-7-20  zhuyanpeng  create
******************************************************************************/
#ifndef __OSPUB_H__
#define __OSPUB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sys.h"

/*---------------------------thread management---------------------------------*/
extern EINT32 CreatePhysicalThread(ETFUNCPTR f, void * y, char * taskname, EINT32 stacksize, EINT32 priority, EINT32 fid);
                                                                                /*create thread(task)*/

extern EINT32 CreateCommonThread(ETFUNCPTR f, void * y, char * taskname, EINT32 stacksize, EINT32 priority);
                                                                                /*create thread(task)*/

extern EINT32 TerminatePhysicalThread(EINT32 id);                               /*delete thread(task)*/

extern EINT32 SleepThread(EINT32 ms);                                           /*delay thread(task)*/

extern EINT32 SetPhyThreadPriority(EINT32 id, EINT32 priority);                 /*set thread'priority*/

extern EINT32 GetPhyThreadPriority(EINT32 id);                                  /*get thread priority*/

extern EUINT32 GetCurrentPhyThreadId(void);                                      /*get current thread ID*/

extern EUCHAR GetCurrentFid(void);                                              /*get current thread'FID*/

extern ETSEM_ID CreateSem(EINT32 flag);                                         /*create semaphore*/

extern EINT32 DeleteSem(ETSEM_ID id);                                           /*delete semaphore*/

extern EINT32 ObtainSem(ETSEM_ID id, EINT32 waitTime);                           /*get semaphore*/

extern EINT32 GiveSem(ETSEM_ID id);                                             /*give up semaphore*/

extern EINT32 RegTaskCmd(void);                                                 /*register mml command*/

/* save bps date string to buf */
extern void GetDateString(char *buf, int len);

/*---------------------------memory management---------------------------------*/
#ifdef ET_DEBUG

#ifdef WINDOWS

#define ADDR_BASE   0x00010000
#define ADDR_END    0x7ffeffff

extern void pathSplitVxToWin(char* src,int max);
#endif

#ifdef VXWORKS
extern char* sysMemStart ();
extern char* sysMemTop ();
#define ADDR_BASE   ((EUINT32)sysMemStart())
#define ADDR_END    ((EUINT32)sysMemTop())

#endif

#ifdef LINUX

#define ADDR_BASE   0x00000000
#define ADDR_END    0xBFFFFFFF

#endif

#ifdef AIX

#define ADDR_BASE   0x00000000
#define ADDR_END    0xBFFFFFFF

#endif


extern void * et_memcpy(void * dest,const void * src,EUINT32 num,char * file,int line);
extern int et_memcmp(const void * dest,const void * src,EUINT32 num,char * file,int line);
extern void * et_memset(void * dest,int ch,int num,char * file,int line);
extern char * et_strcpy(char * dest,const char * src,char * file,int line);
extern char * et_strncpy(char * dest,const char * src,EUINT32 num,char * file,int line);
extern int et_strcmp(const char * dest,const char * src,char * file,int line);
extern int et_strncmp(const char * dest,const char * src,EUINT32 num,char * file,int line);
extern char *getDocDir(void);
#define ETMEMCPY(x,y,z)     et_memcpy((x),(y),(z),__FILE__,__LINE__)
#define ETMEMCMP(x,y,z)     et_memcmp((x),(y),(z),__FILE__,__LINE__)
#define ETMEMSET(x,y,z)     et_memset((x),(y),(z),__FILE__,__LINE__)
#define ETSTRCPY(x,y)       et_strcpy((x),(y),__FILE__,__LINE__)
#define ETSTRNCPY(x,y,z)    et_strncpy((x),(y),(z),__FILE__,__LINE__)
#define ETSTRCMP(x,y)       et_strcmp((x),(y),__FILE__,__LINE__)
#define ETSTRNCMP(x,y,z)    et_strncmp((x),(y),(z),__FILE__,__LINE__)

#else

#define ETMEMCPY(x,y,z)     memcpy((x),(y),(z))
#define ETMEMCMP(x,y,z)     memcmp((x),(y),(z))
#define ETMEMSET(x,y,z)     memset((x),(y),(z))
#define ETSTRCPY(x,y)       strcpy((x),(y))
#define ETSTRNCPY(x,y,z)    strncpy((x),(y),(z))
#define ETSTRCMP(x,y)       strcmp((x),(y))
#define ETSTRNCMP(x,y,z)    strncmp((x),(y),(z))

#endif


extern EINT32 InitDmmLib(EINT32 offset, EINT32 total);                          /*initialize dmm*/

extern void * AllocMemory(EINT32 volume, ECHAR * filename, EINT32 line);        /*allocate memory*/

extern EINT32 subFreeMemBlock(void * address, char * name, int line);           /*free memory*/

extern EINT32 RegMemCmd(void);                                                  /*register mml command*/


/*  对VS2005，默认的字符集是Unicode。如果程序中使用字符串常量时一定要显示进行类型转换，否则编译时报错 */
//wuhtest
#define ALLOCDMM(volume) AllocMemory((volume),(ECHAR *)__FILE__,__LINE__)

#define FreeMemBlock(address) subFreeMemBlock((address),(char *)__FILE__,__LINE__)

extern EULONG GetVolOfFreeMem(void);

/*----------------------------message lib--------------------------------------*/

/*thread identifier struct*/
struct CPID_t
{
    EUINT16 Pid;                                                                /*thread ID*/
    EUCHAR Fid;                                                                 /*function ID*/
    EUCHAR Mid;                                                                 /*board function ID*/
};
#ifdef LINUX
#define MAX_MSG_BODY_LEN    1536                                                /*max length of message parameters*/
#else
#define MAX_MSG_BODY_LEN    1024                                                /*max length of message parameters*/
#endif

/*UDC message struct*/
typedef struct UDCMsg_t
{
    struct CPID_t host;                                                         /*message'reciever identifier*/
    struct CPID_t sender;                                                       /*message'sender identifier*/
    EUINT16 code;                                                               /*message'type code*/
    EUINT16 length;                                                             /*length of message parameters*/
    EUCHAR body[MAX_MSG_BODY_LEN];                                              /*message parameters*/
} APP_MSG;

/*message node struct.message is trasferred by this struct*/

#ifdef OS_MSG_DEBUG
#define MAX_NAME_LENGTH 64
#endif

typedef struct msgNode_t
{
    int free;                                                                   /*flag of being free*/
    struct msgNode_t *next;                                                     /*pointer to next node*/
    void *pSdu;                                                                 /*SDU message struct pointer*/
    APP_MSG *pUdcMsg;                                                           /*UDC message struct pointer*/
#ifdef OS_MSG_DEBUG
    char filename[MAX_NAME_LENGTH];
    EINT32 line;
#endif
} MSG_NODE;

extern EUCHAR GetCurrentMid();

extern EINT32 SetCurrentMid(EUCHAR m);

extern EINT32 InitMsgLib(void);                                                 /*message lib initialize*/

extern MSG_NODE * subGetMsgNode(char * filename, EINT32 line);                  /*get free message node*/

extern EINT32 FreeMsgNode(MSG_NODE * pMsg);                                     /*free message node memory*/

extern EINT32 RegLocalClient(EUCHAR fid, ECHAR *clientName, EINT32 clientPriority, ETFUNCPTR func, EINT32 stackSize);
                                                                                /*register local client*/
extern EINT32 RegSnmpClient(EUCHAR fid,ETFUNCPTR func);

extern EINT32 RegRemoteClient(EUCHAR mid, EUINT16 pid, ECHAR * clientName, ECHAR * ipAddr);

EINT32 RegRemoteClientPort(EUCHAR mid,EUINT16 pid,ECHAR * clientName,ECHAR * ipAddr, EUINT16 peerPort);

extern EINT32 RegDSPClient(EUCHAR mid,EUINT16 pid,ECHAR * clientName,ETFUNCPTR dspEntry);
                                                                                /*register dsp client*/
extern EINT32 UpdateRemoteClient(EUCHAR mid,EUINT16 pid,ECHAR * clientName,ECHAR * ipAddr,ETFUNCPTR dspEntry);
                                                                                /*update remote client by mid/pid*/

extern EINT32 DelLocalClient(EUCHAR fid);                                       /*logout local client*/

extern EINT32 DelRemoteClient(EUCHAR mid, EUINT16 pid);                         /*logout remote client*/

extern EINT32 RecvMsg(MSG_NODE * pMsg);                                         /*receive messages*/

extern EINT32 SendMsg(MSG_NODE * pMsg);                                         /*send common messages*/

extern EINT32 PushMsg(MSG_NODE * pMsg);                                         /*send urgent messages*/

extern EINT32 splResource(EINT32 fid);                                          /*protect resource*/

extern EINT32 splxResource(EINT32 fid);                                         /*give up resource*/

extern EINT32 RegMsgCmd(void);

#define GetMsgNode() subGetMsgNode((char *)__FILE__,__LINE__)
/*----------------------------timer lib--------------------------------------*/

/*date/time struct*/
typedef struct
{
    EUINT16 year;                                                                /*year*/
    EUCHAR month;                                                                /*month*/
    EUCHAR day;                                                                    /*day*/
    EUCHAR dayofweek;                                                            /*week*/
    EUCHAR hour;                                                                /*hour*/
    EUCHAR minute;                                                                /*minute*/
    EUCHAR second;                                                                /*second*/
} ETDATE;

/*plan task executing time*/
typedef struct
{
    ETDATE startTime;                                                            /*starting time*/
    EUCHAR occurs;                                                                /*task executing frequency 1 dayly 2 weekly 3 monthly */
    EUCHAR weekly;                                                                /*bit0 sun bit1 mon bit2 tue bit3 wed
                                                                                    bit4 thu bit5 fri bit6 sat bit7 reserved*/
    EUINT monthly;                                                                /*bit1 first day,bit2 second day,......*/
} JOB_SCHEDULE;

extern ETDATE systemDate;                                                       /*date*/

extern void SetDate(ETDATE date);                                               /*set date*/

extern void GetDate(ETDATE * pCurrentDate);                                     /*get current date*/

extern EINT32 InitTimerLib(EINT32 timer_total);                                 /*initialize timer module*/

extern EINT32 CreateRTimer(EUINT32 count, EUINT16 msgCode, EUCHAR fid, EUINT32 n, ...);/*create relative timer*/

extern EINT32 CreateCTimer(EUINT32 count, EUINT16 msgCode, EUCHAR fid, EUINT32 n, ...);/*create cycle timer*/

extern EINT32 CreateRTimerOfPid(EUINT32 count, EUINT16 msgCode, EUCHAR fid, EUINT16 pid, EUINT32 n, ...);      /*create relative timer*/
extern EINT32 CreateTimer(EUINT32 count, EUINT16 msgCode, EUCHAR fid, EUINT16 pid, EUCHAR type, EUINT32 n, ...);      /*create timer*/

extern EINT32 DeleteTimer(EINT32 handle);                                       /*stop/cancel timer */

extern EUINT GetTimerTick(void);                                                /*get total ticks,s*/

EUINT GetTimerMsTick(void);                                                     /*get total ticks,ms*/

extern void phyTimerIsr(void);

extern EULONG GetInterruptTicks();

extern EULONG GetIdleTicks();

extern EULONG GetKernelTicks();

extern EULONG GetTaskTicks();

extern EINT32 RegTimerCmd(void);                                                /*register mml command*/

/*-------------------------ICP接口---------------------------------------------*/
#define GETICP_STATE_CLOSED  0
#define GETICP_STATE_OPEN  2

#define    ICP_REPORT_OPEN 9
#define    ICP_REPORT_CLOSE 10

typedef void (*ReportState)(int chanId,int state) ;
typedef void (*ReportData)(int chanId,char *pBuf,int len);

//1)模块初始化
extern int InitIcpLib (void);
//返回值：OK表示成功，ERROR表示失败。

//2)ICP通道开通
extern int OpenIcpChanMsg(int peerIp);
extern int OpenIcpChanB1(int peerIp);
extern int OpenIcpChanB1Pdcp(int peerIp);
extern int OpenIcpChanB1Port(int peerIp, EUINT16 port);
extern int OpenIcpChanMsgPort(int peerIp, EUINT16 port);


//peerIp：远端IP地址
//返回值：返回所开通的ICP通道的ID，ERROR表示失败。

//3)ICP通道关闭
extern int CloseIcpChan (int chanId);
//chanId：信道的ID
//返回值：OK表示成功。

//4)发送消息
extern int SendMsgByIcp (int chanId, MSG_NODE *pData);
//chanId：ICP通道的ID
//pData：指向发送的数据
//len：数据长度
//返回值：OK表示成功，ERROR表示失败。
extern int SendB1ByIcp(int chanId, void *pData, int length);


#define MSGGETSHORT(s, cp) { \
    register unsigned char *t_cp = (unsigned char *)(cp); \
    (s) = ((unsigned short)t_cp[0] << 8) \
        | ((unsigned short)t_cp[1]) ;\
}

#define MSGGETLONG(l, cp) { \
    register unsigned char *t_cp = (unsigned char *)(cp); \
    (l) = ((unsigned long)t_cp[0] << 24) \
        | ((unsigned long)t_cp[1] << 16) \
        | ((unsigned long)t_cp[2] << 8) \
        | ((unsigned long)t_cp[3]) ;\
}

#define MSGPUTSHORT(s, cp) { \
    register unsigned short t_s = (unsigned short)(s); \
    register unsigned char *t_cp = (unsigned char *)(cp); \
    *t_cp++ = (unsigned char )(t_s >> 8); \
    *t_cp   = (unsigned char )(t_s); \
}

#define MSGPUTLONG(l, cp) { \
    register unsigned long t_l = (unsigned long)(l); \
    register unsigned char *t_cp = (unsigned char *)(cp); \
    *t_cp++ = (unsigned char )(t_l >> 24); \
    *t_cp++ = (unsigned char )(t_l >> 16); \
    *t_cp++ = (unsigned char )(t_l >> 8); \
    *t_cp   = (unsigned char )(t_l); \
}
extern int SetB1Multi(EUINT32 ipAddr);
extern int DelB1Multi(EUINT32 ipAddr);
extern EINT32 RegIcpCmd(void);
extern  int  GetIcpChannelState(int chanid);
extern  int GetIcpPeerIpByChanId(int chanid);

typedef int (*FUNCICPCHANCFG)(int);

extern int RegIcpReportCallBack(int chanid,
    ReportState pReportState,
    ReportData pReportData);
extern int DelRegIcpReportCallBack(int chanid,
    ReportState pReportState,
    ReportData pReportData);
/*---------------------------end ICP接口-----------------------------------------------*/


/*******************etLogLib************************************/


typedef enum
{
    FILE_DEV = 0x01,
    SOCKET_DEV = 0x02,
    NETFILE_DEV,

} LOG_DEV;



typedef enum
{
    LOG_MOD_ICP = 0x00000001,
    LOG_MOD_SYSCTRL = 0x00000002,
    LOG_MOD_BDBGR = 0x00000004,
    LOG_MOD_LLCP = 0x00000008,
    LOG_MOD_MLE = 0x00000010,
    LOG_MOD_CC = 0x00000020,
    LOG_MOD_SDS = 0x00000040,
    LOG_MOD_SS = 0x00000080,
    LOG_MOD_VLR =0x00000100,
    LOG_MOD_HLR = 0x00000200,
    LOG_MOD_MM = 0x00000400,
    LOG_MOD_BB1AP = 0x00000800,
    LOG_MOD_MEM =0x00001000,
    LOG_MOD_MSG = 0x00002000,
    LOG_MOD_TIMER = 0x00004000,
    LOG_MOD_THREAD = 0x00008000,
    LOG_MOD_NTP =0x00010000,
    LOG_MOD_BEAR = 0x00020000,
    LOG_MOD_CMD = 0x00040000,
    LOG_MOD_MAC = 0x00080000,
    LOG_MOD_LLCF =0x00100000,
    LOG_MOD_TP = 0x00200000,
    LOG_MOD_RM = 0x00400000,
    LOG_MOD_SDU = 0x00800000,
    LOG_MOD_SNMP    = 0x01000000,
    LOG_MOD_RDT        = 0x02000000,
    LOG_MOD_IB1AP    = 0x04000000,
//EDS LOG MOD ID
    LOG_MOD_GUI        = 0x08000000,
    LOG_MOD_TNMM_SAP= 0x10000000,
    LOG_MOD_OAM        = 0x20000000,
    LOG_MOD_FR        = 0x40000000,
    LOG_MOD_IPQOS    = 0x80000000,

    LOG_MOD_INIAP    = 0x00000001,
    LOG_MOD_DATA    = 0x00000002,
    LOG_MOD_PDC_B1AP= 0x00000004,
    LOG_MOD_PDCP    = 0x00000008,
    LOG_MOD_BIOS    = 0x00000010,
    LOG_MOD_COMP    = 0x00000020,
    LOG_MOD_RS485    = 0x00000040

} LOG_MOD;

/***************etLogLib******************************************
 InitLogLib() - initialize the Bluefin log facility
 */
extern EINT32 InitLogLib(void);

/**************************************************************************
 PrintfLog - Bluefin log information output routine
 This routine stores the information to the log buffer and invokes the log task.
 No real I/O operation happens. If there is not enough free space in log buffer,
 information may lose.
 Returns: OK or ERROR
 */
extern EINT32 PrintfLog(EUINT32 logLevel,  /* the global defined information level, see BF_LOG_LVL */
    EUINT32 fid,    /* which module is the caller */
    const ECHAR* fmt,  /* format string to write */
    ...                 /* optional arguments to format string */
);

/**************************************************************************
 PrintfLogPkt - Bluefin packet information output routine
 This routine stores the information to the packet buffer and invokes the log task.
 No real I/O operation happens. If there is not enough free space in packet buffer,
 information may lose.
 */
extern EINT32 PrintfLogPkt(EUINT32 logLevel,  /* the global defined information level, see BF_LOG_LVL */
    EUINT32 fid, /* which module is the caller */
    const ECHAR *data,         /* where is the raw data of the packet */
    EINT32 len,            /* number of bytes of the packet */
    const ECHAR* fmt,  /* format string to write, put any comments here */
    ...                 /* optional arguments to format string */
);


/*打印SUD log*/
extern EINT32 PrintfLogSDU(EUINT32 logLevel,  /* the global defined information level, see BF_LOG_LVL */
    EUINT32 fid, /* Function ID */
    struct MP_BLK_t *sdu, const ECHAR * fmt,  /* format string to write, put any comments here */
    ...                 /* optional arguments to format string */
);

/**************************************************************************
 AddLogDev - Add ET log device
 This routine adds a log device to log device list. If file descriptor is used,
 the caller is responsible for opening the corresponding file
 Inputs:
 lvlFilter - the level filter of this output
 modFilter - the module filter of this output
 fd        - file descriptor, set to -1 when filename is valid
 fileName  - file name, set to NULL if fd is valid
 Return:
 OK or ERROR
 */
extern EINT32 AddLogDev(EUINT32 lvlFilter,  /* what is the level filter of this output */
    EUINT32 modFilter,  /* what modules this output care */
    EINT32* fd,         /* log file descripor, set to -1 when filename is valid */
    ECHAR *fileName, /* log file name, set NULL when fd is valid */
    LOG_DEV type);//Log device type





  /**************************************************************************
 AddLogDev3 - Add ET log device
 This routine adds a log device to log device list. If file descriptor is used,
 the caller is responsible for opening the corresponding file
 Inputs:
 lvlFilter - the level filter of this output
 modFilter - modules 1 to 32
modFilterSecond - moduls 33 to 64
 fd        - file descriptor, set to -1 when filename is valid
 fileName  - file name, set to NULL if fd is valid
 Return:
 OK or ERROR
 */
extern EINT32 AddLogDevExFid(EUINT32 lvlFilter,  /* what is the level filter of this output */
    EUINT32 modFilter,  /* what modules this output care */
    EUINT32 modFilterSecond,/*fid 33 to 64*/
    EINT32* fd,
    /* log file descriptor pointer, set *fd to 0 when filename is appointed
     * if the *fd is a valid value(*fd>0) ,please input the value;
     */
    ECHAR* fileName, /* log file name, never be null */
    LOG_DEV type) ;  /*日志设备类型*/


/********设置日志设备日志过滤等级，模块号*********************/
/********其中模块号为module number,非fid********************************/
/********其命令行实现为输入fid*************************************/
/*
参数:    dataFd     -     输入日志设备的文件描述符（文件设备）或socket号(telnet设备)
             lvlFilter     -     日志设备的过滤等级
             modFilter -    日志设备的modules
             type        -    日志设备类型

*/
extern ESTATUS SetLogDev(EINT32 dataFd, EUINT32 lvlFilter,
                    EUINT32 modFilter/*modules1 to 32*/,
                    EUINT32 modFilterSecond, /*moduls 33 to 64*/
                    LOG_DEV type );



/**************************************************************************
 DelLogDev - delete a log device
 This routine delete a log device from list. If file descriptor is used, the
 caller is responsible for closing the corresponding file.
 Inputs:
 fd       - the file descriptor, set to -1 if fileName is valid
 fileName - the file name, set to NULL if file descriptor is valid
 Return:
 OK or ERROR
 */
extern EINT32 DelLogDev(EINT32 fd, ECHAR* fileName, LOG_DEV type);








/*********************End of etLogLib**********************/

/*********************etFileLib***************************/

/************************************************************************
 Function：       openBinFile
 Description：    打开二进制文件
 Input：          filename:文件名
 mode:模式
 OPEN_FILE_RO = 0,         //打开读,如果文件不存在也不创建。
 OPEN_FILE_WO = 1,          //打开写,如果文件不存在则创建。
 OPEN_FILE_RW = 2,          //打开读写,如果文件不存在则创建。
 OPEN_FILE_RWA = 3,        //打开添加,如果文件不存在则创建。
 CREATE_EXIST_ERR = 4,     //创建文件，如果文件存在则报错。
 OPEN_NONE_ERR = 5,        //打开文件，如果文件不存在则报错。
 OPEN_FILE_DEF = 6        //缺省方式，如果文件存在则将文件内容全部删除；指针指为文件起始,如果文件不存在则创建

 Return：         文件描述符 或 错误代码
 ************************************************************************/
extern EINT32 OpenBinFile(const ECHAR* filename, OPEN_MODE mode);
/*
 * @des:redirect fd
 * @para:
 * fd: file describe
 * position: the location that you want
 */
extern EINT32 SeekBinFile(EINT32 fd, EINT32 position, EINT32 offset);
/*Close file*/
extern EINT32 CloseBinFile(EINT32 fd);
/*write file*/
extern EINT32 WriteBinFile(EINT32 fd, ECHAR* buffer, EINT32 nbytes);
/*read file*/
extern EINT32 ReadBinFile(EINT32 fd, ECHAR* buffer, EINT32 maxbytes);
/*remove file*/
extern EINT32 RemoveBinFile( ECHAR* filename);

/*delete directory*/
extern EINT32 RemoveDir(ECHAR* name);
/*create directory*/
extern EINT32 MakeDir( ECHAR* name);
/*@change directory
 * @para:
 * name：目录文件名
 返回值：0或-1
 * */
extern EINT32 ChangeCurrentDir(ECHAR* name, ECHAR* currentdir);


/*rename file*/
extern EINT32 RenameFile(const ECHAR*, ECHAR*);

/* save file whith sleep */
extern ESTATUS IMGMGR_UpdatFlashImage(char *pFileName, char *pBuf, int bufLen);

#ifdef VXWORKS
/*Get file from ftp server(host)*/
extern ESTATUS GetFile(char* host, char* user, char* passwd, char* fileName);
/*Send file to ftp server(host)*/
extern ESTATUS SendFile(char* host, char* user, char* passwd, char* fileName);

/*****************************End of etFileLib********************/

/*******************For extern dump exception******************************/

/*return 0 success, -1 fail*/
extern EINT32 dumpInit();

/*print exception interface by user programmer:)
 * return 0 success, -1 fail*/
extern EINT32 dumpHealthRecord(char * buffer);

extern EINT8 ClearDump(void);
/*set first debug parameter*/
extern void SetGlobalIntOne(EINT32);
/*set second debug parameter*/
extern void SetGlobalIntTwo(EINT32);

extern void SetCurTask(char*);

#endif
/*******************End of dump exception**********************************/

/*******************SysLog ************************************************/

typedef enum
{

	SYSLOG_KERNEL		= 0,	//             kernel messages
	SYSLOG_USER			= 1,	//             user-level messages
	SYSLOG_MAIL			= 2,	//             mail system
	SYSLOG_SYSTEM		= 3,	//             system daemons
	SYSLOG_SECURITY		= 4,	//             security/authorization messages (note 1)
	SYSLOG_MESSAGES		= 5,	//             messages generated internally by syslogd
	SYSLOG_PRINTER		= 6,	//             line printer subsystem
	SYSLOG_NETWORK		= 7,	//             network news subsystem
	SYSLOG_UUCP			= 8,	//             UUCP subsystem
	SYSLOG_CLOCK		= 9,	//             clock daemon (note 2)
	SYSLOG_AUTH			= 10,	//             security/authorization messages (note 1)
	SYSLOG_FTP			= 11,	//             FTP daemon
	SYSLOG_NTP			= 12,	//             NTP subsystem
	SYSLOG_AUDIT		= 13,	//             log audit (note 1)
	SYSLOG_ALERT		= 14,	//             log alert (note 1)
	SYSLOG_CLOCK2		= 15,	//             clock daemon (note 2)
	SYSLOG_LOCAL_USE0	= 16,	//             local use 0  (local0)
	SYSLOG_LOCAL_USE1	= 17,	//             local use 1  (local1)
	SYSLOG_LOCAL_USE2	= 18,	//             local use 2  (local2)
	SYSLOG_LOCAL_USE3	= 19,	//             local use 3  (local3)
	SYSLOG_LOCAL_USE4	= 20,	//             local use 4  (local4)
	SYSLOG_LOCAL_USE5	= 21,	//             local use 5  (local5)
	SYSLOG_LOCAL_USE6	= 22,	//             local use 6  (local6)
	SYSLOG_LOCAL_USE7	= 23,	//             local use 7  (local7)

}SYSLOG_FACILITY;
typedef enum
{
	SYSLOG_EMERGENCY	= 0,	//       Emergency: system is unusable
	SYSLOG_ALERT_PRI	= 1,	//       Alert: action must be taken immediately
	SYSLOG_CRITICAL		= 2,	//       Critical: critical conditions
	SYSLOG_ERROR		= 3,	//       Error: error conditions
	SYSLOG_WARNING		= 4,	//       Warning: warning conditions
	SYSLOG_NOTICE		= 5,	//       Notice: normal but significant condition
	SYSLOG_INFO			= 6,	//       Informational: informational messages
	SYSLOG_DEBUG		= 7,	//       Debug: debug-level messages

}SYSLOG_PRI;
extern EINT32 etSysLogInit();
extern EINT32 etSysLog(ECHAR facilty, ECHAR Pri, ECHAR Fid, EINT16 Pid, const ECHAR * fmt, ...);

/*******************SysLog ************************************************/

#ifdef __cplusplus
}
#endif

#endif

