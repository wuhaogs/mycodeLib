/************************************************************************
Copyright (C), 2009-2010, Eastcom.
File name：      socketLib.h
Author：          huangzd
Date：             09.7.17
Description：    对不同操作系统的socket接口进行封装，对上层提供统一socket接口
Others：         无
  *************************************************************************/
#ifndef __BEARBSC_H__
#define __BEARBSC_H__
#ifdef __cplusplus
extern "C" {
#endif
/************************************************************************
                            引用的头文件
*************************************************************************/
#include "sys.h"

/************************************************************************
                            宏定义
*************************************************************************/
//#define    ESOCK_STREAM    1        //TCP
//#define    ESOCK_DGRAM     2        //UDP
//#define    ESOCK_RAW       3

#define    SERVER_MAX_CONNECTIONS    10    //允许的最大连接数

enum {LOOP_OFF=0, LOOP_SELF, LOOP_OTHER};                             //语音数据包环回类型
enum {
		//增加不同速率电路
        TETRA_ACELP=1,
   		TETRA_TCH24,
    	TETRA_TCH48,
    	TETRA_TCH72,
        /*支持PDT*/
        PDT_SYNC_SIG,
        PDT_SELP_VOICE,
        PDT_AMBE_VOICE,
        PDT_SELP_SYNCSIG,
        PDT_AMBE_SYNCSIG,
        A_LAW_PCM, //10

        //增加AMR数据的
        /*宽带集群相关*/
        BWT_AMR = 11,
        BWT_ACELP_AMR = 12,
        BWT_AMBE_AMR = 13,
        BWT_AMBE_AMR_SYNCSIG = 14,

        /*pdt acelp + ambe*/
        PDT_ACELP_AMBE_VOICE = 15,
        PDT_ACELP_AMBE_SYNCSIG = 16,
        /*PDT 712相关*/
        PDT_CFG_G712_VOICE = 21,
        PDT_CFG_G712_SYNCSIG = 22,
        PDT_CFG_G712_ACELP_VOICE = 23,
        PDT_CFG_G712_ACELP_SYNCSIG = 24,
        PDT_CFG_G712_AMR_VOICE = 25,
        PDT_CFG_G712_AMR_SYNCSIG = 26,
        PDT_CFG_ACELP_VOICE = 27,
        PDT_CFG_AMR_VOICE = 28

    };            //语音数据包类型

enum
{
    TRAF_TYPE_H264 = 1,
}; // 视频数据包类型

enum {INACTIVE=0x00, SENDONLY=0x001, RCEVONLY=0x02, SENDRECV=0x03};   //RTP通道类型

/*同频同播基站类型定义*/
#ifdef LIB_PDT
enum{PDT_COMMON_BS = 0, PDT_SYNC_BS = 1};
#endif
#define PRIMA_NTP_SVR 1         //用于SetNtpServer(), 主备选择参数
#define SECOND_NTP_SVR 2

#define ETEXIST 2               //CreateRtpChannel()的返回值之一，代表要创建的RTP通道已经存在

#define BSC_BEAR_STAT           //Statistic switch

typedef struct rtp_chan_need		//需发送的RTP通道表的结构
{
    EUINT32 callId;					//组呼编号
    EUCHAR mode;
    EUCHAR loop;
    EUINT16 reserve;		//对齐原子
    EUINT16 endPoint;
    EUINT16 sndPoint;
    //PHY_SLOT upLink;
    //PHY_SLOT downLink;
    EUINT32 multicastIpAddr;		//主机序组播地址
}RTP_CHAN_NEED;

#ifndef SIZE_MS_BUF
#define SIZE_MS_BUF 64
#endif

typedef struct gre_chan_t
{
    EUINT32 greKey;
    EUINT32 ssi;				//通道的ssi值
    struct gre_chan_t *pKeyNext;	//以key为关键字链接起来的指针
    struct gre_chan_t *pSsiNext;    //以ssi/saApi为关键字链接起来的指针
    EUINT32 length;               //arrMsBuf数据的大小
    ECHAR arrMsBuf[SIZE_MS_BUF];    //用来存储gre通道的空口信息
    ECHAR snApi;
    ECHAR state;
}GRE_CHAN;

typedef struct
{
    EUINT32 key;
    EUINT32 ssi;
    ECHAR snApi;
}GRE_CHAN_SYN;






/************************************************************************
                            函数申明
*************************************************************************/
/************************************************************************
  Function：       VoiceCarrierInit
  Description：    初始化RTP语音通讯相关资源，调试台与BSC共用
  Input：          rtpPort: RTP端口号, 0: 采用默认值
				   rtpIp: RTP IP地址, 0: 采用默认值
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others:          无
************************************************************************/
extern EINT32 VoiceCarrierInit(EUINT16 rtpPort, EUINT32 rtpIp);

/************************************************************************
  Function：       OpenBearMultiSock
  Description：    设置BSC rtp socket的组播发送接口地址及发送组播包的特性
  Input：          无
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern EINT32 OpenBearMultiSock(void);

/************************************************************************
  Function：       CreateRtpChannel
  Description：    在RTP通道表中增加一个新的通道，相应的修改HASH表
  Input：
  callId: 通道标识号
  endPoint：被创建RTP Channel对应的endpoint，低字节代表timeslot，高字节代表BSR。
  multicastIpAddr：被创建RTP Channel的组播地址。
  mode：0-inactive，不发送也不接收RTP包；1-sendonly，只发送RTP包；2-recvonly，只接收RTP包；3-sendrecv，即发送也接收RTP包。
  loop：0-不环回；1-loopback，endpoint的上行环回到endpoint的下行；2-hairpin，从endpoint的上行环回到sndEndpoint的下行。（只有当mode为sendonly或sendrecv时，loop才有意义。）
  sndEndPoint：0-无意义，非0-为第2个endpoint标识，低字节代表timeslot，高字节代表BSR。（只有当loop为hairpin时，sndEndPoint才有意义。
  Output：         无
  Return：         成功：ETOK, 已存在：ETEXIST, 失败：ETERROR
  Others：         无
************************************************************************/
EINT32 CreateRtpChannel(EUINT32 callId, EUINT16 endPoint, EUINT32 multicastIpAddr,
                 ECHAR mode, ECHAR loop, EUINT16 sndEndPoint);

/************************************************************************
  Function：       ModifyRtpChannel
  Description：    修改组播地址为multicastIpAddr的RTP通道的mode、loop
  Input：
      callId: 通道标识号（未用）
      endPoint：被创建RTP Channel对应的endpoint，低字节代表timeslot，高字节代表BSR。（未用）
      multicastIpAddr：被创建RTP Channel的组播地址。
      mode：0-inactive，不发送也不接收RTP包；1-sendonly，只发送RTP包；2-recvonly，只接收RTP包；3-sendrecv，即发送也接收RTP包。
      loop：0-不环回；1-loopback，endpoint的上行环回到endpoint的下行；2-hairpin，从endpoint的上行环回到sndEndpoint的下行。（只有当mode为sendonly或sendrecv时，loop才有意义。）
      sndEndPoint：0-无意义，非0-为第2个endpoint标识，低字节代表timeslot，高字节代表BSR。只有当loop为hairpin时，sndEndPoint才有意义。（未用）
  Output：         无
  Return：         成功：ETOK 失败：ETERROR
  Others：         无
************************************************************************/
EINT32 ModifyRtpChannel(EUINT32 callId, EUINT16 endPoint, EUINT32 multicastIpAddr,
                 ECHAR mode, ECHAR loop, EUINT16 sndEndPoint);

/************************************************************************
  Function：       DeleteRTPChannel
  Description：    从RTP通道表中删除一个通道，相应的修改HASH表
  Input：
  callId: 通道标识号
  endPoint：被创建RTP Channel对应的endpoint，低字节代表timeslot，高字节代表BSR。
  multicastIpAddr：被创建RTP Channel的组播地址。
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 DeleteRTPChannel(EUINT32 callId, EUINT16 endPoint, EUINT32 multicastIpAddr);

/************************************************************************
  Function：       DeleteAllChannel
  Description：    从RTP通道表中删除所有通道，相应的修改HASH表
  Input：          无
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern void DeleteAllChannel(void);

/************************************************************************
Function：       getRtpChanTbl
Description：	 获取RTP通道表中的有效通道
Input：          无
Output：         sendTblBuf:保存有效通道表的缓冲区
                 pCount:有效通道表的数量
Return：         ETERROR:无有效通道，ETOK:有有效通道
Others：         无
************************************************************************/
extern EINT32 getRtpChanTbl(ECHAR *sendTblBuf,EUINT32 *pCount);

/*----------------------------ntpClient--------------------------------*/
/************************************************************************
  Function：       SetNtpServer
  Description：    配置NTP服务器地址
  Input：          ipAddr: NTP SERVER的IP地址；ntpSvrType：1:主用，2：备用
  Output：         无
  Return：         成功ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 SetNtpServer(EUINT32 ipAddr, EINT32 ntpSvrType);

/************************************************************************
  Function：       InitNtpClient
  Description：    初始化Ntp客户端，周期性的从NTP服务器获取时间并更正本地时间
  Input：          无
  Output：         无
  Return：         成功ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 InitNtpClient(void);

/************************************************************************
  Function：       EnableNtpClient
  Description：    开启NTP客户端线程
  Input：          无
  Output：         无
  Return：         成功ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 EnableNtpClient(void);

/************************************************************************
  Function：       DisableNtpClient
  Description：    终止NTP客户端线程
  Input：          无
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern void DisableNtpClient(void);

/************************************************************************
                        调度台承载使用函数
************************************************************************/
/************************************************************************
  Function：       CreateSwitchRtpChannel
  Description：    创建调度台RTP通道
  Input：          multicastIpAddr: 组播地址
  Output：         无
  Return：         成功：通道句柄, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 CreateSwitchRtpChannel(EUINT32 multicastIpAddr);

/*ptt_off 到ptt_on时转换*/
extern void ResetSwitchRtpChan(EUINT32 multicastIpAddr);

/************************************************************************
  Function：       DeleteSwitchRtpChannel
  Description：    删除调度台RTP通道
  Input：          chanHdl: 通道句柄, 由CreateSwitchChannel()返回
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 DeleteSwitchRtpChannel(EINT32 chanHdl);

/************************************************************************
  Function：       SendSwitchRtpPkg
  Description：    调试台向指定通道发送RTP数据包
  Input：          chanHdl: 通道句柄, 由CreateSwitchChannel()返回
                   trafType: 数据类型
                   pData: 数据指针
                   len: 数据长度
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 SendSwitchRtpPkg(EINT32 chanHdl, ECHAR trafType, ECHAR *pData, EUINT32 len);

/************************************************************************
  Function：       SetSequenceFirstFlag
  Description：    当通道收发属性变化后，数据包的序列号将不再连续，因此应清零数据包序列记录值
  Input：          chanHdl: 通道句柄, 由CreateSwitchChannel()返回
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern void SetSequenceFirstFlag(EINT32 chanHdl);

/************************************************************************
  Function：       FindChanHdlByMultiIp
  Description：    根据组播地址查找chanHdl，提供调度台
  Input：          multicastIpAddr: 组播地址
  Output：         无
  Return：         成功：通道句柄, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 FindChanHdlByMultiIp(EUINT32 multicastIpAddr);


/************************************************************************
  Function：       SetSndDownFunction
  Description：    设置调试台RTP数据包处理函数
  Input：          function: RECV_Switch_RTP_FUNCTION类型的语音数据包发送函数
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
//RTP数据包的下层处理函数指针类型
typedef EINT32 (* RECV_Switch_RTP_FUNCTION)(EINT32 chanHdl, EUCHAR trafType, ECHAR *pData, EUINT32 len);
extern EINT32 SetSndDownFunction(RECV_Switch_RTP_FUNCTION function);

typedef EINT32 (* RECV_VIDEO_MULTI_RTP_FUNCTION)(EUINT32 callId, EUCHAR trafType, ECHAR *pData, EUINT32 len, EUINT8 markFlag);
extern EINT32 SetVideoMultiRtpFun(RECV_VIDEO_MULTI_RTP_FUNCTION function);
typedef EINT32 (* RECV_VIDEO_UNI_RTP_FUNCTION)(EUINT32 callId, EUCHAR trafType, ECHAR *pData, EUINT32 len, EUINT8 markFlag);
extern EINT32 SetVideoUniRtpFun(RECV_VIDEO_UNI_RTP_FUNCTION function);




typedef  EINT32 (* recvGreFunc_t)(EUINT32 key, EUINT32 seqNum, ECHAR *pData, EUINT32 len);
/************************************************************************
Function：       RegGreRecvFunc
Description：    注册处理ECN侧数据的接口函数
Input：			 recvGreFunc_t 需要注册的函数指针
Output：         无
Return：         成功：ETOK, 失败：ETERROR
Others：         无
************************************************************************/
extern EINT32 RegGreRecvFunc(recvGreFunc_t function);

/************************************************************************
Function：       CreateGreChan
Description：    增加一个有效Gre通道表项
Input：          ssi:空口协议的ssi，snApi:sndcp协议的snApi，key:gre协议key，pBuf：gre通道保存的有用信息，len:pBuf的长度
Output：         无
Return：         成功：ETOK, 失败：ETERROR
Others：         如果有效通道中已经存在具有ssi，snApi或key的通道，则将他们先删除，然后再建立
************************************************************************/
extern EINT32 CreateGreChan(EUINT32 ssi, ECHAR snApi, EUINT32 key, ECHAR *pBuf, EUINT32 len);

/************************************************************************
Function：       DelGreChanByKey
Description：    根据key，删除相关的GRE通道,包括通道中与ssi和snApi相匹配的通道也删除
Input：          key：要删除的GRE通道key
Output：         无
Return：         成功：ETOK,  失败：ETERROR
Others：         无
************************************************************************/
extern EINT32 DelGreChanByKey (EUINT32 key);

/************************************************************************
Function：       DelGreChanBySsiSnApi
Description：    根据ssi/snApi，删除相关的GRE通道,包括通道中与key相匹配的通道也删除
Input：          key：要删除的GRE通道key
Output：         无
Return：         成功：ETOK,  失败：ETERROR
Others：         无
************************************************************************/
extern EINT32 DelGreChanBySsiSnapi(EUINT32 ssi, ECHAR snApi);


/************************************************************************
Function：       DelGreChanBySsi
Description：    根据ssi，删除相关的GRE通道,包括通道中与key相匹配的通道也删除
Input：          key：要删除的GRE通道key
Output：         无
Return：         成功：ETOK,  失败：ETERROR
Others：         无
************************************************************************/
extern EINT32 DelGreChanBySsi(EUINT32 ssi);


/************************************************************************
Function：       GetPreGreChanByKey
Description：    获取和key值相同的gre通道
Input：          key：Gre通道key值
Output：         pGreChanIn: 保存通道信息的指针
Return：         成功：ETOK, 失败：NULL
Others：         已进行信号量保护
************************************************************************/
extern EINT32 GetGreChanByKey(EUINT32 key, GRE_CHAN *pGreChanIn);

/************************************************************************
Function：       GetGreChanBySsi
Description：    获取和ssi/snApi相同的gre通道
Input：          ssi：要查找的通道ssi，snApi：要查找通道的snApi
Output：         pGreChanIn: 保存通道信息的指针
Return：         成功：ETOK, 失败：NULL
Others：         已进行信号量保护
************************************************************************/
extern EINT32 GetGreChanBySsi(EUINT32 ssi, ECHAR snApi, GRE_CHAN *pGreChan);
/************************************************************************
Function：       FindGreChanByKey
Description：    判断gre通道是否备创建
Input：          key：Gre通道key值
Output：         无
Return：         成功：ETOK, 失败：ETERROR
Others：         已经信号量保护
************************************************************************/
extern EINT32 FindGreChanByKey(EUINT32 key);

/************************************************************************
Function：       FindGreKeyBySsi
Description：    查找ssi/snApi通道的key值
Input：          ssi：Gre通道ssi，snApi：Gre通道的snApi
Output：         无
Return：         成功：要查找的key值, 失败：ETERROR
Others：         已经信号量保护
************************************************************************/
extern EINT32 FindGreKeyBySsi(EUINT32 ssi, ECHAR snApi);

/************************************************************************
Function：       SendGreFunc
Description：    向ECN发送数据
Input：			 key:gre key，seqnum：时序号，pData:向ECN端发送的数据，len:pData的长度
Output：         无
Return：         成功：ETOK, 失败：ETERROR
Others：        此模块有其它模块调用，将从MS端接收到的数据经处理发向ECN端,提供给B1接口
************************************************************************/
extern EINT32 SendGreFunc (EUINT32 key, EUINT32 seqNum, ECHAR *pData, EUINT16 len);

/************************************************************************
Function：       GetGreChanTable
Description：    获取gre通道表
Input：
Output：         无
Return：         成功：ETOK, 失败：ETERROR
Others：
************************************************************************/
extern EINT32 GetGreChanTable(ECHAR *pBuf, EUINT32 *pCount);

//add by jinjing
#ifdef WINDOWS
/************************************************************************
  Function：       CreateVideoMulRtpChan
  Description：    创建rtp通道
  Input：          callId: callId     multiIp:组播地址
                   mode: 1:send  2:recv  3:send & recv
  Return：         成功: ETOK    失败: ETERROR
************************************************************************/

EINT32 CreateVideoMulRtpChan(EUINT32 callId, EUINT32 multiIp, EUINT8 mode);

/************************************************************************
  Function：       ModifyVideoMulRtpMode
  Description：    修改rtp 通道mode
  Input：          multiIp:组播地址
                   mode: 1:send  2:recv  3:send & recv
  Return：         成功: ETOK    失败: ETERROR
************************************************************************/

EINT32 ModifyVideoMulRtpMode(EUINT32 multiIp, EINT8 mode);

/************************************************************************
  Function：       DelVideoMulRtpChan
  Description：    删除rtp 通道
  Input：          multiIp:组播地址
  Return：         成功: ETOK    失败: ETERROR
************************************************************************/

EINT32 DelVideoMulRtpChan(EUINT32 multiIp);

/************************************************************************
  Function：       SendVideoMulRtpPkg
  Description：    发送组播包
  Input：          multiIp: 组播地址   trafType:类型 (1:h264)
                   pData:数据指针   len:长度    markFlag:rtp包头中的mark
  Return：         成功: ETOK    失败: ETERROR
************************************************************************/

EINT32 SendVideoMulRtpPkg(EUINT32 multiIp, EUINT8 trafType, EINT8 *pData, EUINT32 len, EUINT8 markFlag);

/************************************************************************
  Function：       CreateVideoUniRtpChan
  Description：    创建rtp通道
  Input：          callId: callId     multiIp:组播地址
                   mode: 1:send  2:recv  3:send & recv
  Return：         成功: ETOK    失败: ETERROR
************************************************************************/

EINT32 CreateVideoUniRtpChan(EUINT32 callId, EUINT32 multiIp, EUINT8 mode);

/************************************************************************
  Function：       ModifyVideoUniRtpMode
  Description：    修改rtp 通道mode
  Input：          multiIp:组播地址
                   mode: 1:send  2:recv  3:send & recv
  Return：         成功: ETOK    失败: ETERROR
************************************************************************/

EINT32 ModifyVideoUniRtpMode(EUINT32 multiIp, EUINT8 mode);

/************************************************************************
  Function：       DelVideoUniRtpChan
  Description：    删除rtp 通道
  Input：          multiIp:组播地址
  Return：         成功: ETOK    失败: ETERROR
************************************************************************/

EINT32 DelVideoUniRtpChan(EUINT32 multiIp);

/************************************************************************
  Function：       SendVideoUniRtpPkg
  Description：    发送单播包
  Input：          multiIp: 组播地址   trafType:类型 (1:h264)
                   pData:数据指针   len:长度    markFlag:rtp包头中的mark
  Return：         成功: ETOK    失败: ETERROR
************************************************************************/

EINT32 SendVideoUniRtpPkg(EUINT32 multiIp, EUINT8 trafType, EINT8 *pData, EUINT32 len, EUINT8 markFlag);



#endif
#ifdef LARGE_CALL_DEBUG

/************************************************************************
  Function：       InitBearLargeCallModule
  Description：  初始化大呼模块
  Input：
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 InitBearLargeCallModule();

/************************************************************************
  Function：       SendLargeCallRtpPkg
  Description：   通过large call rtp 通道发送组播数据
  Input：          	callId: 通道句柄, 由CreateSwitchChannel()返回
                   		trafType: 数据类型
                   		pData: 数据指针
                  		 len: 数据长度
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 SendLargeCallRtpPkg(EINT32 callId, ECHAR trafType, ECHAR *pData, EUINT32 len);

/************************************************************************
  Function：       LargeCallCreateRtpChan
  Description：   为大量呼叫提供的rtp创建借口
  Input：      	callid: 通道的标志
  				mode:通道的属性1，只发送，2只接受
  				multicast:组播地址
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern EINT32 CreateLargeCallRtpChan(EUINT16 callId, EUINT32 multicastIp, ECHAR mode);
/************************************************************************
  Function：       DelLargeCallAllRtpChan
  Description： 删除所有的large call rtp通道
  Input：
  				multicastIp:组播地址
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern EINT32 DelLargeCallAllRtpChan();
/************************************************************************
  Function：       DelLargeCallRtpChanByCallId
  Description：通过callid删除large call rtp 通道
  Input：
  				multicastIp:组播地址
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern EINT32 DelLargeCallRtpChanByCallId(ECHAR callId);
/************************************************************************
  Function：       DelLargeCallRtpChanByMulticast
  Description：  通过组播地址删除large call rtp 通道
  Input：
  				multicastIp:组播地址
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern EINT32 DelLargeCallRtpChanByMulticast(EUINT32 multicastIp);
#endif

#ifdef LIB_PSS
//中心基站处理rtp单播包下行处理函数结构
typedef EINT32 (*DEAL_UNITCAST_RTP_PKT_FUNC)(ECHAR *pData, EUINT16 length, EUCHAR bsrId, EUCHAR slot, EUINT type);

/************************************************************************
  Function：       SendPrimitivePktToSyncBsc
  Description：   向同频同播基站发送rtp信令包
  Input：            pbuf: 发送的buf结构, len发送数据长度
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 SendPrimitivePktToSyncBsc(ECHAR *pBuf, EUINT16 len);

/************************************************************************
  Function：       	SetCenterBscFrameSeq
  Description：   从基站测获取同步帧序号
  Input：          	中心基站同步帧号

  Output：         	无
  Return：
				无
  Others：         	无
************************************************************************/
extern void SetCenterBscFrameSeq(EUINT32 seq);


/************************************************************************
  Function：       SelectRightRtpPkt
  Description：  从单播rtp包控制列表中选择合适的rtp数据包发送
  Input：            无
  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern void SendCenterBsRtpPkt(EUINT16 slot);

/************************************************************************
  Function：       	SetDealUnitcastRtpPktFunc
  Description：    设置单播包处理接口
  Input：
  				func:单播包处理函数
  Output：         	无
  Return：
  				ETOK:成功
  				ETERROR:失败
  Others：         	无
************************************************************************/
extern EINT32 SetDealUnitcastRtpPktFunc(DEAL_UNITCAST_RTP_PKT_FUNC func);

#endif

#ifdef LIB_PDT

//同频同播基站处理信令组播包函数结构
typedef EINT32 (*DEAL_PRIMITIVE_PKT_FUNC)(ECHAR *pBuf, EUINT16 bufLen);
/************************************************************************
  Function：       	SetDealPrimitivePktFunc
  Description：    设置同频同播基站侧处理信令的数据包
  Input：
  				func: 处理接口
  Output：         	无
  Return：
  				ETOK:成功
  				ETERROR:失败
  Others：         	无
************************************************************************/
extern EINT32 SetDealPrimitivePktFunc(DEAL_PRIMITIVE_PKT_FUNC func);


#endif
#ifdef __cplusplus
}
#endif

#endif //__BEARBSC_H__

