#ifndef __oampu_h__
#define __oampu_h__



#ifdef __cplusplus
extern "C" {
#endif

#define MSG_SNMP_REQUEST    0
#define MSG_SNMP_TRAP       1
#define MSG_SNMP_RESPONSE   2


/* 命令行用户等级 */
enum
{
    USLEVEL_NULL,
    USLEVEL_GENERAL,        /* 普通用户 */
    USLEVEL_IMPORTANT,      /* 重要用户 */
    USLEVEL_SUPER,          /* 超级用户 */
    USLEVEL_DEBUG,          /* DEBUG 用户 */
    USLEVEL_MAX             /* Unused */
};

/* 命令行参数检查，错误类型 */
enum
{
    NORMAL_PARAMETER,       /* 没错 */
    NO_PARAMETER,           /* 无参数输入 */
    ERROR_PARAMETER,        /* 错误参数 */
    UNKNOWN_PARAMETER,      /* 未知参数 */
    MISS_MAND_PARAMENTER    /* 缺少必填参数 */
};

#define MAX_MML_REG_NUM     2048    /* 最大 MML 命令数目 */
#define MAXOLDCMDCOUNT                  20      /* 历史记录数目 */
#define MAX_BYTES_PER_LINE              256     /* 命令行一次输入最大字符数 */
#define MAX_TOKEN                       6       /**/
#define MAX_SUPPORT_CLI_NUM             12      /* 10 Telnet + 1 TTY + 1 stdout*/
#define STREAMIODEV_SOCKET              1       /* 登录类型为 TELNET */
#define STREAMMSGTYPE_TTY               2       /* 登录类型为串口 */
#define STREAMIODEV_STDOUT              3       /* 登录类型为标准输出，用于批处理 */
#define MAX_OLDCMDPOOL_SIZE             0x800   /* 记录历史命令的缓冲区大小 */
#define CLI_CONN_TASK_PRIORITY          145     /* 命令行连接任务优先级 */
#define CLI_MAX_USERNAME_LEN            16      /* 用户名最大长度 */
#define CLI_MAX_PASSWORD_LEN            16      /* 密码最大长度 */
#define MAX_CLI_USER    32  /* 可注册最大用户数 */
#define DEF_DIR_LEN     ET_PATHNAME_MAX
#define MAX_CLI_FILENAME    ET_FILENAME_MAX

enum
{
    MMLKEY_NULL,
    MMLKEY_ID,
    MMLKEY_NUMBER,
    MMLKEY_STRING,
    MMLKEY_CONNECTION
};

/* 告警类型 */
typedef enum
{
    TRAP_TYPE_COM = 1,  /* 通信错误 */
    TRAP_TYPE_SOFTWARE, /* 软件错误  */
    TRAP_TYPE_ENV,      /* 环境错误 */
    TRAP_TYPE_QOS,      /* QOS 错误 */
    TRAP_TYPE_EQUIP,    /* 设备错误 */
    TRAP_TYPE_NMS,      /* 网管错误 */
    TRAP_TYPE_PDC,      /* PDC用户信息2011.5.26*/
    TRAP_TYPE_USER,     /* 用户操作，重启等 */
    TRAP_TYPE_MAX
}ET_TRAP_TYPE;


/* 告警等级 */
typedef enum
{
    TRAP_LV_CRITICAL = 1,   /* 紧急告警 */
    TRAP_LV_MAJOR,          /* 主要告警 */
    TRAP_LV_MINOR,          /* 次要告警 */
    TRAP_LV_NORMAL,         /* 普通告警 */
    TRAP_LV_CLEARED,        /* 告警清除 */
    TRAP_LV_PDCUSERINFO,    /*PDC用户信息报告2011.5.26*/
    TRAP_LV_MAX
}ET_TRAP_LEVEL;

/*
TRAP_DEV_EBS = 1,
    TRAP_DEV_ECN,
    TRAP_DEV_EDS,
    TRAP_DEV_PDC,
    TRAP_DEV_MAX
*/

/* 网元类型 */
typedef enum
{
    NE_NULL,
    NE_BS,          /* 1 bsc */
    NE_IMSC,        /* 2 ecn */
    NE_DS,          /* 3 eds */
    NE_NMS,         /* 4 nms*/
    NE_PDC,         /* 5 pdc */
    NE_ISGW,        /* 6 isgw */
    NE_INIGW,       /* 7 initgw */
    NE_SMC,         /* 8 short message center */
    NE_PDT,         /* 9 pdt */
    NE_AUC,         /* 10 authentication center */
    NE_RS,          /* 11 voice record */
    NE_ADGW_CN,     /* 12 ADGW analog digital gatway connet to switch center */
    NE_MPT_BSC,     /* 13 MPT1327 bsc */
    NE_NTP,         /* 14 ntp server */
    NE_CRGW,        /* 15 router */
    NE_DXC,         /* 16 data exchange */
    NE_PSS,         /* 17 pss bsc */
    NE_DSGW,        /* 18 DSGW */
    NE_SWITCH,      /* 19 ethernet switch */
    NE_DAG,         /* 20 eastcom gis system */
    NE_SMG,         /* 21 short message center gateway */
    NE_BSEX,        /* 22 base station control and carrier process board */
    NE_PDTEX,       /* 23 pdt base station control and carrier process board */
	NE_TBBS,        /* 24 tetra bridge base station*/
	NE_PBBS,        /* 25 pdt bridge base station*/
	NE_PSS_MPT,     /* 26 pss MPT */
	NE_SYNC_MPT,    /* 27 sync MPT */
	NE_SYNC_PDT,    /* 28 sync PDT */
    NE_ENB,         /* 29 enb */
    NE_BCC,         /* 30 bcc */
    NE_API,         /* 31 api */
    NE_MEDIA,       /* 32 media */
    NE_RPT,         /* 33 rpt */
    NE_GPS_PARSER,  /* 34 gps parser server*/
    NE_WEB_GIS,     /* 35 web gis server */
    NE_GPS_TRANSFER, /* 36 gps transfer server */
    NE_CAD,         /* 37 cad server */
    NE_SMS_QUERY,   /* 38 sms query */
    NE_WBS,         /* 39 pdt 4 slot bs */
    NE_WBSEX,       /* 40 pdt 4 slot bsex */
    NE_MAX
}ET_DEVTYPE;


/******************************************************************************
function:      SetDevType
description:   set device type, such as NE_BS , NE_IMSC...
arg1:          type,  NE_BS, NE_IMSC,NE_DS,NE_PDC,NE_ISGW, NE_INIGW, NE_SMC
return:        ETOK                  success
               ETERROR               failure
******************************************************************************/
ESTATUS SetDevType(int type);

/******************************************************************************
function:      GetDevType
description:   get device type
return:        device type, such as NE_BS, NE_IMSC,NE_DS,NE_PDC,NE_ISGW, NE_INIGW, NE_SMC
******************************************************************************/
EINT32 GetDevType(void);


/* 告警模块类型 */
typedef enum
{
    TRAP_MODULE_BSC = 1,
    TRAP_MODULE_BSR,
    TRAP_MODULE_RFDS,
    TRAP_MODULE_BSR_TR,
    TRAP_MODULE_BSR_PA,
    TRAP_MODULE_PSM,
    TRAP_MODULE_ACDC,
    TRAP_MODULE_ECN,
    TRAP_MODULE_EDS,
    TRAP_MODULE_PDC,      /* PDC模块 */
    TRAP_MODULE_PDT,      /* dbox pdt */
    TRAP_MODULE_MPTBSC,   /* mpt 1327 */
    TRAP_MODULE_ADGWCN,   /* ADGW */
    TRAP_MODULE_DSGW,     /* DSGW */
    TRAP_MODULE_PSS,      /* PSS */
    TRAP_MODULE_BCCP,     /* BCCP */
    TRAP_MODULE_BBS,      /* BBS */
    TRAP_MODULE_MAX,
}ET_TRAP_MODULETYPE;

/* 告警子模块类型 */
typedef enum
{
    TRAP_SUBMOUDLE_E1 = 1,
    TRAP_SUBMOUDLE_ETHERNET,
    TRAP_SUBMOUDLE_ICP,
}ET_TRAP_SUBMODULETYPE;

typedef struct cli_s
{
    /*MSG_Q_ID      msgID;*/
    char            type;           /* Connection type Telnet or TTY */
    char            active;         /* 1: active 0: non-active */
    char            accessLevel;    /* user level */
    char            debug;          /* debug flag */
    char            waitKeyPut;     /* wait flag */
    char            username[CLI_MAX_USERNAME_LEN];
    int             sid;            /* socket id */
    int             tid;            /* thread id */
    int             unit;
    int             crFlag;
    unsigned int    ipaddr;       /*client IP Address*/
    char            defaultDir[DEF_DIR_LEN+10];
    unsigned char   lastLine[MAX_BYTES_PER_LINE];  /* last command line */
    int             lastLineLen;                    /* number of bytes in lastline */
    unsigned char   recvLine[MAX_BYTES_PER_LINE];  /* current receive line buffer */
    int             pos;                            /* current position in the line */
    int             oldCmdTable[MAXOLDCMDCOUNT*sizeof(int)];    /* the first pointer of history command */
    int             oldCmdCount;                  /* the count of history command*/
    int             oldCmdPos;                      /* the postion of history command */
    unsigned char   oldCmdPool[MAX_OLDCMDPOOL_SIZE];               /* the pool of history command  */
    struct cli_s    *pNext;
    int             watchDebug;
    int             endPos;
    int             backNum;
    #ifdef VXWORKS
    int             tfy, oldStdin, oldStdout, oldStderr;
    int             vxShelIn;
    #endif
	int             rSid;       /* remote server socket id */
    int             rStat;      /* remote server status */
} CLI;


/*-------------------------------------------------------------------------  */
/*    MML命令登记表  */
/*-------------------------------------------------------------------------  */
struct MMLREGISTER_t
{
    ECHAR *Name[3];
    ECHAR  accessLevel;
    EINT32 (*f)(EINT32 handle, CLI * pCli);
};

typedef struct
{
    struct MMLREGISTER_t  MMLRegister[MAX_MML_REG_NUM];    /* 4096 个 MML 命令  */
    int                   MMLRegisterLen;        /* 命令个数  */
} MML;
/*Extern Function*/
/*
MMLInstallCommand: mml 命令注册接口
cmdName: 命令名第一节,必填
fieldName: 命令名第二节,如果没用可置 NULL
subFieldName: 命令名第三节,如果没用可置 NULL
accessLevel: 用户等级
f: 命令实现函数
return: 成功返回 ETOK， 错误返回 ETERROR
*/
extern ESTATUS MMLInstallCommand(
                      ECHAR * cmdName,
                      ECHAR * fieldName,
                      ECHAR * subFieldName,
                      ECHAR accessLevel,
                      EINT32 (*f)(EINT32 handle, CLI * pCli));

/*
DOSInstallCommand: 类 dos 命令注册接口
cmdName: 命令名第，非 NULL
accessLevel: 用户等级
f: 命令实现函数
return: 成功返回 ETOK， 错误返回 ETERROR
*/
extern ESTATUS DOSInstallCommand(
                        const char * cmdName,
                        char  accessLevel,
                        int (*f)(unsigned char z[],
                                int pos[],
                                int value[],
                                int len,
                                CLI * pCli));

extern MML cliMMLReg;

/*Extern Function */
/*
IsSpace: 判断是否为空白字符
c: 被判断字符
return: 如果是“空格符”，或者“制表符” 返回非零值，否则返回 0
*/
extern EINT32 IsSpace(EUCHAR c);

/*
check if a showable char
return: 1:yes 0:no
*/
extern EINT32 IsTerminalChar(EUCHAR c);

/*
IsAlpha: 判断是否为非空白字母字符 ('a'-'z', 'A'-'Z', '_', '?', '@', '#', '$', '*')
c: 被判断字符
return: 如果是返回非零值，否则返回 0
*/
extern EINT32 IsAlpha(EUCHAR c);

/*
IsBinDigit: 判断是否为二进制字符 ('0'-'1')
c: 被判断字符
return: 如果是返回非零值，否则返回 0
*/
extern EINT32 IsBinDigit(EUCHAR c);

/*
IsDecDigit: 判断是否为十进制字符 ('0'-'9')
c: 被判断字符
return: 如果是返回非零值，否则返回 0
*/
extern EINT32 IsDecDigit(EUCHAR c);

/*
IsHexDigit: 判断是否为十六进制字符 ('0'-'9'，'a'-'F', 'A'-'F' )
c: 被判断字符
return: 如果是返回非零值，否则返回 0
*/
extern EINT32 IsHexDigit(EUCHAR c);

/*
IsTermChar: 判断是否为行结尾字符 ('\0', ';')
c: 被判断字符
return: 如果是返回非零值，否则返回 0
*/
extern EINT32 IsTermChar(EUCHAR c);

/*
VerifyIPAddress: 判断是否为有效 IP 字符串
ip: 被判断字符
return: 如果是有效 IP 返回 0，否则非零值
*/
extern EINT32 VerifyIPAddress(ECHAR* ip);

/*
MMLGetParameterByIndex: 获取参数值将参数值的指针放入 Para
handle: 命令句柄，有命令接口函数传入，
pos: 参数位置
Para: 用于保存参数值指针
return: 如果获取成功返回 1，否则返回 0
*/
extern EINT32 MMLGetParameterByIndex(EINT32 handle,EINT32 pos, char * Para[]);

/*
mmlStrupr: 将字符串转换为大写
s: 待转换字符串
return: 返回 0
*/
extern EINT32 mmlStrupr(ECHAR s[]);

/*
mmlAtoi: 将字符串转换成整数
s: 待转换字符串
return: 返回转换后的整数值
*/
extern EINT32 mmlAtoi(ECHAR s[]);

/*
mmlAtof: 将字符串转换成浮点数
str: 待转换字符串
return: 返回转换后的浮点数值
*/
extern double mmlAtof( const ECHAR *str);

/*
mmlItoa: 将整数转换成字符串
value: 待转换字整数
str: 用户存放转换结果的字符数组
radix: 要求转换的进制数 最大值为 34
return: 返回转换完成后的字符串
*/
extern ECHAR *mmlItoa(EINT32 value, ECHAR *str, EINT32 radix);

/*
HighGetContentFromDoubleQuto: 获取引号或者双引号包着字符串
p: 用于存放结果的字符数组
p_len: p 数组长度
s: 原始字符串
s_len: 原始字符串长度
return: 返回获取的字符串长度，出错返回 -1；
*/
extern EINT32 HighGetContentFromDoubleQuto(ECHAR p[],EINT32 p_len, ECHAR s[],EINT32 s_len);

/*
GetIpAddrFromDoubleQuto: 获取 IP 地址字符串
p: 用于存放结果的字符数组
p_len: p 数组长度
s: 原始字符串
s_len: 原始字符串长度
return: 成功返回 ETOK， 错误返回 ETERROR；
*/
extern ESTATUS GetIpAddrFromDoubleQuto(ECHAR p[],EINT32 p_len, ECHAR s[],EINT32 s_len);

/*
GetIpmaskFromDoubleQuto: 获取 IP 掩码字符串
p: 用于存放结果的字符数组
p_len: p 数组长度
s: 原始字符串
s_len: 原始字符串长度
return: 成功返回 ETOK， 错误返回 ETERROR；
*/
extern ESTATUS GetIpmaskFromDoubleQuto(ECHAR p[],EINT32 p_len, ECHAR s[],EINT32 s_len);

/*
GetIpAddrNoErrorCheckFromDoubleQuto: 获取 IP 地址字符串, 与 GetIpAddrFromDoubleQuto 相比
没有过滤掉 127.x.x.x 或者 223.x.x.x 等无效 IP 地址
p: 用于存放结果的字符数组
p_len: p 数组长度
s: 原始字符串
s_len: 原始字符串长度
return: 成功返回 ETOK， 错误返回 ETERROR；
*/
extern ESTATUS GetIpAddrNoErrorCheckFromDoubleQuto(ECHAR p[],EINT32 p_len, ECHAR s[],EINT32 s_len);

/*
MML_resultPrint: 打印参数获取结果
pCli: 命令行结构体
result: 获取参数过程中设置的参数获取结果数值
*/
extern void MML_resultPrint(CLI * pCli, EINT32 result);

/*
mmlPrintf: 格式化字符串输出
pCli: 命令行结构体
format: 格式化串
return: 正确返回 输出字符长度, 错误返回 ETERROR
*/
extern ESTATUS mmlPrintf(CLI * pCli, ECHAR * format,...);

/*
cliDevRecv: 获取用户输入
pCli: 命令行结构体
pBuf: 缓冲区
bufLen: 缓冲区大小
return: 正确返回获取字符串长度, 错误返回 -1
*/
extern int cliDevRecv(CLI * pCli, char * pBuf, int bufLen);

/*
cliGetOneLineFromStream: 获取一行用户输入
pBuf: 缓冲区
bufLen: 缓冲区大小
pCli: 命令结构体
cryptograph: 输入是否为密码
return: 正确返回获取字符串长度, 如果是网络错误返回 -1，输入长度超过 bufLen 返回 -2
*/
extern int cliGetOneLineFromStream(char * pBuf, int bufLen, CLI * pCli, int cryptograph);

/*
cliTaskInit: 命令行模块初始化
prompt: 命令行提示符字符串
return: 正确返回 ETOK, 错误返回 ETERROR
*/
extern ESTATUS cliTaskInit(char *prompt);

/*
DoCmdFile: 执行 CLI 批处理
fileName: 批处理文件名
pCli: CLI 结构指针
return: 返回批处理文件内容行数
*/
extern int DoCmdFile(char *fileName, CLI *pCli);

/* 获取标准输出CLI 结构指针 */
extern CLI * GetStdCli(void);

/* 初始化标准输出CLI 结构 */
extern int stdCliInit(void);
/* 关闭标准输出CLI */
extern void stdCliClose(CLI * pCli);

#if defined(LINUX)||defined(AIX)
/*
coreDumpInit: linux coredump 初始化函数
return: 正确返回 ETOK, 错去返回 ETERROR
*/
ESTATUS coreDumpInit(void);
#endif

#if defined(LINUX)||defined(AIX)||defined(VXWORKS)
/*
getDumpWriteArea: 获取写消息地址指针
addr： 用于存放写消息地址值的指针
return: 正确返回 ETOK, 错去返回 ETERROR
*/
int getDumpWriteArea(unsigned long *addr);

/*
getDumpWriteArea: 获取读消息地址指针
addr： 用于存放读消息地址值的指针
return: 正确返回 ETOK, 错去返回 ETERROR
*/
int getDumpReadArea(unsigned long *addr);
#endif

const char* getDefaultDir(void);
extern void etraReboot(int type);


/* export snmp process result defines */
#undef NO_ERROR
#define NO_ERROR            0
#undef NO_SUCH_NAME
#define    NO_SUCH_NAME        2
#undef GEN_ERR
#define    GEN_ERR             5
#undef COMMIT_FAILED
#define COMMIT_FAILED       14


#define MAX_NMIF_SETGET_MSG_LEN 512

/* dig struct pointer from agentMsg pointer */
#define DIG_AGTMSG_P(ST,P)    ((ST*)(P)->msgBody)
#define DIG_AGTMSG(ST,V)    ((ST*)(V).msgBody)

#define DECLARE_MSG_DATA(type, msg, data)  NMIF_GETSET_MSG msg;    \
                                    type *data;                     \
                                    data = (type*)msg.msgBody;      \
                                    memset((void*)&msg, 0, sizeof(NMIF_GETSET_MSG));    \
                                    msg.bodyLen = sizeof(type);
/*
#define UINT_TEST(struc, name)  (struc)->name= VB_GET_UINT32(vbp);        \
                if (MIN_##name > (struc)->name                    \
                || MAX_##name < (struc)->name)                    \
      {testproc_error(pktp, vbp, GEN_ERR); break;}

#define INT_TEST(struc, name)  (struc)->name= VB_GET_INT32(vbp);        \
                if (MIN_##name > (struc)->name                    \
                || MAX_##name < (struc)->name)                    \
      {testproc_error(pktp, vbp, GEN_ERR); break;}
*/

typedef EULONG (__stdcall * SNMPFUNPTR)(EINT32 opCode, EINT32 optInd, void *pData, EINT32 *result);

typedef EULONG (__stdcall * SNMPFUNPTREXTEND)(EINT32 opCode, EINT32 optInd, EINT32 optInd2, EINT32 optInd3, EINT32 optInd4,void *pData, EINT32 *result);

typedef struct
{
    unsigned short code;    /*消息代理，与具体应用程序相关，不统一编号*/
    unsigned short sequence;    /*消息序列号，匹配消息*/
    union
    {
        unsigned int optInd;    /* opration id */
        int rspInd;             /* response id */
    }indicator; /* GET ; 0:get first row，; 1:get current row，;2:get next row 2，SET：set index*/

    unsigned int optInd2;    /* opration id */
    unsigned int optInd3;    /* opration id */
    unsigned int optInd4;    /* opration id */

    int bodyLen;        /*GET/SET消息体有效长度*/
    unsigned char msgBody[MAX_NMIF_SETGET_MSG_LEN];
}NMIF_GETSET_MSG;

typedef int (*OpcodeHandler)(NMIF_GETSET_MSG*);
typedef struct OpcodeHandTable
{
    int min;
    int max;
    OpcodeHandler *table;
}OPCODE_HANDTABLE;

int DealOpcodeMsg(struct OpcodeHandTable *table, int opCode,
            NMIF_GETSET_MSG *pAgtMsg);

EINT32 regDevTypeIdHandle(EUINT16 (*idGet)(void));

ESTATUS AddSnmpTrapServer(EUINT32 ip, EINT32 port);
ESTATUS DelSnmpTrapServer(EUINT32 ip, EINT32 port);

int RegSnmpHanderTable(int min, int max, OpcodeHandler * table);


void getStrId(char *dst, void* p);
void getIdStr(void* p, char *src, int maxLen);
void getIdStrLen(void* p, char *src, int maxLen);


void SetAgentDebug(int val);
int getAgentDebug(void);
EINT32 agentPubLibInit(void);
EUINT16 SendSnmpReqMsg(int mid, int pid, int fid,
                        NMIF_GETSET_MSG *pAgtMsg);
EINT32 SendSnmpRspMsg(void *pNode); /* MSG_NODE */
EINT32 RegM2Client(EINT32 fid, SNMPFUNPTR f);
EINT32 RegM2EXTENDClient(EINT32 fid, SNMPFUNPTREXTEND f);

int waitSnmpResponse(NMIF_GETSET_MSG *pAgtMsg, EUINT16 seq);

/*
snmpBindSrcIp(GetIpAddr("1.2.3.4"));
*/
ESTATUS snmpBindSrcIp(int ip);
#if defined(WINDOWS)
#define snprintf _snprintf
#endif

#ifdef __cplusplus
}
#endif

#endif /* __oampu_h__ */

