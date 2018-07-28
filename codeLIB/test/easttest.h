/************************************************************************
Copyright (C), 2018-2020, Eastcom.All Rights Reserved.
File name��     easttest.h
Author��        wuh
Date�� 		    2018-06-19
Description��

Others��        None
History:
2018-06-19 wuh Created
*************************************************************************/
#ifndef _EASTCOM_TEST_H_
#define _EASTCOM_TEST_H_
#include "sys.h"
#include "stdio.h"

// �ּ����
#define MMI_MAPPING_LEVEL_F_C      	(0x39)    //'9'
#define MMI_MAPPING_LEVEL_CONST 	 (0x100000)
#define MMI_MAPPING_GBI90			(7001)
#define MMI_MAPPING_GBI95           (12001)
#define MMI_MAPPING_GBI97			(14001)
#define MMI_MAPPING_GBI98			(15001)
#define MMI_MAPPING_GBI99			(16001)

//�ζӽṹ TEAM   8 5 3
typedef enum
{
    MMI_ADDR_TEAM_L_IN_BEGIN=5,
    MMI_ADDR_TEAM_L_IN_END=7,
    MMI_ADDR_TEAM_L_FIN_BEGIN=3,
    MMI_ADDR_TEAM_L_FIN_END=4,
    MMI_ADDR_TEAM_L_NP_BEGIN=0,
    MMI_ADDR_TEAM_L_NP_END=2
  //  MMI_ADDR_TEAM_L_MAX=8
}mmi_addr_team_l_enum;//location

typedef enum
{
    MMI_ADDR_TEAM_L_0=0,
    MMI_ADDR_TEAM_L_1,
    MMI_ADDR_TEAM_L_2,
    MMI_ADDR_TEAM_L_3,
    MMI_ADDR_TEAM_L_4,
    MMI_ADDR_TEAM_L_5,
    MMI_ADDR_TEAM_L_6,
    MMI_ADDR_TEAM_L_7,
    MMI_ADDR_TEAM_L_8,
    MMI_ADDR_TEAM_L_MAX
}mmi_addr_l_enum;
typedef enum
{
    MMI_ADDR_TEAM_LEN_3=3,
    MMI_ADDR_TEAM_LEN_5=5,
    MMI_ADDR_TEAM_LEN_6=6,
    MMI_ADDR_TEAM_LEN_8=8,
    MMI_ADDR_TEAM_LEN_MAX=9
}mmi_addr_team_len_enum;//location

typedef enum
{
    MMI_ADDR_FIN_1=0,//    1  ��
    MMI_ADDR_FIN_2=1,//    2  ��
    MMI_ADDR_FIN_MAX
}mmi_addr_fin_type_enum;//location
// �ּ����
typedef enum
{
	MMI_ADDR_9_L_FC=0,//first ECHAR
	MMI_ADDR_9_L_FLAG=1,
	MMI_ADDR_9_L_V_BEGIN=2,
	MMI_ADDR_9_L_V_END=4
}mmi_addr_9_level_offset_enum;

typedef enum
{
	MMI_ADDR_9_L_0=0,
	MMI_ADDR_9_L_1=1,
	MMI_ADDR_9_L_2=2,
	MMI_ADDR_9_L_3=3,
	MMI_ADDR_9_L_4=4,
	MMI_ADDR_9_L_5=5,
	MMI_ADDR_9_L_6=6,
	MMI_ADDR_9_L_7=7,
	MMI_ADDR_9_L_8=8,
	MMI_ADDR_9_L_9=9,
	MMI_ADDR_9_L_10=10
}mmi_addr_9_level_flag_enum;

typedef struct
{
    EUINT32  uicurNP;
    EUINT32  uipNP;//ʡNP
}NP_TABLE_t;

/***********new head************/
#define ADDRESS_NOTMATCH -2
#define ADDR_NUMBER_BASE_1 0x100001//������һ�Ӳ���
#define ADDR_NUMBER_BASE_2 0x103C29//��������Ӳ���
#define ADDR_J_ASCII 0x23//#
#define ADDR_X_ASCII 0X2a//*

/*******NP*******/
#define ADDR_NP_BASE 296
#define ADDR_NP_OFFSET 15
#define ADDR_NP_MIN 328
#define ADDR_NP_MAX 806
#define ADDR_NP_MPT_MIN 200
#define ADDR_NP_MPT_MAX 327
/*******NAI*******/
#define ADDR_NP_PDT_ZJP_MIN_1 274
#define ADDR_NP_PDT_ZJP_MAX_1 285
#define ADDR_NP_PDT_ZJP_POLICE 804
#define ADDR_NAI_PDT_ZJP_MIN_1 570
#define ADDR_NAI_PDT_ZJP_MAX_1 581
#define ADDR_NAI_PDT_ZJP_MIN_2 800
#define ADDR_NAI_PDT_ZJP_MAX_2 803
#define ADDR_NAI_PDT_ZJP_POLICE 476
#define ADDR_NAI_PDT_MIN 32
#define ADDR_NAI_PDT_MAX 511
#define ADDR_NAI_MPT_MIN 0
#define ADDR_NAI_MPT_MAX 31

/*******SSI*******/
#define ADDR_SSI_IND_1_MIN 1
#define ADDR_SSI_IND_1_MAX 15400
#define ADDR_SSI_IND_2_MIN 15401
#define ADDR_SSI_IND_2_MAX 32200
#define ADDR_SSI_DCN_MIN 32481
#define ADDR_SSI_DCN_MAX 32490
#define ADDR_SSI_SSN_MIN 32491
#define ADDR_SSI_SSN_MAX 32510
#define ADDR_SSI_INT_MIN 32652/*�ڲ�����*/
#define ADDR_SSI_INT_MAX 32751

#define ADDR_LOW15BIT_MAX 0x7FFF
/*******SGI*******/
#define ADDR_SGI_GRP_MIN 1
#define ADDR_SGI_GRP_MAX 7000
#define ADDR_SGI_LVL_GRP_MIN 7001
#define ADDR_SGI_LVL_GRP_MAX 17000


/*
 *�㽭ʡ�g�����뷶Χin
 */
#define  ADDR_NUM_IND_ZJP_MIN_1  1
#define  ADDR_NUM_IND_ZJP_MAX_1  29999
#define  ADDR_NUM_IND_ZJP_SCHEDULE 30000
#define  ADDR_NUM_IND_ZJP_MIN_2  30001
#define  ADDR_NUM_IND_ZJP_MAX_2  30019
#define  ADDR_NUM_IND_ZJP_MIN_3  30020
#define  ADDR_NUM_IND_ZJP_MAX_3  32200
#define  ADDR_NUM_IND_ZJP_MIN_4  32201
#define  ADDR_NUM_IND_ZJP_MAX_4  32767
/*******���뷶Χ��in��*******/
//IND
#define ADDR_NUM_IND_1_MIN 200
#define ADDR_NUM_IND_1_MAX 899
#define ADDR_NUM_IND_2_MIN 200
#define ADDR_NUM_IND_2_MAX 549
//GRP
#define ADDR_NUM_GRP_MIN 900
#define ADDR_NUM_GRP_MAX 999
//DCN
#define ADDR_NUM_DCN_MIN 100
#define ADDR_NUM_DCN_MAX 109
//SSN
#define ADDR_NUM_SSN_MIN 110
#define ADDR_NUM_SSN_MAX 129

//INTERNAL CABLE
#define ADDR_NUM_INT_MIN 9600
#define ADDR_NUM_INT_MAX 9699

//PABX
#define ADDR_NUM_PABX_MIN 1000
#define ADDR_NUM_PABX_MAX 8999

/*******�ζԷ�Χ��fin��*******/
//IND
#define ADDR_FORMAT_IND_1_MIN 20
#define ADDR_FORMAT_IND_1_MAX 41
#define ADDR_FORMAT_IND_2_MIN 42
#define ADDR_FORMAT_IND_2_MAX 89

//GRP
#define ADDR_FORMAT_GRP_MIN 20
#define ADDR_FORMAT_GRP_MAX 89

/*******�ּ����*******/
#define ADDR_9_ASCII 0x39   //'9'

/*******���г���*************/
#define ADDR_TEAM1_LEN	700
#define ADDR_TEAM2_LEN	350
#define ADDR_ZJ_FGN_LEN	100


//PSTN Flag

/*ȫ���궨�忪ʼ*/
#define ADDR_ALL_NUMBER_1_MIN 1911
#define ADDR_ALL_NUMBER_1_MAX 1917
#define ADDR_ALL_NUMBER_2_MIN 1921
#define ADDR_ALL_NUMBER_2_MAX 1927
#define ADDR_ALL_NUMBER_3_MIN 1931
#define ADDR_ALL_NUMBER_3_MAX 1937
#define ADDR_ALL_NUMBER_4_MIN 1941
#define ADDR_ALL_NUMBER_4_MAX 1947
#define ADDR_ALL_NUMBER_5_MIN 1951
#define ADDR_ALL_NUMBER_5_MAX 1957
#define ADDR_ALL_NUMBER_6_MIN 1961
#define ADDR_ALL_NUMBER_6_MAX 1967
#define ADDR_ALL_NUMBER_7_MIN 1971
#define ADDR_ALL_NUMBER_7_MAX 1977
#define ADDR_ALL_NUMBER_8_MIN 1981
#define ADDR_ALL_NUMBER_8_MAX 1987

#define ADDR_ALL_ID_4 0xFFFFFB
#define ADDR_ALL_ID_5 0xFFFFFC
#define ADDR_ALL_ID_6 0xFFFFFD
#define ADDR_ALL_ID_7 0xFFFFFE
#define ADDR_ALL_ID_8 0xFFFFFF

#define ADDR_ALL_ID_123_BASE1 (0x107FFF)
#define ADDR_ALL_ID_123_BASE2 (0x107FFE)
#define ADDR_ALL_ID_123_NP_BASE (328)
#define ADDR_ALL_DYN_NUMBER_MASK1 (0x7FFF)
#define ADDR_ALL_DYN_NUMBER_MASK2 (0x7FFE)
#define ADDR_ALL_DYN_NUMBER_FORWARD_MIN (32)
#define ADDR_ALL_DYN_NUMBER_FORWARD_MAX (510)
/*ȫ���궨�����*/

#define SK_PSTN_INV_SRV 11         //PSTN����
#define SK_PSTN_GRP_SRV 12         //PSTN���

#define ADDR_MPT_IND_2_BASE 354
#define ADDR_MPT_GRP_2_BASE 51

#define ADDR_MPT_IND_3_BASE 236
#define ADDR_MPT_GRP_3_BASE 34

#define ADDR_MPT_IND_4_BASE 118
#define ADDR_MPT_GRP_4_BASE 17

#define ADDR_MPT_IND_MIN 200
#define ADDR_MPT_IND_MAX 899
#define ADDR_MPT_GRP_MIN 900
#define ADDR_MPT_GRP_MAX 999
#define ADDR_MPT_CPSX_MIN 900
#define ADDR_MPT_CPSX_MAX 909
#define ADDR_MPT_OFFSET 13

#define ADDR_MPT_LOW13BIT_MAX 0x1FFF

#define ADDR_MPT1327_SSI_MAX 8100
#define ADDR_MPT1327_BLOCK_NUM_LEN 810

#define ADDR_MPT_DCN_MIN 8170
#define ADDR_MPT_DCN_MAX 8180


#define ADDR_MPT1327_TEAM1_FIN_MIN 20
#define ADDR_MPT1327_TEAM1_SFIN_MIN 21/*��վ�Ӻ�*/
#define ADDR_MPT1327_TEAM234_FIN_MIN 20
#define ADDR_MPT_TEAM_B_MAX 10


  /*
   *mpt1343�����
   */
#define MPT1343_QUEUE_SMIN  (2001)
#define MPT1343_QUEUE_SMAX  (5499)
#define MPT1343_QUEUE_GMIN  (5500)
#define MPT1343_QUEUE_GMAX  (6050)
#define MPT1343_BIG_SBASE   (200)
#define MPT1343_BIG_GBASE   (900)
#define MPT1343_LITTLE_SBASE (20)
#define MPT1343_LITTLE_GBASE (90)
#define MPT1343_BIG_SLEN    (700)
#define MPT1343_BIG_GLEN    (100)
#define MPT1343_LITTLE_SLEN (70)
#define MPT1343_LITTLE_GLEN (10)


/*�û������Ӧ���ȵ�ȡֵ��Χ*/
#define MIN_LEN2_VALUE 10
#define MAX_LEN2_VALUE 99
#define MIN_LEN3_VALUE 100
#define MAX_LEN3_VALUE 999
#define MIN_LEN4_VALUE 1000
#define MAX_LEN4_VALUE 9999
#define MIN_LEN5_VALUE 10000
#define MAX_LEN5_VALUE 99999
#define MIN_LEN6_VALUE 100000
#define MAX_LEN6_VALUE 999999
#define MIN_LEN7_VALUE 1000000
#define MAX_LEN7_VALUE 9999999
#define MIN_LEN8_VALUE 10000000
#define MAX_LEN8_VALUE 99999999
#define MIN_LEN9_VALUE 100000000
#define MAX_LEN9_VALUE 999999999
#define MIN_LEN10_VALUE 1000000000
#define MAX_LEN10_VALUE 3279999999UL/*������ʾ��Ҫ����32λ����ʾֵ��ģ���������Ϊ327*/

#define MAX_ADDR 32
#define ADDR_NP_PDT_POLICE 804

#define MAX_NUM_MPT1343_TEAM 100

#define ADDR_MPT_NP_MIN 200
#define ADDR_MPT_NP_MAX 327
#define ADDR_MPT_TEAM_ROW_MAX 4

#define ADDR_MPT_PFIX_MAX 127/*�������ʶ����*/

#define _EXTERNAL_NUM_MAX 31/* �ⲿ�������λ��       */

#define MAX_PSTN_BCD_LEN 16

#define ADD_AIR_HEADER 4000000000UL/*�տں����40�ڱ�ʶ*/

#define MAX_24_SSI_VALUE 16777215/*24λ�տں������ֵ*/
#define MAX_20_SSI_VALUE 1048575/*20λ�տں������ֵ*/

typedef enum
{
    MMI_ADDR_TEAM_TYPE_GRP=0,//��
    MMI_ADDR_TEAM_TYPE_IND,//��
    MMI_ADDR_TEAM_TYPE_DCN,//dispatch console����̨����
    MMI_ADDR_TEAM_TYPE_SSN,//special service number �ط�̨����
    MMI_ADDR_TEAM_TYPE_LVL_GRP, //�ּ����
    MMI_ADDR_TEAM_TYPE_INT,     //�ڲ�����
    MMI_ADDR_TEAM_TYPE_PABX,    //PABX
    MMI_ADDR_TEAM_TYPE_ERR
}mmi_addr_team_type_enum;//location

//�û����볤��
typedef enum
{
    ADDR_LEN_0=0,
    ADDR_LEN_1=1,
    ADDR_LEN_2=2,
    ADDR_LEN_3=3,
    ADDR_LEN_4=4,
    ADDR_LEN_5=5,
    ADDR_LEN_6=6,
    ADDR_LEN_7=7,
    ADDR_LEN_8=8,
    ADDR_LEN_9=9,
    ADDR_LEN_10=10,
    ADDR_LEN_17=17,
    ADDR_LEN_18=18,
    ADDR_LEN_32 = 32,
    ADDR_LEN_MAX
}ADDR_NUMBER_LEN_e;

//�û����볤��
typedef enum
{
    BEGIN_LEN_0=0,
    BEGIN_LEN_1=1,
    BEGIN_LEN_2=2,
    BEGIN_LEN_3=3,
    BEGIN_LEN_4=4,
    BEGIN_LEN_5=5,
    BEGIN_LEN_6=6,
    BEGIN_LEN_7=7
}BEGIN_LEN_e;

typedef enum
{
    ZJ_PDT_DIALING_RULE = 0,
    STANDARD_PDT_DIALING_RULE,
    INGORE_PDT_DIALING_RULE
}PDT_DIALING_RULE_e;

typedef struct
{
    EUINT32 uibegin_f;
    EUINT32 uiend_f;
}ADDR_MPT_TEAM_T;

typedef enum
{
    PDT_MODE = 0,
    MPT_MODE
}Mode_e;

typedef enum
{
    PDT_TMO = 0,
    PDT_DMO = 2,
    MPT_TMO,
    MPT_DMO
}workMode_e;

typedef struct
{
  EUINT32 uiQueue;
  EUINT32 uiBaseAddr;
  EUINT32 uiStartAddr;
  EUINT32 uiLenofQueue;
  EUINT32 uiCallType;
}MPT1343_PLANNING_t;

/*MPT�ζӽṹ���ļ�*/
typedef enum
{
    TEAM_MPT_1 = 1,
    TEAM_MPT_2,
    TEAM_MPT_3,
    TEAM_MPT_4
}ADDR_MPT_B_E;

typedef enum
{
    SMALL_TEAM,
    BIG_TEAM
}TEAM_TYPE_e;

typedef enum
{
    MPT1327_DIALING_RULE = 0,
    MPT1343_DIALING_RULE
}MPT_DIALING_RULE_e;

EUINT32 SearchMpt1327Fin(EUINT32 uifin);

typedef enum
{
    CALL_INV = 0,/*����*/
    CALL_GROUP,/*���*/
    CALL_PSTN_INV,/*����PSTN*/
    CALL_PSTN_GROUP,/*���PSTN*/
    CALL_BROADCAST,/*�㲥����*/
    CALL_PABX_INV,/*����PABX*/
    CALL_PABX_GROUP/*���PABX*/
}callType_e;

typedef enum
{
    NORMAL_CALL = 0,/*��ͨ����*/
    PRIORITY_CALL = 2,/*���Ⱥ���*/
    EMERGENCY_CALL = 4/*��������*/
}callPriority_e;

typedef enum
{
    DS_NUMBER0 = 100,
    DS_NUMBER1 = 111,
    DS_NUMBER2 = 121,
    DS_NUMBER3 = 131,
    DS_NUMBER4 = 141,
    DS_NUMBER5 = 151,
    DS_NUMBER6 = 161,
    DS_NUMBER7 = 171,
    DS_NUMBER8 = 181,
    DS_NUMBER9 = 191,
    DS_NUMBER10 = 112
}DisPatchnumber_e;

typedef enum
{
    DS_ID0 = 8170,
    DS_ID1 = 8171,
    DS_ID2 = 8172,
    DS_ID3 = 8173,
    DS_ID4 = 8174,
    DS_ID5 = 8175,
    DS_ID6 = 8176,
    DS_ID7 = 8177,
    DS_ID8 = 8178,
    DS_ID9 = 8179,
    DS_ID10 = 8180
}DisPatchId_e;


#define MAX_LOCAL_ECN_NUM      32 //��1��󳤶�,bpsʵ��
#define MAX_LOCAL_PREFIX_NUM     64 //��2-1��󳤶�
#define MAX_LOCAL_GRPPREFIX_NUM  32 //��2-2��󳤶�
#define MAX_REMOTE_PREFIX_NUM    64 //��3��󳤶�
#define MAX_REMOTE_ECN_NUM       64 //��4��󳤶�
#define MAX_ADJ_PDC_NUM          64 //��5��󳤶�

typedef enum PREFIX_TableType
{
    TYPE_LOCAL_MS = 0,
    TYPE_LOCAL_GRP = 1,
    TYPE_REMOTE_MS = 2,
    PREFIX_TYPE_MAX
}PREFIX_TableType_e;

typedef enum TableType
{
    TBL_LOCAL_MSPREFIX = 0,
    TBL_LOCAL_GRPPREFIX = 1,
    TBL_REMOTE_MSPREFIX = 2,
    TBL_PREFIX_MAX ,
    TBL_REMOTE_ECN = 4,
    TBL_ADJ_PDC    = 5,
    TBL_MAX
}TableType_e;



typedef enum PREFIX_TableUseMode
{
    ADD = 0,
    UPDATE = 1,
    DEL = 2,
    PREFIX_USEMODE_MAX
}PREFIX_Table_UseMode_e;


/* bps���ñ�2��һ����¼ */
typedef struct
{
	EINT8   strDialPrefix[16];
	EUINT32 uiFirstEcnid;
	EUINT32 uiSecondEcnid;
}CFG_PDC_LOCAL_MS_T,CFG_PDC_LOCAL_GRP_T;

/* bps���ñ�3��һ����¼ */
typedef struct
{
	EINT8   strDialPrefix[16];
	EUINT32 uiPdcIP;
}CFG_PDC_REMOTE_MS_T;

/* bps���ñ�4��һ����¼ */
typedef struct
{
	EUINT32	uiEcnid ;
	EUINT32 uiPdcip;
}CFG_PDC_REMOTE_ECN_T;

/* bps���ñ�5��һ����¼ */
typedef struct
{
	EUINT32 uiPeerIp;
}CFG_PDC_ADJ_PDC_T;

//���ر�2��һ����¼
typedef struct
{
	NODE 	pTable2Node;
	CFG_PDC_LOCAL_MS_T tCfgInfo;
	CFG_PDC_LOCAL_MS_T *ptCfgInfo;
	EUINT8  unMsType;
	EUINT32  uiPos;//���ñ��е�λ��
}LOCAL_MS_INFO_NODE_t,LOCAL_GRP_INFO_NODE_t;

//���ر�3��һ����¼
typedef struct
{
	NODE 	pTable3Node;
	CFG_PDC_REMOTE_MS_T tCfgInfo;
	EUINT8  unMsType;
	EUINT32  uiPos; //���ñ��е�λ��
}REMOTE_MS_INFO_NODE_t;

//���ر�4��һ����¼
typedef struct
{
    NODE 	pTable4Node;
	CFG_PDC_REMOTE_ECN_T tCfgInfo;
	EUINT16 usCfgPos; //���ñ��е�λ��
}REMOTE_ECN_INFO_NODE_t;


//���ر�5��һ����¼
typedef struct
{
    NODE    pTable5Node;
	CFG_PDC_ADJ_PDC_T  tCfgInfo;
	EUINT16 usCfgPos;  //���ñ��е�λ��
	EULONG ICPChannelId;
    EINT32 ICPState;
}ADJ_PDC_INFO_NODE_t;

typedef struct
{
    EBOOL  initFlag;
    EUINT32 totalByte;
    ECHAR   *pMem;
	ETSEM_ID prefixSem;//wuh add
	LIST    freePrefixMemPool[PREFIX_TYPE_MAX];//wuh add
	void   *pPrefixMemPoolHead[PREFIX_TYPE_MAX];
}PREFIX_TBL_CTRL;

typedef struct
{
    CFG_PDC_LOCAL_MS_T   atLocalMs[MAX_LOCAL_PREFIX_NUM];
    CFG_PDC_LOCAL_GRP_T  atLocalGRP[MAX_LOCAL_GRPPREFIX_NUM];
    CFG_PDC_REMOTE_MS_T  atRemoteMs[MAX_REMOTE_PREFIX_NUM];
    CFG_PDC_REMOTE_ECN_T atRemoteEcn[MAX_REMOTE_ECN_NUM];
    CFG_PDC_ADJ_PDC_T    atAdjPdc[MAX_ADJ_PDC_NUM];
}CFG_TBL_INFO_T;
typedef struct
{
    CFG_PDC_LOCAL_MS_T   *patLocalMs[MAX_LOCAL_PREFIX_NUM];
    CFG_PDC_LOCAL_GRP_T  *patLocalGRP[MAX_LOCAL_GRPPREFIX_NUM];
    CFG_PDC_REMOTE_MS_T  *patRemoteMs[MAX_REMOTE_PREFIX_NUM];
    CFG_PDC_REMOTE_ECN_T *patRemoteEcn[MAX_REMOTE_ECN_NUM];
    CFG_PDC_ADJ_PDC_T    *patAdjPdc[MAX_ADJ_PDC_NUM];
}PCFG_TBL_INFO_T;


void testIDConvert();

#endif  //__ADDR_MAPPING_H__



