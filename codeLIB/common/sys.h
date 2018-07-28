/******************************************************************************
Copyright(C),2009-, Eastcom
Author:
Date:
Description:
Others:
******************************************************************************/

#ifndef __ETRA_SYS_H__
#define __ETRA_SYS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ETOK            0
#define ETERROR         -1
#define ETNORMAL        1

#define ETTRUE  1
#define ETFALSE 0


#define BPSLIB_VERSION_MAJOR   "4"
#define BPSLIB_VERSION_UPPER   "1"
#define BPSLIB_VERSION_MIDDLE  "0"
#define BPSLIB_VERSION_MINOR   "11"


#define TASK_SNMP_TRAP_PRI          149  /* snmp trap client task priority */
#define TASK_SNMP_CORE_PRI          150  /* snmp trap client task priority */
#define TASK_SNMP_CFGSAVE_PRI       151  /* snmp cfg save task priority */
#define TASK_SNMP_CFGGET_PRI        152  /* snmp cfg get task priority */
#define TASK_SNMP_UPDATEIMAGE_PRI   153  /* snmp update image task priority */
#define TASK_SNMP_REBOOT_PRI        154  /* snmp reboot task priority */


/*Add by Lv Yanlin*/

#define ET_FILENAME_MAX        20
#define ET_PATHNAME_MAX        196

typedef enum
{
    OPEN_FILE_RO = 0,
    OPEN_FILE_WO = 1,
    OPEN_FILE_RW = 2,
    OPEN_FILE_RWA = 3,
    CREATE_EXIST_ERR = 4,
    OPEN_NONE_ERR = 5,
    OPEN_FILE_DEFAULT = 6
    
}OPEN_MODE;

typedef enum
{
    LOG_INFO = 0x01,
    LOG_ALARM_1 = 0x02, 
    LOG_ALARM_2 = 0x04, 
    LOG_ALARM_3 = 0x08, 
    LOG_PACKET = 0x10, 
    LOG_SHOW = 0x20, /* for show routine output, non-markable */
    LOG_ERROR = 0x40  /* for critical error output, non-markable */
} LOG_LVL;



#ifdef ET_DEBUG
#define DEBUG_BUILD
#define ICP_DEBUG
#define OS_MEM_DEBUG
#define OS_MSG_DEBUG
#define OS_TASK_DEBUG
#define OS_TIMER_DEBUG
#define SDU_DEBUG
#define BEAR_DEBUG

#endif

#ifdef WINDOWS

#pragma warning(disable:4115)
#pragma warning(disable:4127)   /* FDSET */


#define _WIN32_WINNT 0x0400

#include "etwindows.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <io.h>
#include <process.h>
#endif /*WINDOWS*/

#ifdef VXWORKS
#include <vxworks.h>
#include <stdio.h>
#include <string.h>
#include <errnoLib.h>
#include <inetLib.h>
#include <ioLib.h>
#include <sockLib.h>
#include <stdLib.h>
#include <strLib.h>
#include <loglib.h>
#include <dosfslib.h>
#include <dirent.h>
#include <stat.h>
#include <fioLib.h>
#include <netLib.h>
#include <tickLib.h>
#include <intLib.h>
#include <sysLib.h>
#include <sioLib.h>
#include <memLib.h>
#include <hostLib.h>
#include <math.h>

extern STATUS    taskLock     (void);
extern STATUS    taskUnlock     (void);

extern int select(int, fd_set *, fd_set *, fd_set *, struct timeval *);

#define __cdecl
#define __stdcall
#endif /*VXWORKS*/

#ifdef LINUX
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sched.h>
#include <limits.h>
#include <time.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <linux/netdevice.h>
#include <net/if_arp.h>   
#include <arpa/inet.h>
#include <elf.h>

#define __stdcall
#endif /*LINUX*/
#ifndef IMPORT
#define IMPORT extern
#endif




#ifdef AIX
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sched.h>
#include <limits.h>
#include <time.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#define __stdcall
#endif 



#ifndef LOCAL
#define LOCAL static
#endif

#ifdef WINDOWS
typedef signed char             ECHAR;
typedef unsigned char           EUCHAR;
typedef ECHAR                   EINT8;
typedef EUCHAR                  EUINT8;
typedef short                   EINT16;
typedef unsigned short          EUINT16;
typedef int                     EINT32;
typedef unsigned long int       EUINT32;

typedef unsigned short          EUSHORT;
typedef unsigned int            EUINT;
typedef unsigned long           EULONG;
typedef int                     ESTATUS;

typedef int                     EBOOL;

typedef __int64                 EINT64;
typedef unsigned __int64        EUINT64;

typedef unsigned long           IP_ADDRESS;
typedef EUINT64                 ELONGSTATS;
typedef int                     socklen_t;

typedef int (*FUNCPTR) ();     /* ptr to function returning int */
typedef void (*VOIDFUNCPTR) (); /* ptr to function returning void */
typedef unsigned long int ulong_t;
typedef unsigned char uchar_t;
#define NONE        (-1)    /* for times when NULL won't do */
#define EOS        '\0'    /* C string terminator */
//#define    EWOULDBLOCK    70        /* Operation would block */
#endif /*WINDOWS*/

#ifdef VXWORKS
typedef signed char             ECHAR;
typedef unsigned char           EUCHAR;
typedef ECHAR                   EINT8;
typedef EUCHAR                  EUINT8;
typedef short                   EINT16;
typedef unsigned short          EUINT16;
typedef int                     EINT32;
typedef unsigned int            EUINT32;


typedef unsigned long           IP_ADDRESS;
typedef unsigned short          EUSHORT;
typedef unsigned int            EUINT;
typedef unsigned long           EULONG;
typedef int                     ESTATUS;
/*typedef int                     socklen_t;*/

typedef int                     EBOOL;

typedef long long               EINT64;
typedef unsigned long long      EUINT64;

typedef EUINT64                 ELONGSTATS;    /* compiler/libc issues */

#define     DUMP_HIST_MSG_NUM               128
#define     DUMP_MSG_PROCESSED_NUM          64

#endif /*VXWORKS*/

#if defined(LINUX) || defined(AIX)
typedef char                    ECHAR;
typedef unsigned char           EUCHAR;
typedef ECHAR                   EINT8;
typedef EUCHAR                  EUINT8;
typedef short                   EINT16;
typedef unsigned short          EUINT16;
typedef int                     EINT32;
typedef unsigned int            EUINT32;

typedef unsigned short          EUSHORT;
typedef unsigned int            EUINT;
typedef unsigned long           EULONG;
typedef int                     ESTATUS;

typedef int                     EBOOL;

typedef long long               EINT64;
typedef unsigned long long      EUINT64;

typedef unsigned int            IP_ADDRESS;
typedef EUINT64                 ELONGSTATS;

typedef int (*FUNCPTR) ();     /* ptr to function returning int */
typedef void (*VOIDFUNCPTR) (); /* ptr to function returning void */
typedef unsigned long int ulong_t;
typedef unsigned char uchar_t;

typedef int BOOL;
extern EUCHAR GetCurrentMid();
#define DUMP_HIST_MSG_NUM   128
#define EOS '\0'
#endif
#define FID_MAX         64      /*max value of FID,0 - 63 is valid*/
/* BSC FID define */
#define FID_ICP         1       /* 板间通信 */
#define FID_SYSCTRL     2       /* 系统控制 */
#define FID_BDBGR       3       /* 单板管理 */
#define FID_LLCP        4       /* 逻辑链路层PROC */
#define FID_MLE         5       /* 移动链路实体 */
#define FID_CC          6       /* 呼叫控制 */
#define FID_SDS         7       /* 短数据服务 */
#define FID_SS          8       /* 补充业务 */
#define FID_VLR         9       /* 拜访位置寄存器 */
#define FID_HLR         10      /* 归属数据库 */
#define FID_MM          11      /* 移动管理 */
#define FID_BB1AP       12      /* B1接口 */
#define FID_MEM         13      /* 内存管理 */
#define FID_MSG         14      /* 消息管理 */
#define FID_TIMER       15      /* 定时器 */
#define FID_THREAD      16      /* 进程管理 */
#define FID_NTP         17      /* 时间服务器 */
#define FID_BEAR        18      /* 承载 */
#define FID_CMD         19      /* 命令行 */
#define FID_MAC         20      /* MAC */
#define FID_LLCF        21      /* 逻辑链路层FM */
#define FID_TP          22      /* 基站事务处理 */
#define FID_RM          23      /* 资源管理 */
#define FID_SDU         24      /* sud管理 */
#define FID_SNMP        25      /* 网管代理 */
#define FID_RDT         26      /*主备*/
#define FID_IB1AP       27      /*下B1*/

//EDS Functon ID
#define FID_GUI         28
#define FID_TNMM_SAP    29
#define FID_OAM         30

#define FID_FR          31
#define FID_IPQOS       32

#define FID_INIAP       33      /*交换互联*/
#define FID_PDC_DATA    34      /*PDC 数据模块*/
#define FID_PDC_B1AP    35      /*PDC B1接口*/
#define FID_PDCP        36      /*PDP模块*/
#define FID_BIOS        37      /*调度BIOS*/
#define FID_COMP        38      /*主备竞争*/
#define FID_RS485       39      /*485设备*/
#define FID_CTLDSP      40      /* dspinf */
#define FID_PDC_RADIUS_CLIENT 41 /* PDC Radius Client */

#define FID_TPAL        42
#define FID_PPAL        43
#define FID_DNS         42      /*DNS*/
#define FID_APAL        43      /*dbox与analog接口*/
#define FID_SMCDB       44      /* 短信中心数据库功能块 */
#define FID_DR          45      /*容灾*/
#define FID_GWCF        46      /**/
#define FID_TEST        47      /*自动化测试用的FID*/
#define FID_DSINF       48      /*ds与dbox之间的接口*/
#define FID_EC          49      /*ec模块*/

#define FID_CRTP        50      /*帧中继压缩*/

#define FID_SCCSIO      51      /*sepura 串口AT 命令解析模块*/
#define FID_SLIC_FXO    52      /* dbox fxo 电话接口 */
#define FID_Q921        52      /*isgw q921 */
#define FID_L2TP        53      /*L2TP模块*/
#define FID_SLIC_RECORD 54      /*Play record*/
#define FID_PRIAP       54      /*isgw q931*/


#define FID_SLIC_FXS    55      /* dbox fxs 电话接口 */
#define FID_SNMP_GIS    55      /* gis */

#define FID_DSP         56      /* dsp desktop number */

#define FID_SCTP        60

#define FID_DS_PSTN     59      /* ds pstn */
#define FID_VOICE       61      /*与ds的FID*/
#define FID_AUDIT       62      /* 交换监测 */
#define FID_SNMP_RS     63      /* 全网录音 */ 


#define FID_PSIP        34      /*PSIP模块*/
#define FID_ESIP        35      /*ESIP模块*/
#define FID_SIPSTK      36      /*SIP协议栈*/
#define FID_IPAL        37      /*INIAP协议适配模块*/

/* SR FID DEFINES */
#define FID_LOWMAC        1
#define FID_DSPLOG        2

/* BBS */
#define FID_BBS_MAC     24      /* 桥接站车台MAC */
#define FID_BPAL        20      /* 桥接站B1 */
#define FID_CMCE        57      /* CMCE*/
#define FID_API			58      /* 交换中心与API SERVER之间的接口模块 */

/* DIAMETER */
#define FID_RDS			56

/*宽带融合*/
#define FID_BWTSIP		57
#define FID_CM          49      /*交换链接管理*/
/* BSC MID define */
#ifdef BOARD_TYPE_BCCP
#define MID_BSR         2       /* 载波板 */
#else
#define MID_BSR         1       /* 载波板 */
#endif
#define MID_BSC         2       /* 主用主控板 */
#define MID_PEER        (GetCurrentMid() | 0x10)    /* 对端BSC */
#define MID_ECN         4       /* 交换中心 */
#define MID_BSR_DSP     5       /* DSP */
#define MID_PDCP        6       /* PDP 模块*/
#define MID_RSRC        7       /* RSRC 模块*/
#define MID_CBSC        10      /* 同频同播中心BSC板*/

/* BSR MID define */
//#define MID_BSR         1       /* 载波板 */
//#define MID_BSC         2       /* 主控板 */
#define MID_DSP         5       /* DSP */

/* DBOX MID define*/
#define MID_DBOX        6       /*DBOX 单板*/
#define MID_DS          2       /*调度台*/
#define MID_TEST        6       /* 自动化测试 */
#define MID_FXGW		8		/* 移动基站互联互通设备 新工程FXGW*/
#define MID_DSGWO       8       /* 移动基站互联互通设备 DSGWO 在DBOX工程 */
#define MID_ISGW        9       /* ISGW */
#define PID_BROADCAST            0xffff      //广播用pid

#define MID_BBS        10       /*桥接站BSC*/
#define MID_APP        1        /*车载台用户层*/
#define MID_KER        2        /*车载台内核层*/
#define MID_MEDIA      11       /*媒体服务器*/

#ifdef WINDOWS
#define MIN_SYSMEMORY   0x2800000           //min of system dynamic memory
#else
#define MIN_SYSMEMORY   0x6000000           //min of system dynamic memory
#endif
extern EINT32 InitbasePlatform(EINT32 volume, char *prompt);
extern ECHAR* GetBPSLibInfo(void);
extern EUINT32 calcCrc32(EUINT32 crc, EUCHAR * pData, EINT32 len);

extern EINT32 InitBsrPlatform(void);            //initialize bsr platform
extern EINT32 InitBscPlatform(void);            //initialize bsc platform
extern EINT32 SetBoardId(EUINT16 id);           //set board(bsr/bsc) id,available only when debug
extern EUINT16 GetBoardId(void);                //get board(bsr/bsc) id

#if 1
#ifdef WINDOWS
#define ETSEM_ID  HANDLE
#endif

#ifdef VXWORKS
#define ETSEM_ID  SEM_ID
#endif

#if defined(LINUX) || defined(AIX)
typedef sem_t* ETSEM_ID;
#endif
#endif

#define ETNO_WAIT          0                                                    /*no block,return right now*/
#define ETWAIT_FOREVER     -1                                                   /*wait until getting semaphore*/

#define EMPTYSEM           0                                                    /*empty semaphore*/
#define FULLSEM            1                                                    /*full semaphore*/

#if defined(WINDOWS) || defined(VXWORKS)
typedef EULONG (__stdcall * ETFUNCPTR)(void * x);
#else
typedef void * (* ETFUNCPTR)(void * x);
#endif

#ifdef WINDOWS
#define ET_PACK_ALIGN(x)
#elif (defined VXWORKS) || (defined LINUX) || (defined(AIX))
#define ET_PACK_ALIGN(x) __attribute__((packed, aligned(x)))
#endif //VXWORKS

/******************************************SUD START*********************************************************/
#ifdef WINDOWS
#pragma warning(disable:4201)
#pragma warning(disable:4200)
#endif //WINDOWS

#define ET_SDU_TRACE                  //switch of trace information

typedef struct MP_SLAB_t              //MP_BUF控制结构
{
    struct MP_SLAB_t *pNext;          //指向MP_SLAB链表
    EUINT32 mpBufBitSize;             //MP_BUF的大小
    EUINT32 mpBufNum;                 //MP_BUF剩余数量
#ifdef ET_SDU_TRACE
    EUINT32 minMpBufCount;            //MP_BUF最小剩余数量
#endif //ET_SDU_TRACE
    struct MP_BUF_t *mpBufFreeList;   //指向MP_BUF的链表
} MP_SLAB;

typedef struct MP_BLK_t             //数据访问入口
{
    union
    {
        struct MP_BLK_t *pNextSdu;    //指向下一个数据包
        struct MP_BLK_t *pNext;     //指向下一个MP_BLK空闲块
    };
    EUINT32 dataBitLen;                //该MP_BLK所指向MP_BUF中的有效数据长度
    struct MP_BLK_t *pNextBlk;      //指向下该数据包的下一个数据块(MP_BLK)
    EUINT32 dataBitOffset;            //该MP_BLK所属MP_BUF中有效数据偏移值
    EUINT32 oldDataBitOffset;       //记录前一个dataBitOffset的位置
    EUINT32 currBitOffset;            //该MP_BLK所属MP_BUF当前写入位置偏移值
    EUINT32 oldCurrBitOffset;       //记录前一个currBitOffset的位置
    EUINT32 decodeBitOffset;        //该SDU数据包当前读取位置偏移值
    EUINT32 blankBitOffset;         //预留空隙的起始偏移量
    EUINT32 blankBitLen;            //预留空隙的长度
    struct MP_BUF_t *pMpBuf;        //指向MP_BLK所属MP_BUF
    EUINT32 sduBitLen;                 //数据包长度
#ifdef ET_SDU_TRACE
#define MAX_FILENAME_LEN 15
    ECHAR fileName[MAX_FILENAME_LEN + 1];   //分配该MP_BUF的文件名
    EUINT32 fileLine;                 //分配该MP_BUF的函数所在的行
#endif //ET_SDU_TRACE
} MP_BLK;

typedef struct MP_BUF_t                //数据存储单元
{
    union 
    {
        struct MP_BUF_t *pNext;        //指向下一个空闲MP_BUF
        struct MP_SLAB_t *pMpSlab;     //指向所属MP_SLAB
    };
    EUINT32 mpBufBitSize;             //数据MP_BUF大小
    EUINT32 refCount;                 //引用计数
    EUCHAR data[0];                   //数据
} MP_BUF;
/******************************************SUD END**********************************************************/

/*TRAP SERVER Configuration*/
#define MAX_TRAP_SERVER_NUM  4

#define DOC_PATH_MAX 256

//the index of physical queue
typedef enum IpQosPriority_t
{
    PRIORITY_0,
    PRIORITY_1,
    PRIORITY_2,
    PRIORITY_3,
    PRIORITY_4,
    
#ifndef AIX
    PRIORITY_MAX
#endif
} IPQOS_PRIORITY;

typedef int (*SYSTEM_MONITER_FUNCTION)(int module, int reason, int subReason);


enum 
{
    SYSTEM_MONITER_MODULE_SDU = 1,
    SYSTEM_MONITER_MODULE_MSG,
    SYSTEM_MONITER_MODULE_TIMER,
    SYSTEM_MONITER_MODULE_MEM = 4,
    SYSTEM_MONITER_MODULE_SOCKET,
    SYSTEM_MONITER_MODULE_FILE,
    SYSTEM_MONITER_MODULE_TASK,
    SYSTEM_MONITER_MODULE_MBUF = 8,
};

#ifdef __cplusplus
}
#endif

#endif  /*__ETRA_SYS_H__*/

