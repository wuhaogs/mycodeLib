/******************************************************************************
Copyright(C),2009-, Eastcom
Author:
Date:
Description:
Others:
******************************************************************************/

#ifndef __ETRA_CTRLBSC_H__
#define __ETRA_CTRLBSC_H__

#ifdef __cplusplus
extern "C" {
#endif

/*************RDT*********/




//文件状态
typedef enum en_file_state
{
    NOT_USED_FILE_STATE = 0,
    FILE_NORMAL,
    FILE_INEXIST,
    FILE_ERROR,
    MAX_FILE_STATE
}FILE_STATE_EN;

//文件同步状态
#define FILE_SYN_STATE_COMPLETE 1
#define FILE_SYN_STATE_NOT_COMPLETE 0
#define FILE_SYN_STATE_RUNNINTG 2
#define RDT_FILE_UPDATE 1000
extern EINT32 InitRdt(void);
extern int SetRdtFileSynStateByFileId(int fileId,int fileSynState);

extern int SetRdtFileStateByFileId(int fileId,int fileState);
extern int GetFileIdByFileName(char *filename);
extern ESTATUS AddEnvDev(EINT32 id,ECHAR *pDevName, EUINT32 addr);
/*RDT_MOD不定义启动直接为单主板不启动rdt任务，定义会启动rdt任务*/
#define RDT_MOD
void SendFileUpdateToRdt(EUCHAR selfFid,EUINT16 selfPid,EUINT16 code,EUCHAR fileId);
/*************RDT END*********/

/*Image Management Function*/
extern EINT32 IMGMGR_UpdateImage(char *pFileName, int imageType);
extern ESTATUS InitIMGMGR(void);

/*System Control Function*/
/*Internal IP address and Network Mask*/
/*Return IP Address, string*/
extern ECHAR* GetCfgIntraIpAddr(void);

/*Return IP Address, Intege, Big Endian*/
extern EUINT32 GetCfgIntraIpAddrINT(void);

extern ESTATUS SetCfgIntraIpAddr(ECHAR *p);

extern ECHAR* GetCfgIntraIpMask(void);

extern ESTATUS SetCfgIntraIpMask(ECHAR *p);

/*Internet IP address and Network Mask for OAM*/
/*Return IP Address, string*/
extern ECHAR* GetCfgInterOAMIpAddr(void);

/*Return IP Address, Intege, Big Endian*/
extern EUINT32 GetCfgInterOAMIpAddrINT(void);

extern ESTATUS SetCfgInterOAMIpAddr(ECHAR *p);

extern ECHAR* GetCfgInterOAMIpMask(void);

extern ESTATUS SetCfgInterOAMIpMask(ECHAR *p);

/*Internet IP address and Network Mask for Data*/
/*Return IP Address, string*/
extern ECHAR* GetCfgInterDataIpAddr(void);

/*Return IP Address, Intege, Big Endian*/
extern EUINT32 GetCfgInterDataIpAddrINT(void);

extern ESTATUS SetCfgInterDataIpAddr(ECHAR *p);

extern ECHAR* GetCfgInterDataIpMask(void);

extern ESTATUS SetCfgInterDataIpMask(ECHAR *p);

/*Internet IP address and Network Mask for ECN*/
/*Return IP Address, string*/
extern ECHAR* GetCfgInterECNIpAddr(void);

/*Return IP Address, Intege, Big Endian*/
extern EUINT32 GetCfgInterECNIpAddrINT(void);

extern ESTATUS SetCfgInterECNIpAddr(ECHAR *p);

extern ECHAR* GetCfgInterECNIpMask(void);

extern ESTATUS SetCfgInterECNIpMask(ECHAR *p);


/*dsgw ip*/
extern ECHAR* GetCfgDsgwIp(void);
extern ESTATUS SetCfgDsgwIp(ECHAR *p);


/*Redundant IP address and Network mask*/
extern ECHAR* GetCfgRDTSelfIpAddr(void);
extern EUINT32 GetCfgRDTSelfIpAddrINT(void);

extern ESTATUS SetCfgRDTSelfIpAddr(ECHAR *p);

extern ECHAR* GetCfgRDTSelfIpMask(void);

extern ESTATUS SetCfgRDTSelfIpMask(ECHAR *p);

extern ECHAR* GetCfgRDTPeerIpAddr(void);

extern ESTATUS SetCfgRDTPeerIpAddr(ECHAR *p);
    
/*Gateway Address*/
extern ECHAR* GetCfgGateway(void);

extern ESTATUS SetCfgGateway(ECHAR *p);

/*Primary ECN IP Address*/
/*Return IP Address, string*/
extern ECHAR* GetCfgPrimECNAddr(void);

/*Return IP Address, Intege, Big Endian*/
extern EUINT32 GetCfgPrimECNAddrINT(void);

extern ESTATUS SetCfgPrimECNAddr(ECHAR *p);

/*the pdc prim ip cfg*/
extern ECHAR* GetCfgPrimPDCAddr(void);

extern EUINT32 GetCfgPrimPDCAddrInt();

extern ESTATUS SetCfgPrimPDCAddr(ECHAR *p);
/*the pdc Second ip cfg*/
extern ECHAR* GetCfgSecondPDCAddr(void);

extern EUINT32 GetCfgSecondPDCAddrInt();

extern ESTATUS SetCfgSecondPDCAddr(ECHAR *p);
//extern EUINT16 GetCpBoardId(void);
extern EUCHAR GetBsrMid();


#if defined (LIB_PDT) || defined (LIB_PSS)
ESTATUS SetCfgDboxEnable(EINT32 v);
EINT32 GetCfgDboxEnable(void);
ESTATUS GetCfgPdtDboxIpTable(ECHAR *str, FILE *fd, EUINT32 *pChecksum);
ESTATUS SetCfgPdtDboxIpTable(ECHAR *p);

#endif

extern EUINT32 GetECNTestCfgType(void);
extern ESTATUS SetECNTestCfgType(EUINT32 v);

/*Secondary ECN IP Address*/
/*Return IP Address, string*/
extern ECHAR* GetCfgSecondECNAddr(void);

/*Return IP Address, Intege, Big Endian*/
extern EUINT32 GetCfgSecondECNAddrINT(void);


extern ESTATUS SetCfgSecondECNAddr(ECHAR *p);

/*FTP Server Configuration*/
extern ECHAR* GetCfgFtpServerAddr(void);

extern ESTATUS SetCfgFtpServerAddr(ECHAR *p);

extern ECHAR* GetCfgFtpUsername(void);

extern ESTATUS SetCfgFtpUsername(ECHAR *p);


extern ECHAR* GetCfgFtpPwd(void);

extern ESTATUS SetCfgFtpPwd(ECHAR *p);


/*NTP SERVER Configuration*/
/*Return IP Address, string*/
extern ECHAR* GetCfgPrimNtpServer(void);

/*Return IP Address, Intege, Big Endian*/
extern EUINT32 GetCfgPrimNtpServerINT(void);


extern ESTATUS SetCfgPrimNtpServer(ECHAR *p);

/*Return IP Address, string*/
extern ECHAR* GetCfgSecondNtpServer(void);

/*Return IP Address, Intege, Big Endian*/
extern EUINT32 GetCfgSecondNtpServerINT(void);
extern ESTATUS SetCfgSecondNtpServer(ECHAR *p);

extern EUINT32 GetCfgNtpZone(void);
extern ESTATUS SetCfgNtpZone(EUINT32 zone);

extern EUINT32  GetCfgNtpGpsUtcOffset(void);
extern ESTATUS SetCfgNtpGpsUtcOffset(EUINT32 offset);

extern EBOOL GetCfgNtpState(void);
extern ESTATUS SetCfgNtpState(EBOOL v);

extern EINT32 GetZoneStr(ECHAR *zoneStr, EINT32 zoneDiff);
extern EINT32 GetZoneDiff(ECHAR *zoneStr, EINT32 *zoneDiff);

extern EUINT32 GetCfgClkMode(void);
extern ESTATUS SetCfgClkMode(EUINT32 mode);

EINT32 GetCfgSystemMoniterReboot(void);
ESTATUS SetCfgSystemMoniterReboot(EINT32 Tmp);

extern ESTATUS AddTrapServer(ECHAR *ipAddr, EINT32 port);
extern ESTATUS DelTrapServer(ECHAR *ipAddr, EINT32 port);
extern ESTATUS GetTrapServer(EINT32 id, EUINT32 *ipAddr, EINT32 *port);

/*RS485 Device Configuratuon*/
#define MAX_RS485DEV_NUM    12

extern ESTATUS AddRS485Dev(EINT32 id,ECHAR *pDevName, EUINT32 addr);
extern ESTATUS DelRS485Dev(EINT32 id);
extern ESTATUS GetRS485Dev(EINT32 id, ECHAR *pDevName, EUINT32 *pAddr);

/*Environment Device Configuration*/
#define MAX_ENVIRONMENT_NUM  8

/*BSR IP Address Configuration*/
extern ESTATUS SetBSCfgBSRIPAddrEntry(EINT32 bsrID, EUINT32 ipAddr);
extern ESTATUS GetBSCfgBSRIPAddrEntry(EINT32 bsrID, EUINT32 *pIpAddr);

#ifdef LIB_PSS
/*BSC IP Address Configuration*/

extern ESTATUS SetBSCfgBSCIPAddrEntry(EINT32 bscID, EUINT32 ipAddr);
extern ESTATUS GetBSCfgBSCIPAddrEntry(EINT32 bscID, EUINT32 *pIpAddr);

#define	MAX_BSC_NUM	  256
extern ESTATUS SetBSCfgBSCNameEntry(EINT32 bsrID, ECHAR * pName);
extern ESTATUS GetBSCfgBSCNameEntry(EINT32 bscID, ECHAR * pName);
extern ESTATUS DelBSCfgBSCEntry(EINT32 bscID);
extern ESTATUS SetBSCfgBSCChanEntry(EINT32 bsrID, EINT32 chanID, EINT32 chanState);
extern ESTATUS GetBSCfgBSCChanEntry(EINT32 bsrID, EINT32 chanID, EINT32 *pChanState);
extern ESTATUS SetBSCfgBSCRecvIDEntry(EINT32 bsrID, EINT32 recvID);
extern ESTATUS GetBSCfgBSCRecvIDEntry(EINT32 bsrID,EINT32 *pRecvID);

#else
#ifdef LIB_PDT
extern ESTATUS SetBSCfgBSCType(EINT32 type);
extern EINT32 GetBSCfgBSCType(void);
extern EUINT32 GetCfgPdtMode(void);
extern  ESTATUS SetCfgPdtMode(EINT32 Tmp);
extern EUINT32 GetCfgPdtSpecialState(void);
extern ESTATUS SetCfgPdtSpecialState(EINT32 spst);

extern ESTATUS  PdtRmoToPdtTmo(EUINT16 bsrId);
extern ESTATUS  PdtTmoToPdtRmo(EUINT16 bsrId);
extern EINT32 GetBSCfgSyncBSCType(void);
extern ESTATUS SetBSCfgSyncBSCType(EINT32 v);

extern EINT32 GetBscCfgPowerThread(void);
extern EUINT32  SetBscCfgPowerThread(EUINT32 uiValue);
extern EINT32 GetBscCfgRCPos(void);
extern EUINT32 SetBscCfgRCPos(EUINT32 uiValue);
extern EINT32 GetBscCfgPpalPar(void);
extern EUINT32 SetBscCfgPpalPar(EUINT32 uiValue);
extern EUINT32 GetBscCfgSingleBsWeakAuth(void);
extern EINT32 SetBscCfgSingleBsWeakAuth(EUINT32 uiValue);
extern EUCHAR *GetBscCfgWeakAuthMkey(void);
extern EINT32  SetBscCfgWeakAuthMkey(EUCHAR *punValue);
extern EUINT32 GetBscCfgWeakAuthMKVer(void);
extern EINT32  SetBscCfgWeakAuthMKVer(EUINT32 uiValue);
extern EUINT32 GetBscCfgEmgTimerLen (void);
extern EINT32  SetBscCfgEmgTimerLen(EUINT32 uiValue);
extern EUINT32 GetBscCfgPacketTimerLen (void);
extern EINT32  SetBscCfgPacketTimerLen(EUINT32 uiValue);
extern EUINT32 GetBscCfgCrcMaskPar (void);
extern EINT32  SetBscCfgCrcMaskPar(EUINT32 uiValue);
extern EINT32 GetCfgPdtChannelScene(void);
extern ESTATUS SetCfgPdtChannelScene(EUINT32 val);
extern EINT32 GetCfgPdtGpsNum(void);
extern ESTATUS SetCfgPdtGpsNum(EUINT32 val);
extern  ESTATUS GetBSCfgGpsChan(EINT32 bsrID, EINT32 chanID, EINT32 *pChanState);

extern EINT32   SetBSCfgCtrlChannelFER (EUINT32 v);
extern EUINT32  GetBSCfgCtrlChannelFER (void);

extern EINT32   SetBSCfgCtrlChannelRSSI (EUINT32 v);
extern EUINT32  GetBSCfgCtrlChannelRSSI (void);

extern EINT32   SetBSCfgTrafficChannelFER (EUINT32 v);
extern EUINT32  GetBSCfgTrafficChannelFER (void);

extern EINT32   SetBSCfgTrafficChannelRSSI (EUINT32 v);
extern EUINT32  GetBSCfgTrafficChannelRSSI (void);

extern EINT32   SetBSCfgBSMF (EUINT32 v);
extern EUINT32  GetBSCfgBSMF (void);

extern EINT32   SetBSCfgCtrlChannelDML (EUINT32 v);
extern EUINT32  GetBSCfgCtrlChannelDML (void);

extern EINT32   SetBSCfgTrafficChannelDML (EUINT32 v);
extern EUINT32  GetBSCfgTrafficChannelDML (void);

extern EINT32   SetBSCfgCtrlChannelVML (EUINT32 v);
extern EUINT32  GetBSCfgCtrlChannelVML (void);

extern EINT32   SetBSCfgTrafficChannelVML (EUINT32 v);
extern EUINT32  GetBSCfgTrafficChannelVML (void);

extern EINT32   SetBSCfgHomeRSSI (EUINT32 v);
extern EUINT32  GetBSCfgHomeRSSI (void);

extern EINT32   SetBSCfgHomeLEFT (EUINT32 v);
extern EUINT32  GetBSCfgHomeLEFT (void);

extern EINT32 SetBSCfgBsGrade(EUINT32 grade);
extern EUINT32 GetBSCfgBsGrade(void);

extern EINT32 SetBSCfgBsType(EUINT32 type);
extern EUINT32 GetBSCfgBsType(void);

extern EUINT32 SetSelfGpsTsccRepSwitch(EUINT32 value);
extern EUINT32 GetSelfGpsTsccRepSwitch(void);

#endif
#endif

#if defined(LIB_PDT) || defined(LIB_PSS)
extern ECHAR *GetCfgPdtSyncBsMulticastIp(void);
extern EUINT32 GetCfgPdtSyncBsMulticastIpInt(void);
extern EINT32 SetCfgPdtSyncBsMulticastIp(ECHAR *p);
#endif

#ifdef LIB_PDT
extern ECHAR *GetCfgPdtCenterBsIp(void);
extern EUINT32 GetCfgPdtCenterBsIpInt(void);
extern EINT32 SetCfgPdtCenterBsIp(ECHAR *p);
#endif

#if defined(LIB_PDT)
/* pdt standard support: not stand, 1: stand, default:0 */
EINT32 GetCfgPdtStand(void);
ESTATUS SetCfgPdtStand(EUINT32 val);

/* pdt voice type, 0: old compatible, 1:ambe soft 2:selp soft default:1 */
EINT32 GetCfgPdtVoiceType(void);
ESTATUS SetCfgPdtVoiceType(EUINT32 val);

/* sync stattion 0:not sync, 1: sync */
EINT32 GetCfgPdtSyncBsc(void);
ESTATUS SetCfgPdtSyncBsc(EUINT32 val);

#endif

extern ECHAR GetCfgPdtRtpType(void);
extern EUINT32 SetCfgPdtRtpType(EUINT32 val);

extern EINT32 GetCfgPdtVoiceType(void);
extern ESTATUS SetCfgPdtVoiceType(EUINT32 val);

extern EINT32 GetCfgVoiceType(void);
extern ESTATUS SetCfgVoiceType(EINT32 type);

extern EINT32 GetCfgMSType(void);
extern EINT32 SetCfgMSType(EINT32 type);


extern ECHAR GetCfgBsRtpQueueCount(void);
extern EUINT32 SetCfgBsRtpQueueCount(EUINT32 val);

/*BS System Information*/
/*BS ID, range: 1, 100*/
extern EINT32 GetBSCfgBSID(void);
extern ESTATUS SetBSCfgBSID(EINT32 v);

/*BS Name, MAX Length: 16*/
extern ECHAR* GetBSCfgBSName(void);
extern ESTATUS SetBSCfgBSName(ECHAR *p);

/*BS GSSI, range: 1, 13999999*/
extern EINT32 GetBSCfgBSGSSI(void);
extern ESTATUS SetBSCfgBSGSSI(EINT32 v);

/*BS Authencation, MAX Length: 16, MIN Length: 6*/
extern ECHAR* GetBSCfgAuthKey(void);
extern ESTATUS SetBSCfgAuthKey(ECHAR *p);

/*BS Supported Authencation Algorithm , bit1: MD5, bit2: SHA-1, bit3: 3GPP f2*/
extern EINT32 GetBSCfgAuthAlg(void);
extern ESTATUS SetBSCfgAuthAlg(EINT32 v);

extern EINT32 GetBSCfgGpsSync(void);
extern ESTATUS SetBSCfgGpsSync(EINT32 v);

/* bs 类型 ，范围0-3, 默认值0 */
extern EINT32 GetBSCfgBSType(void);
extern ESTATUS SetBSCfgBSType(EINT32 v);
/*  closeWaitTime 10000ms            1-3600000 */
extern EUINT32 GetBSCfgCloseWaitTime(void);
extern ESTATUS SetBSCfgCloseWaitTime(EUINT32 v);

extern EUINT32 GetBSCfgMcchFlag(void);
extern ESTATUS SetBSCfgMcchFlag(EUINT32 v);

#if defined(LIB_PDT) || defined(LIB_PSS)
/* mode net scal 0-3, 0*/
EINT32 GetPdtcCfgMode(void);
ESTATUS SetPdtcCfgMode(EINT32 v);

/* Location Area Identity 1-0xFFF, 1*/
EINT32 GetPdtcCfgLAI(void);
ESTATUS SetPdtcCfgLAI(EINT32 v);

/* Network Area Identity 1-0x1FF, 1*/
EINT32 GetPdtcCfgNAI(void);
ESTATUS SetPdtcCfgNAI(EINT32 v);

/* authentication type 0:pdt, 1:tetra */
EINT32 GetPdtcCfgAuthType(void);
ESTATUS SetPdtcCfgAuthType(EINT32 v);

/* Mobile Zone Code 1-0x3F, 1*/
EINT32 GetPdtcCfgMZC(void);
ESTATUS SetPdtcCfgMZC(EINT32 v);

/* factory identity 1-0xFF, 1*/
EINT32 GetPdtcCfgMFID(void);
ESTATUS SetPdtcCfgMFID(EINT32 v);

/* factory identity 0-15, 0*/
EINT32 GetPdtcCfgCC(void);
ESTATUS SetPdtcCfgCC(EINT32 v);

/* pdt iop 0-0xffffffff, 0*/
EINT32 GetCfgPdtIOP(void);
ESTATUS SetCfgPdtIOP(EINT32 v);

/* user classfy identity 0-3, 3*/
EINT32 GetPdtcCfgPAR(void);
ESTATUS SetPdtcCfgPAR(EINT32 v);
/* random acc limit 0-3, 0*/
EINT32 GetPdtcCfgUP(void);
ESTATUS SetPdtcCfgUP(EINT32 v);

/* address mask 0-24, 0*/
EINT32 GetPdtcCfgMASK(void);
ESTATUS SetPdtcCfgMASK(EINT32 v);

/* retransmit time  0-15, 5*/
EINT32 GetPdtcCfgWT(void);
ESTATUS SetPdtcCfgWT(EINT32 v);

/* ALOHA base frame length  0-15, 5*/
EINT32 GetPdtcCfgBackoff(void);
ESTATUS SetPdtcCfgBackoff(EINT32 v);

/* ALOHA base frame length  0-3, 0*/
EINT32 GetPdtcCfgSF(void);
ESTATUS SetPdtcCfgSF(EINT32 v);

/* AIETYPE 0-3, 0*/
EINT32 GetPdtcCfgAIETYPE(void);
ESTATUS SetPdtcCfgAIETYPE(EINT32 v);

/* max ms tx power 15-45, 35*/
EINT32 GetPdtcCfgmaxTxPower(void);
ESTATUS SetPdtcCfgmaxTxPower(EINT32 v);

/* ALOHA base frame length  -125 -  -50, -110*/
EINT32 GetPdtcCfgminRxLevel(void);
ESTATUS SetPdtcCfgminRxLevel(EINT32 v);

/* frames with no traffic  0-144, 144*/
EINT32 GetPdtcCfgtraffInactDelay(void);
ESTATUS SetPdtcCfgtraffInactDelay(EINT32 v);

/* reselect Threshold   0-15, 10*/
EINT32 GetPdtcCfgreselThreshold(void);
ESTATUS SetPdtcCfgreselThreshold(EINT32 v);

/* reselect hysteresis 0-15, 6*/
EINT32 GetPdtcCfgreselHysteresis(void);
ESTATUS SetPdtcCfgreselHysteresis(EINT32 v);

/* unconfirm retry  1-4, 2*/
EINT32 GetPdtcCfgunackRetries(void);
ESTATUS SetPdtcCfgunackRetries(EINT32 v);

/* active retry   1-4, 3*/
EINT32 GetPdtcCfgackRetries(void);
ESTATUS SetPdtcCfgackRetries(EINT32 v);
/*gsp*/
EINT32 GetPdtcCfgGpsMode(void);
ESTATUS SetPdtcCfgGpsMode(EINT32 v);

EUINT32 GetPdtcCfgPttPriority(void);
ESTATUS SetPdtcCfgPttPriority(EUINT32 v);

EINT32 GetBSCfgFreqBand(void);
ESTATUS SetBSCfgFreqBand(EINT32 v);

EUINT32 GetBSCfgDuplexSpacing(void);
ESTATUS SetBSCfgDuplexSpacing(EINT32 v);


EBOOL GetBSCfgRXAboveTX(void);
ESTATUS SetBSCfgRXAboveTX(EBOOL v);


EINT32 GetBSCfgSubscriberClass(void);
ESTATUS SetBSCfgSubscriberClass(EINT32 v);

EINT32 GetBSCfgMAXTXPower(void);
ESTATUS SetBSCfgMAXTXPower(EINT32 v);
/*MIN RX Acess Level, range:-125, -50, default: -110dbm*/
EINT32 GetBSCfgMINRXAccLevel(void);
ESTATUS SetBSCfgMINRXAccLevel(EINT32 v);

EINT32 GetBSCfgRadioDLTimeout(void);
ESTATUS SetBSCfgRadioDLTimeout(EINT32 v);

EUINT32 GetBSCfgColorCode(void);
ESTATUS SetBSCfgColorCode(EUINT32 v);

EINT32 GetBSCfgCarrierOffset(void);
ESTATUS SetBSCfgCarrierOffset(EINT32 v);
EINT32 GetCfgAdgwMptType(void);

EUINT32 GetADGWAnalogType(void);
ECHAR* GetCfgDigitalECNAddr(void);
EUINT32 GetCfgDigitalECNAddrINT(void);
ESTATUS SetCfgDigitalECNAddr(ECHAR *p);

#else

/*BS Service Cell information*/
/*MCC(Mobile Country code), range: 0, 1023*/
extern EUINT32 GetBSCfgMCC(void);
extern ESTATUS SetBSCfgMCC(EUINT32 v);

/*MNC(Mobile Network Code), range: 0, 16383*/
extern EUINT32 GetBSCfgMNC(void);
extern ESTATUS SetBSCfgMNC(EUINT32 v);

/*Coloer code, range: 0, 63, default:1*/
extern EUINT32 GetBSCfgColorCode(void);
extern ESTATUS SetBSCfgColorCode(EUINT32 v);

/*System code, range: 0, 15, default:1*/
extern EUINT32 GetBSCfgSysCode(void);
extern ESTATUS SetBSCfgSysCode(EUINT32 v);

/*LA(Location ), range: 0, 16383, default:0*/
extern EINT32 GetBSCfgLA(void);
extern ESTATUS SetBSCfgLA(EINT32 v);

/*Subscriber Class, range: 0, 0xffff, default: 0xffff*/
extern EINT32 GetBSCfgSubscriberClass(void);
extern ESTATUS SetBSCfgSubscriberClass(EINT32 v);

/*BS Service Cell Access Parameter*/
/*MAX MS TX Power, range:15, 45, default: 35dbm*/
extern EINT32 GetBSCfgMAXTXPower(void);
extern ESTATUS SetBSCfgMAXTXPower(EINT32 v);

/*MIN RX Acess Level, range:-125, -50, default: -110dbm*/
extern EINT32 GetBSCfgMINRXAccLevel(void);
extern ESTATUS SetBSCfgMINRXAccLevel(EINT32 v);

/*Access paramter, range:-53, -23, default: -39dbm*/
extern EINT32 GetBSCfgAccessParam(void);
extern ESTATUS SetBSCfgAccessParam(EINT32 v);

/*Minimum Priority, range:0, 7, default: 0*/
extern EINT32 GetBSCfgMINPriority(void);
extern ESTATUS SetBSCfgMINPriority(EINT32 v);

/*Random Access Timing, range:0, 15, default: 8 TDMA frame, 0: Always randomize, 15: Immediate access..*/
extern EINT32 GetBSCfgRandAccTime(void);
extern ESTATUS SetBSCfgRandAccTime(EINT32 v);

/*Radion Downlink Timeout, range: 0, 2360, default:432, units: Timeslots, 0 = timeout disabled.*/
extern EINT32 GetBSCfgRadioDLTimeout(void);
extern ESTATUS SetBSCfgRadioDLTimeout(EINT32 v);

/*Random Access Transmissions range: 0, 15, default:5*/
extern EINT32 GetBSCfgRandAccTrans(void);
extern ESTATUS SetBSCfgRandAccTrans(EINT32 v);

/*Random Access Response Timer, range: 1, 15, default: 5*/
extern EINT32 GetBSCfgRandAccRspTimer(void);
extern ESTATUS SetBSCfgRandAccRspTimer(EINT32 v);

/*Frame Length Factor, range: 1, 4, default: 1*/
extern EINT32 GetBSCfgFrameLenFactor(void);
extern ESTATUS SetBSCfgFrameLenFactor(EINT32 v);

/*Random Acc. Frame Length, range: 1, 2, 3, 4, 5, 6, 8, 10, 12, 16, 20, 24, 32, default: 10, units:subslots*/
extern EINT32 GetBSCfgRandAccFrameLen(void);
extern ESTATUS SetBSCfgRandAccFrameLen(EINT32 v);

/*BS Service Cell Traffic Parameter*/
/*Traffic Timeout, range: 0, 2160, default: 432*/
extern EINT32 GetBSCfgTrffTimeout(void);
extern ESTATUS SetBSCfgTrffTimeout(EINT32 v);

/*Traffic Inactivity Delay, range: 0, 144, default: 5, units: timeslots*/
extern EINT32 GetBSCfgTrffInactiveDelay(void);
extern ESTATUS SetBSCfgTrffInactiveDelay(EINT32 v);

/*Taffic Reserved Access Timeout (T.206), range: 9, 100, default: 18, units: frames*/
extern EINT32 GetBSCfgTrffRsvAccTimeout(void);
extern ESTATUS SetBSCfgTrffRsvAccTimeout(EINT32 v);

EINT32 GetBSCfgUplinkVoiceFailureDetectionTime(void);
ESTATUS SetBSCfgUplinkVoiceFailureDetectionTime(EINT32 v);

EINT32 GetBSCfgUplinkVoiceFailureThreshold(void);
ESTATUS SetBSCfgUplinkVoiceFailureThreshold(EINT32 v);

EINT32 GetBSCfgReTransmissionDataMaxNum(void);
ESTATUS SetBSCfgReTransmissionDataMaxNum(EINT32 v);

EINT32 GetBSCfgUnitdataRepetitionNum(void);
ESTATUS SetBSCfgUnitdataRepetitionNum(EINT32 v);

EINT32 GetBSCfgPduAssociationFlag(void);
ESTATUS SetBSCfgPduAssociationFlag(EINT32 v);

/*BS Service Cell Reselect Parameter*/
/*Slow Reselect Threshold Above Fast, range: 0, 30, default: 6, units: db*/
extern EINT32 GetBSCfgSlowReselThreshold(void);
extern ESTATUS SetBSCfgSlowReselThreshold(EINT32 v);

/*Fast Reselect Threshold, range: 0, 30, default: 8, units: db*/
extern EINT32 GetBSCfgFastReselThreshold(void);
extern ESTATUS SetBSCfgFastReselThreshold(EINT32 v);

/*Slow Reselect Hysteresis, range: 0, 30, default: 8, units: db*/
extern EINT32 GetBSCfgSlowReselHysteresis(void);
extern ESTATUS SetBSCfgSlowReselHysteresis(EINT32 v);

/*Fast Reselect Hysteresis, range: 0, 30, default: 6, units: db*/
extern EINT32 GetBSCfgFastReselHysteresis(void);
extern ESTATUS SetBSCfgFastReselHysteresis(EINT32 v);

/*CellServiceLevel: 0, 3, default: 0*/
extern EINT32 GetBSCfgCellServiceLevel(void);
extern ESTATUS SetBSCfgCellServiceLevel(EINT32 v);


/*BS Service Cell Carrier Parameter*/
/*Frequency Band, range: 0, 15, default: 3*/
extern EINT32 GetBSCfgFreqBand(void);
extern ESTATUS SetBSCfgFreqBand(EINT32 v);

/*TX (Transmit) Base Frequency, range: 100000000, 1000000000, default: 300000000, units: hz*/
extern EINT32 GetBSCfgTXBaseFreq(void);
extern ESTATUS SetBSCfgTXBaseFreq(EUINT32 v);

/*Duplex Spacing, range: 0, 7, default: 0*/
extern EUINT32 GetBSCfgDuplexSpacing(void);
extern ESTATUS SetBSCfgDuplexSpacing(EINT32 v);

/*Carrier Offset, range: 0, 6250, 6250, 12500, default: 0, units: hz*/
extern EINT32 GetBSCfgCarrierOffset(void);
extern ESTATUS SetBSCfgCarrierOffset(EINT32 v);

/*RX Above TX, range: TRUE/FALSE, default: FALSE*/
extern EINT32 GetBSCfgRXAboveTX(void);
extern ESTATUS SetBSCfgRXAboveTX(EINT32 v);

/*BsN252, 1~5, 2*/
extern EUINT32 GetBSCfgBsN252(void);
extern ESTATUS SetBSCfgBsN252(EUINT32 v);

/*BsN252, 0~5, 1*/
extern EUINT32 GetBSCfgBsN253(void);
extern ESTATUS SetBSCfgBsN253(EUINT32 v);

/*broadcast time >0,  60*/    
EUINT32 GetBSCfgBroadcastTime(void);
ESTATUS SetBSCfgBroadcastTime(EUINT32 v);

/* scan time, >0, 60*/
EUINT32 GetBSCfgScanTime(void);
ESTATUS SetBSCfgScanTime(EUINT32 v);

/* cell reselect support,default 2: 0-3*/
EINT32 GetBSCfgCellReselSupport(void);
ESTATUS SetBSCfgCellReselSupport(EINT32 v);

/* neighbour cell syncronize default 1, 0-1*/
EINT32 GetBSCfgNeighCellSync(void);
ESTATUS SetBSCfgNeighCellSync(EINT32 v);    


/* SDS address method  0   0-3 */
EUINT32 GetBSCfgSDSaddrMethod(void);

ESTATUS SetBSCfgSDSAddrMethod(EUINT32 v);

#endif /* LIB_PDT */
/*  heartWaitTime 1000ms            1-3600000 */
EUINT32 GetBSCfgHeartWaitTime(void);
ESTATUS SetBSCfgHeartWaitTime(EUINT32 v);

/* regWaitTime 1000ms            1-3600000 */
EUINT32 GetBSCfgRegWaitTime(void);
ESTATUS SetBSCfgRegWaitTime(EUINT32 v);

/* openWaitTime 10000ms           1-3600000 */
EUINT32 GetBSCfgOpenWaitTime(void);
ESTATUS SetBSCfgOpenWaitTime(EUINT32 v);
/*  linkrecoverytime  */
EUINT32 GetBSCfgLinkRecoveryTime(void);
ESTATUS SetBSCfgLinkRecoveryTime(EUINT32 v);

/*Crtp two fullheader's max interval time: 0~0xffff, 0*/
extern EUINT32 GetBSCfgMaxTime(void);
extern ESTATUS SetBSCfgMaxTime(EUINT32 v);

/**Crtp two fullheader's max interval time: >= 0 ,700 */
extern EUINT32 GetBSCfgMaxPeriod(void);
extern ESTATUS SetBSCfgMaxPeriod(EUINT32 v);

/*crtp max head size:20~168 ,168 */
extern EUINT32 GetBSCfgMaxHeadSize(void);
extern ESTATUS SetBSCfgMaxHeadSize(EUINT32 v);

/*max parall compress num:3~1000 ,67 */
extern EUINT32 GetBSCfgMaxCrtpContext(void);
extern ESTATUS SetBSCfgMaxCrtpContext(EUINT32 v);

#define MAX_HDLC_IF_NUM 5
#define MAX_HDLC_LINK_NUM 5

/*BSR Configuration*/
#define MAX_BSR_NUM   16
#define MAX_SLOT_NUM  8

extern ESTATUS SetBSCfgBSRNameEntry(EINT32 bsrID, ECHAR * pName);

extern ESTATUS SetBSCfgBSRRecvIDEntry(EINT32 bsrID, EINT32 recvID);
extern ESTATUS SetBSCfgBSRFreqEntry(EINT32 bsrID,EUINT16 carrierID,EUINT32 freq);

extern ESTATUS DelBSCfgBSREntry(EINT32 bsrID);

extern ESTATUS GetBSCfgBSRNameEntry(EINT32 bsrID, ECHAR * pName);
extern ESTATUS GetBSCfgBSRRecvIDEntry(EINT32 bsrID,EINT32 *pRecvID);
extern ESTATUS GetBSCfgBSRFrequenceEntry(EINT32 bsrID,EUINT16 carrierID,EUINT32 *pFreq);
extern ESTATUS GetBSCfgBSRCSCCHEntry(EINT32 bsrID,EUINT16 *pNumOfcscch);

extern ESTATUS SetBSCfgBSRChanEntry(EINT32 bsrID, EINT32 chanID, EINT32 chanState);

extern ESTATUS GetBSCfgBSRChanEntry(EINT32 bsrID, EINT32 chanID, EINT32 *pChanState);

extern ESTATUS GetBSCfgBSRTempEntry(EINT32 bsrID,EUINT16 *pTemp);
extern ESTATUS SetBSCfgBSRTempEntry(EINT32 bsrID,EUINT16 tempThreshold);


extern ESTATUS GetBSCfgBSRReturnLossEntry(EINT32 bsrID,EUINT16 *pReturnloss);
extern ESTATUS SetBSCfgBSRReturnLossEntry(EINT32 bsrID,EUINT16 returnLoss);

extern ESTATUS GetBSCfgBSRPowerEntry(EINT32 bsrID,EUINT16 *pPower);
extern ESTATUS SetBSCfgBSRPowerEntry(EINT32 bsrID,EUINT16 power);

extern ESTATUS GetBSCfgBSRTypeEntry(EINT32 bsrID, EUINT16 * pType);
extern ESTATUS SetBSCfgBSRTypeEntry(EINT32 bsrID, EUINT16 type);

extern ESTATUS GetBSCfgBSRMcnumEntry(EINT32 bsrID, EUINT32 * pMcnum);
extern ESTATUS SetBSCfgBSRMcnumEntry(EINT32 bsrID, EUINT32 Mcnum);
extern ESTATUS GetBSCfgBSRRxnumEntry(EINT32 bsrID, EUINT32 * pRxnum);
extern ESTATUS SetBSCfgBSRRxnumEntry(EINT32 bsrID, EUINT32 Rxnum);

extern ESTATUS GetBSCfgBSRCapwrEntry(EINT32 bsrID, EUINT32 * pCapwr);
extern ESTATUS SetBSCfgBSRCapwrEntry(EINT32 bsrID, EUINT32 capwr);

extern ESTATUS SetBSCfgBSRPscindexEntry(EINT32 bsrID,EUINT16 carrierID,EUINT32 pscindex);
extern ESTATUS GetBSCfgBSRPscindexEntry(EINT32 bsrID,EUINT16 carrierID,EUINT32 *pPscindex);

extern EINT32 GetBSCfgIdleTimeBeforeTrpaClose(void);
extern ESTATUS SetBSCfgIdleTimeBeforeTrpaClose(EINT32 v);

/*ECN Configuration*/
/*LDAP Server Configuration*/
/*LDAP Server IP address*/
extern ECHAR* GetCfgLDAPServerAddr(void);
extern ESTATUS SetCfgLDAPServerAddr(ECHAR *p);

/*ACCESS LDAP Server Username, MAX LENGTH:16*/
extern ECHAR* GetCfgLDAPUsername(void);
extern ESTATUS SetCfgLDAPUsername(ECHAR *p);

/*ACCESS LDAP Server Password, MAX LENGTH:16*/
extern ECHAR* GetCfgLDAPPwd(void);
extern ESTATUS SetCfgLDAPPwd(ECHAR *p);
    
/*ECN System Information*/
/*ECN ID, range: 1, 56*/
EINT32 GetECNCfgECNID(void);
ESTATUS SetECNCfgECNID(EINT32 v);

/*ECN Name, MAX Length: 16*/
ECHAR* GetECNCfgECNName(void);
ESTATUS SetECNCfgECNName(ECHAR *p);

/*ECN System information*/
/*MCC(Mobile Country code), range: 0, 1023*/
EUINT32 GetECNCfgMCC(void);
ESTATUS SetECNCfgMCC(EUINT32 v);

/*MNC(Mobile Network Code), range: 0, 16383*/
EUINT32 GetECNCfgMNC(void);
ESTATUS SetECNCfgMNC(EUINT32 v);

/*System code, range: 0, 15, default:1*/
EUINT32 GetECNCfgSysCode(void);
ESTATUS SetECNCfgSysCode(EUINT32 v);

/*ECN Authenticaiton Key, MAX Length: 16, MIN Length: 6*/
ECHAR* GetECNCfgAuthKey(void);
ESTATUS SetECNCfgAuthKey(ECHAR *p);

/*ECN General Parameter*/
/*Pre-emption Mode, range: 0(Pre-emption Presentation), 1(Forced User Pre-emption), default: 2*/
EINT32 GetECNCfgPrmptMode(void);
ESTATUS SetECNCfgPrmptMode(EINT32 v);

/*Route Status Events to Dispatch, range: TRUE/FALSE, default: FALSE*/
EBOOL GetECNCfgRTStatusToDS(void);
ESTATUS SetECNCfgRTStatusToDS(EBOOL v);

/*Multigroup Listeners Preemptable, range: TRUE/FALSE, default: TRUE*/
EBOOL GetECNCfgMultiGPLstPrmpt(void);
ESTATUS SetECNCfgMultiGPLstPrmpt(EBOOL v);

/*Max Number of Short Data Retries, range: 1, 10, default: 5*/
EINT32 GetECNCfgMaxShortDataRetries(void);
ESTATUS SetECNCfgMaxShortDataRetries(EINT32 v);

/*Tetra mode, range: 0, 2, range: 0(Message), 1(quasi-transmission), 2(transmission), default: 1*/
EINT32 GetECNCfgTrunkingMode(void);
ESTATUS SetECNCfgTrunkingMode(EINT32 v);

/*End the call after hangup time, range: TRUE/FALSE, default: TRUE*/
EBOOL GetECNCfgEndAfterHangTime(void);
ESTATUS SetECNCfgEndAfterHangTime(EBOOL v);

/* queue the user's transmit request 1:yes, 2:no */
EINT32 GetECNCfgTransRequestQueue(void);
ESTATUS SetECNCfgTransRequestQueue(EINT32 v);

/*allow one register area has several locations 1:allow(yes) 2:no*/
EINT32 GetECNCfgRaAllowMultiLa(void);
ESTATUS SetECNCfgRaAllowMultiLa(EINT32 v);

/*group attach life time: nextITSIAttach(0),nextLocationUpdate(1)*/
EINT32 GetECNCfgGroupLifeTime(void);
ESTATUS SetECNCfgGroupLifeTime(EINT32 v);

/*notify methord of register: 0;broadcast 1:group by group*/
EINT32 GetECNCfgNotifyRegMode(void);
ESTATUS SetECNCfgNotifyRegMode(EINT32 v);

/*group call area: 0: select this group's users. 1: select and scan this group's users*/
EINT32 GetECNCfgGrpCallPagingArea(void);
ESTATUS SetECNCfgGrpCallPagingArea(EINT32 v);

/*ssi hash table size*/
EINT32 GetECNCfgSsiHashSize(void);
ESTATUS SetECNCfgSsiHashSize(EINT32 v);

/*Timer*/
/*Group Call Service Timeout, range: 1, 30, default: 2, units: second*/
EINT32 GetECNCfgGroupCallHangTime(void);
ESTATUS SetECNCfgGroupCallHangTime(EINT32 v);

/*Private Call Service Timeout, range: 10, 60, default: 10, units: second*/
EINT32 GetECNCfgPrvtCallHangTime(void);
ESTATUS SetECNCfgPrvtCallHangTime(EINT32 v);

/*Private Call Service Timeout, range: 0, 3660, default: 30, units: second*/
EINT32 GetECNCfgEmergHangTime(void);
ESTATUS SetECNCfgEmergHangTime(EINT32 v);

/*Maximum Group Call Duration /Channel Assignment, range: 1, 60, default: 10, units: minute*/
EINT32 GetECNCfgGroupCallDuration(void);
ESTATUS SetECNCfgGroupCallDuration(EINT32 v);

/*Maximum Private Call Duration /Channel Assignment, range: 1, 60, default: 10, units: minute*/
EINT32 GetECNCfgPrvtCallDuration(void);
ESTATUS SetECNCfgPrvtCallDuration(EINT32 v);

/*Maximum Interconnect Call Duration /Channel Assignment, range: 1, 60, default: 10, units: minute*/
EINT32 GetECNCfgInterconnCallDuration(void);
ESTATUS SetECNCfgInterconnCallDuration(EINT32 v);

/*Interconnect Call Ring Length, range: 1, 60, default: 55, units: second*/
EINT32 GetECNCfgInterconnRing(void);
ESTATUS SetECNCfgInterconnRing(EINT32 v);

/*Private Call Ring Length, range: 1, 60, default: 20, units: second*/
EINT32 GetECNCfgPrvtRing(void);
ESTATUS SetECNCfgPrvtRing(EINT32 v);

/*Call Setup, range: 1, 20, default: 8, units: second*/
EINT32 GetECNCfgCallSetup(void);
ESTATUS SetECNCfgCallSetup(EINT32 v);

/*Interconnect Call Fade, range: 5, 30, default: 10, units: second*/
EINT32 GetECNCfgInterconnFade(void);
ESTATUS SetECNCfgInterconnFade(EINT32 v);

/*Interconnect Call Final, range: 5, 30, default: 15, units: second*/
EINT32 GetECNCfgInterconnFinal(void);
ESTATUS SetECNCfgInterconnFinal(EINT32 v);

/*Channel Reserved, range: 0, 255, default: 0, units: second*/
EINT32 GetECNCfgChanReserved(void);
ESTATUS SetECNCfgChanReserved(EINT32 v);

/*MAX Transmission Time, range: 5, 300, default: 65, units: second*/
EINT32 GetECNCfgMAXTransTime(void);
ESTATUS SetECNCfgMAXTransTime(EINT32 v);

/*late entry intervalue, range: 1,30*/
EINT32 GetECNCfgLateEntryInterval(void);
ESTATUS SetECNCfgLateEntryInterval(EINT32 v);

/*scan user's record cycle, range: 1,5*/
EINT32 GetECNCfgSubScanInterval(void);
ESTATUS SetECNCfgSubScanInterval(EINT32 v);

/*bs link recorey timeout, range: 5,30*/
EINT32 GetECNCfgBsLinkRecovery(void);
ESTATUS SetECNCfgBsLinkRecovery(EINT32 v);

/*status message Sent Timeout, range: 1,6*/
EINT32 GetECNCfgStatusSentTimeout(void);
ESTATUS SetECNCfgStatusSentTimeout(EINT32 v);

/*wait time for reporting of send short date, range: 1,10*/
EINT32 GetECNCfgSdsSentTimeout(void);
ESTATUS SetECNCfgSdsSentTimeout(EINT32 v);

/*addtion wait time for reporting of send short date, range: 0,6*/
EINT32 GetECNCfgSdsSentTimeoutAdd(void);
ESTATUS SetECNCfgSdsSentTimeoutAdd(EINT32 v);

/*the start of Multicast IP Address for Voice*/
ECHAR* GetECNCfgVoiceStartIP(void);
ESTATUS SetECNCfgVoiceStartIP(ECHAR *p);

/*the count of Multicast IP Address for Voice, range: 1, 8192*/
EUINT32 GetECNCfgVoiceIPNum(void);
ESTATUS SetECNCfgVoiceIPNum(EUINT32 v);

/*Adjacent Cell Configuration*/
#define MAX_BS_ID 100
#define MAX_ECN_ID 56
#define MAX_ADJCELL_ID 31

extern ESTATUS DelECNCfgAdjCellEntry(EINT32 bsID, EINT32 ecnIDofAdjCell, EINT32 bsIDofAdjCell);

extern ESTATUS AddECNCfgAdjCellEntry(EINT32 bsID, EINT32 ecnIDofAdjCell, EINT32 bsIDofAdjCell);

/*BS Service Configuration is changed, OK: changed, ERROR: no changed*/
extern ESTATUS BSSrvCfgIsChange(void);

extern ESTATUS InitBscCfg(void);
extern ESTATUS LoadBscCfg(void);

extern ESTATUS SaveCfg(void);

extern EINT32 InitBscMng(void);                                     //initialize bsc board management

extern EUINT16 GetCarrierNumByBsrId(EUINT16 bsrId,EUINT16 carrierid);
extern EUINT16 GetPDTChannelNumByBsrId(EUINT16 bsrId,EUINT16 carrierid);

extern EUINT16 GetBsrIdByPDTChannelNum(EUINT16 chanNum);
extern EUINT16 GetCarrierByPDTChannelNum(EUINT16 chanNum);

extern EUINT32 GetMcch(void);
extern EUINT16 GetMainCarrierBsrId(void);
extern EUINT16 GetMainCarrierCarrierId(EUINT16 bsrId);

extern EUINT32 GetStateOfSlaveBsc(void);                            //get state of slave bsc

extern int EthernetStatusChg(BOOL online,EUINT32 Ethernet);

extern int E1StatusChg(EUINT32 e1Num,int alarmCode,int isAlarm);

#ifdef VXWORKS
extern void ActiveMultiIp();                                        //active IP when board is master BSC
extern void DeleteMultiIp();                                        //delete IP when board is slave BSC
#endif

#define BASEFREQUECE 300000000
#define CHANNELBAND  25

enum                                                                //BSR status
{
    STATE_ERROR,
    STATE_OK
};

typedef struct
{
    EUCHAR mcch;		                                            //是否支持MCCH，0：不支持，1：支持
    EUCHAR state;                                                   //bsr state
    EUINT16 bsrId;                                                  //bsr id:1-16
    EUINT16 mcarrierNum;                                            //main carrier number
    EUCHAR channel[8];                                              //channel state
}BSRRESOURCE;
//配置文件名称定义
extern char BSC_SYS_CFG_COMM_FILENAME[DOC_PATH_MAX];
extern char  BSC_SYS_CFG_BSSRV_FILENAME[DOC_PATH_MAX];
extern char  BSC_SYS_CFG_ECN_FILENAME[DOC_PATH_MAX];
extern char  BSC_SYS_CFG_RDT_FILENAME[DOC_PATH_MAX];
extern char  BSC_SYS_CFG_ALLCFG_FILENAME[DOC_PATH_MAX];

extern char  BSC_VXWORKS_IMAGE_FILENAME[DOC_PATH_MAX];
extern char  BSC_FPGA_IMAGE_FILENAME[DOC_PATH_MAX];
extern char  BSR_VXWORKS_IMAGE_FILENAME[DOC_PATH_MAX];
extern char  BSR_FPGA_IMAGE_FILENAME[DOC_PATH_MAX];
extern char  BSR_DSP_IMAGE_FILENAME[DOC_PATH_MAX];
extern char PDT_MBSR_IMAGE_FILENAME[DOC_PATH_MAX];

#define BSC_SYS_CFG_COMM_SIGNAL   "#BSC_SYS_CFG_COMM\n"
#define BSC_SYS_CFG_BSSRV_SIGNAL  "#BSC_SYS_CFG_BSSRV\n"
#define BSC_SYS_CFG_ECN_SIGNAL    "#BSC_SYS_CFG_ECN\n"
#define BSC_SYS_CFG_RDT_SIGNAL    "#BSC_SYS_CFG_RDT\n"
/*temperature*/
extern EINT32 GetMaxTmp(void);
extern ESTATUS SetMaxTmp(EINT32 Tmp);
extern ESTATUS SetMinTmp(EINT32 Tmp);
extern EINT32 GetMinTmp(void);
/*environmet temperature*/
extern EINT32 GetEnvMaxTmp(void);
extern ESTATUS SetEnvMaxTmp(EINT32 Tmp);
extern EINT32 GetEnvMinTmp(void);
extern ESTATUS SetEnvMinTmp(EINT32 Tmp);
extern EINT32 GetEnvMaxHum(void);
extern ESTATUS SetEnvMaxHum(EINT32 Tmp);
extern EINT32 GetEnvMinHum(void);
extern ESTATUS SetEnvMinHum(EINT32 Tmp);


/*L2TP IP Address Configuration*/
extern ECHAR* GetCfgL2tpIpAddr(void);
extern ESTATUS SetCfgL2tpIpAddr(ECHAR *p);

/*Receive hello packet time*/
extern EUINT32 GetCfgL2tpHelloTime(void);
extern ESTATUS SetCfgL2tpHelloTime(EUINT32 helloTimeOut);

/*set l2tp bsc name*/
extern ECHAR* GetCfgL2tpLacName(void);
extern ESTATUS SetCfgL2tpLacName(ECHAR *p);

extern ECHAR* GetCfgPppUserName(void);
extern ESTATUS SetCfgPppUserName(ECHAR *p);
extern ECHAR* GetCfgPppPassword(void);
extern ESTATUS SetCfgPppPassword(ECHAR *p);


/*Net type Configuration*/
extern EUINT32 GetCfgNetType(void);
extern ESTATUS SetCfgNetType(EUINT32 netType);
enum Net_Type_E{
    ETH_TYPE ,
	FR_TYPE,
	VPN_TYPE,
	GRE_TYPE,
	PPPE1_TYPE,
    MAX_TYPE
};
extern EUINT32 GetCfgPingTxTmo(void);
extern ESTATUS SetCfgPingTxTmo(EUINT32 PingTxTmo);
extern EUINT32 GetCfgPingTxTmoMs(void);
extern ESTATUS SetCfgPingTxTmoMs(EUINT32 PingTxTmoMs);


#define BSR_REBOOT_ALARM    17                          //trap report of BSR reboot
#define REBOOT_BSR_FROM_BSC 4                           //trap cause number


#define BSC_REBOOT_ALARM    18                          //trap report of BSR reboot

enum
{
    BSR_TYPE_TETRA = 1,
    BSR_TYPE_PDT,
    BSR_TYPE_PDT4,
};

enum
{
    BSC_DOS_COMMAND = 1,                                //use reboot command to reboot BSC
    REBOOT_BSC_FROM_SNMP,                               //reboot BSR by SNMP command
	BSC_SELFCHECK_FAIL,
	GPS_MONITOR_FAIL,
};

#define CFG_FILE_LEN_MAX 0x8000
#define MAX_ROUTE_NUM 8

/*帧中继时隙搭接时的开始时隙*/
ESTATUS GetCfgE1StartSlot(void);
ESTATUS SetCfgE1StartSlot(EUINT32 slot);
ESTATUS GetCfgE1EndSlot(void);
ESTATUS SetCfgE1EndSlot(EUINT32 slot);

/*E1时隙搭接*/
extern ESTATUS GetCfgE1TdmConnect(void);
extern ESTATUS SetCfgE1TdmConnect(EUINT32 slot);

/*e1 级联配置*/
extern ESTATUS GetCfgE1CascadeStatus(EUINT32 unit);
extern ESTATUS SetCfgE1CascadeStatus(EUINT32 unit, EUINT32 stauts);
extern ESTATUS GetCfgE1CascadeSlotSrc(EUINT32 unit);
extern ESTATUS SetCfgE1CascadeSlotSrc(EUINT32 unit, EUINT32 slot);
extern ESTATUS GetCfgE1CascadeSlotDst(EUINT32 unit);
extern ESTATUS SetCfgE1CascadeSlotDst(EUINT32 unit, EUINT32 slot);
extern ESTATUS GetCfgE1CascadeSlotOffset(EUINT32 unit);
extern ESTATUS SetCfgE1CascadeSlotOffset(EUINT32 unit, EUINT32 offset);

/*时钟选择*/
extern ESTATUS GetCfgE1ClockSelect(void);
extern ESTATUS SetCfgE1ClockSelect(EUINT32 clock);

extern ESTATUS SetBSCfgSocketPort(EUINT32 v);
extern EUINT32 GetBSCfgSocketPort(void);

extern int SendToCbsc(void * pMsg);
extern EUINT16 GetMainCarrierNum(void);

/*****************image***************/
extern int GetImageStateByFileId(int fileId);

/******************************/

/*帧中继时隙搭接时的开始时隙*/
ESTATUS GetCfgE1StartSlot(void);
ESTATUS SetCfgE1StartSlot(EUINT32 slot);
ESTATUS GetCfgE1EndSlot(void);
ESTATUS SetCfgE1EndSlot(EUINT32 slot);

/*E1时隙搭接*/
extern ESTATUS GetCfgE1TdmConnect(void);
extern ESTATUS SetCfgE1TdmConnect(EUINT32 slot);

/*e1 级联配置*/
extern ESTATUS GetCfgE1CascadeStatus(EUINT32 unit);
extern ESTATUS SetCfgE1CascadeStatus(EUINT32 unit, EUINT32 stauts);
extern ESTATUS GetCfgE1CascadeSlotSrc(EUINT32 unit);
extern ESTATUS SetCfgE1CascadeSlotSrc(EUINT32 unit, EUINT32 slot);
extern ESTATUS GetCfgE1CascadeSlotDst(EUINT32 unit);
extern ESTATUS SetCfgE1CascadeSlotDst(EUINT32 unit, EUINT32 slot);
extern ESTATUS GetCfgE1CascadeSlotOffset(EUINT32 unit);
extern ESTATUS SetCfgE1CascadeSlotOffset(EUINT32 unit, EUINT32 offset);

/*时钟选择*/
extern ESTATUS GetCfgE1ClockSelect(void);
extern ESTATUS SetCfgE1ClockSelect(EUINT32 clock);
extern ESTATUS SetBSCfgBSCSingleFlag(EINT32 flag);
extern EINT32 GetBSCfgBSCSingleFlag(void);

//干扰和 拥塞
extern EINT32   SetBSCfgJamTestPeriod(EUINT32 val);
extern EUINT32 GetBSCfgJamTestPeriod(void);

extern EUINT32 GetBSCfgCarrierIntFlag(void);
extern EINT32 SetBSCfgCarrierIntFlag(EUINT32 val);

extern EUINT32 GetBSCfgDLJamThresholdLevel1(void);                //获得一级拥塞的门限值
extern  EINT32 SetBSCfgDLJamThresholdLevel1(EUINT32 val); 
//设置一级拥塞的门限值
extern EUINT32 GetBSCfgDLJamThresholdLevel2(void);               //获得二级拥塞的门限值
extern  EINT32 SetBSCfgDLJamThresholdLevel2(EUINT32 val);   //设置二级拥塞的门限值
extern EUINT32 GetBSCfgDLJamThresholdLevel3(void);              //获得三级拥塞的门限值
extern  EINT32 SetBSCfgDLJamThresholdLevel3(EUINT32 val);  //设置三级拥塞的门限值
extern EINT32 GetBSCfgIntCarrierDisable(void);
extern ESTATUS SetBSCfgIntCarrierDisable(EINT32 v);
extern EINT32 GetBSCfgIntCarrierRecovery(void);
extern ESTATUS SetBSCfgIntCarrierRecovery(EINT32 v);
extern EINT32 GetBSCfgBroadcastFlag(void);
extern ESTATUS SetBSCfgBroadcastFlag(EINT32 v);
extern EINT32 GetBSCfgCPUThresholdLevel1(void);
extern EINT32 SetBSCfgCPUThresholdLevel1(EUINT32 val);
extern EINT32 GetBSCfgCPUThresholdLevel2(void);
extern EINT32 SetBSCfgCPUThresholdLevel2(EUINT32 val);
extern EINT32 GetBSCfgCPUThresholdLevel3(void);
extern EINT32 SetBSCfgCPUThresholdLevel3(EUINT32 val);

extern EINT32 GetBSCfgDLJamThreshold(void);
extern  EINT32 SetBSCfgDLJamThreshold(EUINT32 val);
extern EINT32 GetBSCfgULJamThreshold(void);
extern  EINT32 SetBSCfgULJamThreshold(EUINT32 val);

extern  EUINT32 GetBSCfgDisturbTestPeriod(void);
extern  EINT32   SetBSCfgDisturbTestPeriod(EUINT32 val);
extern   EINT32 GetBSCfgDisturbRSSI(void);
extern  EINT32   SetBSCfgDisturbRSSI(EINT32 val);
extern EUINT32 GetBSCfgDisturbIntRate(void);
extern EINT32   SetBSCfgDisturbIntRate(EUINT32 val);
extern ESTATUS SetBSCfgGpsBdMode(EUINT32 mode);
extern EUINT32 GetBSCfgGpsBdMode(void);
extern ESTATUS SetBSCfgAlmLedFlag(EUINT32 flag);
extern EUINT32 GetBSCfgAlmLedFlag(void);

extern EINT32   SetBSCfgChangeMcchBeganTime (EUINT32 val);
extern EUINT32  GetBSCfgChangeMcchBeganTime (void);
extern EINT32   SetBSCfgChangeMcchEndTime (EUINT32 val);
extern EUINT32  GetBSCfgChangeMcchEndTime (void);
extern EINT32   SetBSCfgChangeMcchFlag(EUINT32 val);
extern EUINT32  GetBSCfgChangeMcchFlag(void);


extern ESTATUS SetBSCfgBSRMcchPriEntry(EINT32 bsrID, EINT32 mcchpri);
extern ESTATUS GetBSCfgBSRMcchPriEntry(EINT32 bsrID, EINT32 * pmcchpri);
extern EINT32   SetBSCfgLteFlag (EUINT32 v);
extern EUINT32  GetBSCfgLteFlag (void);
extern  EINT32 GetBscState(void);

extern void SetBearType(EUINT16 type);
extern EUINT16 GetBearType(void);

extern EINT32   SetBSCfgRebootTimes (EUINT32 v);
extern EUINT32  GetBSCfgRebootTimes  (void);
extern EINT32 SetBSCfgPsmFanAlarmFlag (EUINT32 v);
extern EUINT32 GetBSCfgPsmFanAlarmFlag  (void);

extern EUINT32 GetCfgTscNg(void);
extern EINT32 SetCfgTscNg(EUINT32 value);
extern EUINT32 GetCfgTscNdeg(void);
extern EINT32 SetCfgTscNdeg(EUINT32 value);
extern EUINT32 GetCfgTscNminmm(void);
extern EINT32 SetCfgTscNminmm(EUINT32 value);
extern EUINT32 GetCfgTscNminf(void);
extern EINT32 SetCfgTscNminf(EUINT32 value);
extern EUINT32 GetCfgTscEw(void);
extern EINT32 SetCfgTscEw(EUINT32 value);
extern EUINT32 GetCfgTscEdeg(void);
extern EINT32 SetCfgTscEdeg(EUINT32 value);
extern EUINT32 GetCfgTscEminmm(void);
extern EINT32 SetCfgTscEminmm(EUINT32 value);
extern EUINT32 GetCfgTscEminf(void);
extern EINT32 SetCfgTscEminf(EUINT32 value);
extern ESTATUS SetBSCfgFrameNumOfDelaySend(EUINT32 num);
extern EUINT32 GetBSCfgFrameNumOfDelaySend(void);
extern ESTATUS SetBSCfgRoamUserDetectTime(EUINT32 time);
extern EUINT32 GetBSCfgRoamUserDetectTime(void);
extern ESTATUS SetBSCfgGSdsSendtime(EUINT32 time);
extern EUINT32 GetBSCfgGSdsSendtime(void);

extern EINT32 GetBSCfgStealingInterval(void);
extern ESTATUS SetBSCfgStealingInterval(EINT32 v);

extern ESTATUS SetControlRate(EUCHAR ucSlotArray, EUCHAR ucDirect, EUINT32 uiRate);
extern ESTATUS GetBSCfgBSRRecvIDEntry(EINT32 bsrID,EINT32 *pRecvID);
extern ESTATUS GetBSCfgBSRFreqEntry(EINT32 bsrID,EUINT16 carrierID,EUINT32 *pFreq);

EINT32 GetBSCfgCommScchNum(void);
ESTATUS SetBSCfgCommScchNum(EINT32 v);

typedef struct 
{
    EINT32 interrupt;
    EINT32 kernel;
    EINT32 idle;
    EINT32 task;
}CPU_STATE;

typedef struct
{
    EULONG total; 
    EULONG allocated;
    EULONG free;
    EINT32 ratio;
}MEM_STATE;

#ifdef __cplusplus
}
#endif

#endif //__ETRA_CTRLBSC_H__

