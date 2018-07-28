#ifndef __oampu_h__
#define __oampu_h__



#ifdef __cplusplus
extern "C" {
#endif

#define MSG_SNMP_REQUEST    0
#define MSG_SNMP_TRAP       1
#define MSG_SNMP_RESPONSE   2


/* �������û��ȼ� */
enum
{
    USLEVEL_NULL,
    USLEVEL_GENERAL,        /* ��ͨ�û� */
    USLEVEL_IMPORTANT,      /* ��Ҫ�û� */
    USLEVEL_SUPER,          /* �����û� */
    USLEVEL_DEBUG,          /* DEBUG �û� */
    USLEVEL_MAX             /* Unused */
};

/* �����в�����飬�������� */
enum
{
    NORMAL_PARAMETER,       /* û�� */
    NO_PARAMETER,           /* �޲������� */
    ERROR_PARAMETER,        /* ������� */
    UNKNOWN_PARAMETER,      /* δ֪���� */
    MISS_MAND_PARAMENTER    /* ȱ�ٱ������ */
};

#define MAX_MML_REG_NUM     2048    /* ��� MML ������Ŀ */
#define MAXOLDCMDCOUNT                  20      /* ��ʷ��¼��Ŀ */
#define MAX_BYTES_PER_LINE              256     /* ������һ����������ַ��� */
#define MAX_TOKEN                       6       /**/
#define MAX_SUPPORT_CLI_NUM             12      /* 10 Telnet + 1 TTY + 1 stdout*/
#define STREAMIODEV_SOCKET              1       /* ��¼����Ϊ TELNET */
#define STREAMMSGTYPE_TTY               2       /* ��¼����Ϊ���� */
#define STREAMIODEV_STDOUT              3       /* ��¼����Ϊ��׼��������������� */
#define MAX_OLDCMDPOOL_SIZE             0x800   /* ��¼��ʷ����Ļ�������С */
#define CLI_CONN_TASK_PRIORITY          145     /* �����������������ȼ� */
#define CLI_MAX_USERNAME_LEN            16      /* �û�����󳤶� */
#define CLI_MAX_PASSWORD_LEN            16      /* ������󳤶� */
#define MAX_CLI_USER    32  /* ��ע������û��� */
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

/* �澯���� */
typedef enum
{
    TRAP_TYPE_COM = 1,  /* ͨ�Ŵ��� */
    TRAP_TYPE_SOFTWARE, /* �������  */
    TRAP_TYPE_ENV,      /* �������� */
    TRAP_TYPE_QOS,      /* QOS ���� */
    TRAP_TYPE_EQUIP,    /* �豸���� */
    TRAP_TYPE_NMS,      /* ���ܴ��� */
    TRAP_TYPE_PDC,      /* PDC�û���Ϣ2011.5.26*/
    TRAP_TYPE_USER,     /* �û������������� */
    TRAP_TYPE_MAX
}ET_TRAP_TYPE;


/* �澯�ȼ� */
typedef enum
{
    TRAP_LV_CRITICAL = 1,   /* �����澯 */
    TRAP_LV_MAJOR,          /* ��Ҫ�澯 */
    TRAP_LV_MINOR,          /* ��Ҫ�澯 */
    TRAP_LV_NORMAL,         /* ��ͨ�澯 */
    TRAP_LV_CLEARED,        /* �澯��� */
    TRAP_LV_PDCUSERINFO,    /*PDC�û���Ϣ����2011.5.26*/
    TRAP_LV_MAX
}ET_TRAP_LEVEL;

/*
TRAP_DEV_EBS = 1,
    TRAP_DEV_ECN,
    TRAP_DEV_EDS,
    TRAP_DEV_PDC,
    TRAP_DEV_MAX
*/

/* ��Ԫ���� */
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


/* �澯ģ������ */
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
    TRAP_MODULE_PDC,      /* PDCģ�� */
    TRAP_MODULE_PDT,      /* dbox pdt */
    TRAP_MODULE_MPTBSC,   /* mpt 1327 */
    TRAP_MODULE_ADGWCN,   /* ADGW */
    TRAP_MODULE_DSGW,     /* DSGW */
    TRAP_MODULE_PSS,      /* PSS */
    TRAP_MODULE_BCCP,     /* BCCP */
    TRAP_MODULE_BBS,      /* BBS */
    TRAP_MODULE_MAX,
}ET_TRAP_MODULETYPE;

/* �澯��ģ������ */
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
/*    MML����ǼǱ�  */
/*-------------------------------------------------------------------------  */
struct MMLREGISTER_t
{
    ECHAR *Name[3];
    ECHAR  accessLevel;
    EINT32 (*f)(EINT32 handle, CLI * pCli);
};

typedef struct
{
    struct MMLREGISTER_t  MMLRegister[MAX_MML_REG_NUM];    /* 4096 �� MML ����  */
    int                   MMLRegisterLen;        /* �������  */
} MML;
/*Extern Function*/
/*
MMLInstallCommand: mml ����ע��ӿ�
cmdName: ��������һ��,����
fieldName: �������ڶ���,���û�ÿ��� NULL
subFieldName: ������������,���û�ÿ��� NULL
accessLevel: �û��ȼ�
f: ����ʵ�ֺ���
return: �ɹ����� ETOK�� ���󷵻� ETERROR
*/
extern ESTATUS MMLInstallCommand(
                      ECHAR * cmdName,
                      ECHAR * fieldName,
                      ECHAR * subFieldName,
                      ECHAR accessLevel,
                      EINT32 (*f)(EINT32 handle, CLI * pCli));

/*
DOSInstallCommand: �� dos ����ע��ӿ�
cmdName: �������ڣ��� NULL
accessLevel: �û��ȼ�
f: ����ʵ�ֺ���
return: �ɹ����� ETOK�� ���󷵻� ETERROR
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
IsSpace: �ж��Ƿ�Ϊ�հ��ַ�
c: ���ж��ַ�
return: ����ǡ��ո���������ߡ��Ʊ���� ���ط���ֵ�����򷵻� 0
*/
extern EINT32 IsSpace(EUCHAR c);

/*
check if a showable char
return: 1:yes 0:no
*/
extern EINT32 IsTerminalChar(EUCHAR c);

/*
IsAlpha: �ж��Ƿ�Ϊ�ǿհ���ĸ�ַ� ('a'-'z', 'A'-'Z', '_', '?', '@', '#', '$', '*')
c: ���ж��ַ�
return: ����Ƿ��ط���ֵ�����򷵻� 0
*/
extern EINT32 IsAlpha(EUCHAR c);

/*
IsBinDigit: �ж��Ƿ�Ϊ�������ַ� ('0'-'1')
c: ���ж��ַ�
return: ����Ƿ��ط���ֵ�����򷵻� 0
*/
extern EINT32 IsBinDigit(EUCHAR c);

/*
IsDecDigit: �ж��Ƿ�Ϊʮ�����ַ� ('0'-'9')
c: ���ж��ַ�
return: ����Ƿ��ط���ֵ�����򷵻� 0
*/
extern EINT32 IsDecDigit(EUCHAR c);

/*
IsHexDigit: �ж��Ƿ�Ϊʮ�������ַ� ('0'-'9'��'a'-'F', 'A'-'F' )
c: ���ж��ַ�
return: ����Ƿ��ط���ֵ�����򷵻� 0
*/
extern EINT32 IsHexDigit(EUCHAR c);

/*
IsTermChar: �ж��Ƿ�Ϊ�н�β�ַ� ('\0', ';')
c: ���ж��ַ�
return: ����Ƿ��ط���ֵ�����򷵻� 0
*/
extern EINT32 IsTermChar(EUCHAR c);

/*
VerifyIPAddress: �ж��Ƿ�Ϊ��Ч IP �ַ���
ip: ���ж��ַ�
return: �������Ч IP ���� 0���������ֵ
*/
extern EINT32 VerifyIPAddress(ECHAR* ip);

/*
MMLGetParameterByIndex: ��ȡ����ֵ������ֵ��ָ����� Para
handle: ��������������ӿں������룬
pos: ����λ��
Para: ���ڱ������ֵָ��
return: �����ȡ�ɹ����� 1�����򷵻� 0
*/
extern EINT32 MMLGetParameterByIndex(EINT32 handle,EINT32 pos, char * Para[]);

/*
mmlStrupr: ���ַ���ת��Ϊ��д
s: ��ת���ַ���
return: ���� 0
*/
extern EINT32 mmlStrupr(ECHAR s[]);

/*
mmlAtoi: ���ַ���ת��������
s: ��ת���ַ���
return: ����ת���������ֵ
*/
extern EINT32 mmlAtoi(ECHAR s[]);

/*
mmlAtof: ���ַ���ת���ɸ�����
str: ��ת���ַ���
return: ����ת����ĸ�����ֵ
*/
extern double mmlAtof( const ECHAR *str);

/*
mmlItoa: ������ת�����ַ���
value: ��ת��������
str: �û����ת��������ַ�����
radix: Ҫ��ת���Ľ����� ���ֵΪ 34
return: ����ת����ɺ���ַ���
*/
extern ECHAR *mmlItoa(EINT32 value, ECHAR *str, EINT32 radix);

/*
HighGetContentFromDoubleQuto: ��ȡ���Ż���˫���Ű����ַ���
p: ���ڴ�Ž�����ַ�����
p_len: p ���鳤��
s: ԭʼ�ַ���
s_len: ԭʼ�ַ�������
return: ���ػ�ȡ���ַ������ȣ������� -1��
*/
extern EINT32 HighGetContentFromDoubleQuto(ECHAR p[],EINT32 p_len, ECHAR s[],EINT32 s_len);

/*
GetIpAddrFromDoubleQuto: ��ȡ IP ��ַ�ַ���
p: ���ڴ�Ž�����ַ�����
p_len: p ���鳤��
s: ԭʼ�ַ���
s_len: ԭʼ�ַ�������
return: �ɹ����� ETOK�� ���󷵻� ETERROR��
*/
extern ESTATUS GetIpAddrFromDoubleQuto(ECHAR p[],EINT32 p_len, ECHAR s[],EINT32 s_len);

/*
GetIpmaskFromDoubleQuto: ��ȡ IP �����ַ���
p: ���ڴ�Ž�����ַ�����
p_len: p ���鳤��
s: ԭʼ�ַ���
s_len: ԭʼ�ַ�������
return: �ɹ����� ETOK�� ���󷵻� ETERROR��
*/
extern ESTATUS GetIpmaskFromDoubleQuto(ECHAR p[],EINT32 p_len, ECHAR s[],EINT32 s_len);

/*
GetIpAddrNoErrorCheckFromDoubleQuto: ��ȡ IP ��ַ�ַ���, �� GetIpAddrFromDoubleQuto ���
û�й��˵� 127.x.x.x ���� 223.x.x.x ����Ч IP ��ַ
p: ���ڴ�Ž�����ַ�����
p_len: p ���鳤��
s: ԭʼ�ַ���
s_len: ԭʼ�ַ�������
return: �ɹ����� ETOK�� ���󷵻� ETERROR��
*/
extern ESTATUS GetIpAddrNoErrorCheckFromDoubleQuto(ECHAR p[],EINT32 p_len, ECHAR s[],EINT32 s_len);

/*
MML_resultPrint: ��ӡ������ȡ���
pCli: �����нṹ��
result: ��ȡ�������������õĲ�����ȡ�����ֵ
*/
extern void MML_resultPrint(CLI * pCli, EINT32 result);

/*
mmlPrintf: ��ʽ���ַ������
pCli: �����нṹ��
format: ��ʽ����
return: ��ȷ���� ����ַ�����, ���󷵻� ETERROR
*/
extern ESTATUS mmlPrintf(CLI * pCli, ECHAR * format,...);

/*
cliDevRecv: ��ȡ�û�����
pCli: �����нṹ��
pBuf: ������
bufLen: ��������С
return: ��ȷ���ػ�ȡ�ַ�������, ���󷵻� -1
*/
extern int cliDevRecv(CLI * pCli, char * pBuf, int bufLen);

/*
cliGetOneLineFromStream: ��ȡһ���û�����
pBuf: ������
bufLen: ��������С
pCli: ����ṹ��
cryptograph: �����Ƿ�Ϊ����
return: ��ȷ���ػ�ȡ�ַ�������, �����������󷵻� -1�����볤�ȳ��� bufLen ���� -2
*/
extern int cliGetOneLineFromStream(char * pBuf, int bufLen, CLI * pCli, int cryptograph);

/*
cliTaskInit: ������ģ���ʼ��
prompt: ��������ʾ���ַ���
return: ��ȷ���� ETOK, ���󷵻� ETERROR
*/
extern ESTATUS cliTaskInit(char *prompt);

/*
DoCmdFile: ִ�� CLI ������
fileName: �������ļ���
pCli: CLI �ṹָ��
return: �����������ļ���������
*/
extern int DoCmdFile(char *fileName, CLI *pCli);

/* ��ȡ��׼���CLI �ṹָ�� */
extern CLI * GetStdCli(void);

/* ��ʼ����׼���CLI �ṹ */
extern int stdCliInit(void);
/* �رձ�׼���CLI */
extern void stdCliClose(CLI * pCli);

#if defined(LINUX)||defined(AIX)
/*
coreDumpInit: linux coredump ��ʼ������
return: ��ȷ���� ETOK, ��ȥ���� ETERROR
*/
ESTATUS coreDumpInit(void);
#endif

#if defined(LINUX)||defined(AIX)||defined(VXWORKS)
/*
getDumpWriteArea: ��ȡд��Ϣ��ַָ��
addr�� ���ڴ��д��Ϣ��ֵַ��ָ��
return: ��ȷ���� ETOK, ��ȥ���� ETERROR
*/
int getDumpWriteArea(unsigned long *addr);

/*
getDumpWriteArea: ��ȡ����Ϣ��ַָ��
addr�� ���ڴ�Ŷ���Ϣ��ֵַ��ָ��
return: ��ȷ���� ETOK, ��ȥ���� ETERROR
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
    unsigned short code;    /*��Ϣ���������Ӧ�ó�����أ���ͳһ���*/
    unsigned short sequence;    /*��Ϣ���кţ�ƥ����Ϣ*/
    union
    {
        unsigned int optInd;    /* opration id */
        int rspInd;             /* response id */
    }indicator; /* GET ; 0:get first row��; 1:get current row��;2:get next row 2��SET��set index*/

    unsigned int optInd2;    /* opration id */
    unsigned int optInd3;    /* opration id */
    unsigned int optInd4;    /* opration id */

    int bodyLen;        /*GET/SET��Ϣ����Ч����*/
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

