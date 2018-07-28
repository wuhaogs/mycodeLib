/************************************************************************
Copyright (C), 2009-2010, Eastcom.
File name��      socketLib.h
Author��          huangzd
Date��             09.7.17
Description��    �Բ�ͬ����ϵͳ��socket�ӿڽ��з�װ�����ϲ��ṩͳһsocket�ӿ�
Others��         ��
  *************************************************************************/
#ifndef __BEARBSC_H__
#define __BEARBSC_H__
#ifdef __cplusplus
extern "C" {
#endif
/************************************************************************
                            ���õ�ͷ�ļ�
*************************************************************************/
#include "sys.h"

/************************************************************************
                            �궨��
*************************************************************************/
//#define    ESOCK_STREAM    1        //TCP
//#define    ESOCK_DGRAM     2        //UDP
//#define    ESOCK_RAW       3

#define    SERVER_MAX_CONNECTIONS    10    //��������������

enum {LOOP_OFF=0, LOOP_SELF, LOOP_OTHER};                             //�������ݰ���������
enum {
		//���Ӳ�ͬ���ʵ�·
        TETRA_ACELP=1,
   		TETRA_TCH24,
    	TETRA_TCH48,
    	TETRA_TCH72,
        /*֧��PDT*/
        PDT_SYNC_SIG,
        PDT_SELP_VOICE,
        PDT_AMBE_VOICE,
        PDT_SELP_SYNCSIG,
        PDT_AMBE_SYNCSIG,
        A_LAW_PCM, //10

        //����AMR���ݵ�
        /*�����Ⱥ���*/
        BWT_AMR = 11,
        BWT_ACELP_AMR = 12,
        BWT_AMBE_AMR = 13,
        BWT_AMBE_AMR_SYNCSIG = 14,

        /*pdt acelp + ambe*/
        PDT_ACELP_AMBE_VOICE = 15,
        PDT_ACELP_AMBE_SYNCSIG = 16,
        /*PDT 712���*/
        PDT_CFG_G712_VOICE = 21,
        PDT_CFG_G712_SYNCSIG = 22,
        PDT_CFG_G712_ACELP_VOICE = 23,
        PDT_CFG_G712_ACELP_SYNCSIG = 24,
        PDT_CFG_G712_AMR_VOICE = 25,
        PDT_CFG_G712_AMR_SYNCSIG = 26,
        PDT_CFG_ACELP_VOICE = 27,
        PDT_CFG_AMR_VOICE = 28

    };            //�������ݰ�����

enum
{
    TRAF_TYPE_H264 = 1,
}; // ��Ƶ���ݰ�����

enum {INACTIVE=0x00, SENDONLY=0x001, RCEVONLY=0x02, SENDRECV=0x03};   //RTPͨ������

/*ͬƵͬ����վ���Ͷ���*/
#ifdef LIB_PDT
enum{PDT_COMMON_BS = 0, PDT_SYNC_BS = 1};
#endif
#define PRIMA_NTP_SVR 1         //����SetNtpServer(), ����ѡ�����
#define SECOND_NTP_SVR 2

#define ETEXIST 2               //CreateRtpChannel()�ķ���ֵ֮һ������Ҫ������RTPͨ���Ѿ�����

#define BSC_BEAR_STAT           //Statistic switch

typedef struct rtp_chan_need		//�跢�͵�RTPͨ����Ľṹ
{
    EUINT32 callId;					//������
    EUCHAR mode;
    EUCHAR loop;
    EUINT16 reserve;		//����ԭ��
    EUINT16 endPoint;
    EUINT16 sndPoint;
    //PHY_SLOT upLink;
    //PHY_SLOT downLink;
    EUINT32 multicastIpAddr;		//�������鲥��ַ
}RTP_CHAN_NEED;

#ifndef SIZE_MS_BUF
#define SIZE_MS_BUF 64
#endif

typedef struct gre_chan_t
{
    EUINT32 greKey;
    EUINT32 ssi;				//ͨ����ssiֵ
    struct gre_chan_t *pKeyNext;	//��keyΪ�ؼ�������������ָ��
    struct gre_chan_t *pSsiNext;    //��ssi/saApiΪ�ؼ�������������ָ��
    EUINT32 length;               //arrMsBuf���ݵĴ�С
    ECHAR arrMsBuf[SIZE_MS_BUF];    //�����洢greͨ���Ŀտ���Ϣ
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
                            ��������
*************************************************************************/
/************************************************************************
  Function��       VoiceCarrierInit
  Description��    ��ʼ��RTP����ͨѶ�����Դ������̨��BSC����
  Input��          rtpPort: RTP�˿ں�, 0: ����Ĭ��ֵ
				   rtpIp: RTP IP��ַ, 0: ����Ĭ��ֵ
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others:          ��
************************************************************************/
extern EINT32 VoiceCarrierInit(EUINT16 rtpPort, EUINT32 rtpIp);

/************************************************************************
  Function��       OpenBearMultiSock
  Description��    ����BSC rtp socket���鲥���ͽӿڵ�ַ�������鲥��������
  Input��          ��
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern EINT32 OpenBearMultiSock(void);

/************************************************************************
  Function��       CreateRtpChannel
  Description��    ��RTPͨ����������һ���µ�ͨ������Ӧ���޸�HASH��
  Input��
  callId: ͨ����ʶ��
  endPoint��������RTP Channel��Ӧ��endpoint�����ֽڴ���timeslot�����ֽڴ���BSR��
  multicastIpAddr��������RTP Channel���鲥��ַ��
  mode��0-inactive��������Ҳ������RTP����1-sendonly��ֻ����RTP����2-recvonly��ֻ����RTP����3-sendrecv��������Ҳ����RTP����
  loop��0-�����أ�1-loopback��endpoint�����л��ص�endpoint�����У�2-hairpin����endpoint�����л��ص�sndEndpoint�����С���ֻ�е�modeΪsendonly��sendrecvʱ��loop�������塣��
  sndEndPoint��0-�����壬��0-Ϊ��2��endpoint��ʶ�����ֽڴ���timeslot�����ֽڴ���BSR����ֻ�е�loopΪhairpinʱ��sndEndPoint�������塣
  Output��         ��
  Return��         �ɹ���ETOK, �Ѵ��ڣ�ETEXIST, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
EINT32 CreateRtpChannel(EUINT32 callId, EUINT16 endPoint, EUINT32 multicastIpAddr,
                 ECHAR mode, ECHAR loop, EUINT16 sndEndPoint);

/************************************************************************
  Function��       ModifyRtpChannel
  Description��    �޸��鲥��ַΪmulticastIpAddr��RTPͨ����mode��loop
  Input��
      callId: ͨ����ʶ�ţ�δ�ã�
      endPoint��������RTP Channel��Ӧ��endpoint�����ֽڴ���timeslot�����ֽڴ���BSR����δ�ã�
      multicastIpAddr��������RTP Channel���鲥��ַ��
      mode��0-inactive��������Ҳ������RTP����1-sendonly��ֻ����RTP����2-recvonly��ֻ����RTP����3-sendrecv��������Ҳ����RTP����
      loop��0-�����أ�1-loopback��endpoint�����л��ص�endpoint�����У�2-hairpin����endpoint�����л��ص�sndEndpoint�����С���ֻ�е�modeΪsendonly��sendrecvʱ��loop�������塣��
      sndEndPoint��0-�����壬��0-Ϊ��2��endpoint��ʶ�����ֽڴ���timeslot�����ֽڴ���BSR��ֻ�е�loopΪhairpinʱ��sndEndPoint�������塣��δ�ã�
  Output��         ��
  Return��         �ɹ���ETOK ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
EINT32 ModifyRtpChannel(EUINT32 callId, EUINT16 endPoint, EUINT32 multicastIpAddr,
                 ECHAR mode, ECHAR loop, EUINT16 sndEndPoint);

/************************************************************************
  Function��       DeleteRTPChannel
  Description��    ��RTPͨ������ɾ��һ��ͨ������Ӧ���޸�HASH��
  Input��
  callId: ͨ����ʶ��
  endPoint��������RTP Channel��Ӧ��endpoint�����ֽڴ���timeslot�����ֽڴ���BSR��
  multicastIpAddr��������RTP Channel���鲥��ַ��
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 DeleteRTPChannel(EUINT32 callId, EUINT16 endPoint, EUINT32 multicastIpAddr);

/************************************************************************
  Function��       DeleteAllChannel
  Description��    ��RTPͨ������ɾ������ͨ������Ӧ���޸�HASH��
  Input��          ��
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern void DeleteAllChannel(void);

/************************************************************************
Function��       getRtpChanTbl
Description��	 ��ȡRTPͨ�����е���Чͨ��
Input��          ��
Output��         sendTblBuf:������Чͨ����Ļ�����
                 pCount:��Чͨ���������
Return��         ETERROR:����Чͨ����ETOK:����Чͨ��
Others��         ��
************************************************************************/
extern EINT32 getRtpChanTbl(ECHAR *sendTblBuf,EUINT32 *pCount);

/*----------------------------ntpClient--------------------------------*/
/************************************************************************
  Function��       SetNtpServer
  Description��    ����NTP��������ַ
  Input��          ipAddr: NTP SERVER��IP��ַ��ntpSvrType��1:���ã�2������
  Output��         ��
  Return��         �ɹ��oETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 SetNtpServer(EUINT32 ipAddr, EINT32 ntpSvrType);

/************************************************************************
  Function��       InitNtpClient
  Description��    ��ʼ��Ntp�ͻ��ˣ������ԵĴ�NTP��������ȡʱ�䲢��������ʱ��
  Input��          ��
  Output��         ��
  Return��         �ɹ��oETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 InitNtpClient(void);

/************************************************************************
  Function��       EnableNtpClient
  Description��    ����NTP�ͻ����߳�
  Input��          ��
  Output��         ��
  Return��         �ɹ��oETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 EnableNtpClient(void);

/************************************************************************
  Function��       DisableNtpClient
  Description��    ��ֹNTP�ͻ����߳�
  Input��          ��
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern void DisableNtpClient(void);

/************************************************************************
                        ����̨����ʹ�ú���
************************************************************************/
/************************************************************************
  Function��       CreateSwitchRtpChannel
  Description��    ��������̨RTPͨ��
  Input��          multicastIpAddr: �鲥��ַ
  Output��         ��
  Return��         �ɹ���ͨ�����, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 CreateSwitchRtpChannel(EUINT32 multicastIpAddr);

/*ptt_off ��ptt_onʱת��*/
extern void ResetSwitchRtpChan(EUINT32 multicastIpAddr);

/************************************************************************
  Function��       DeleteSwitchRtpChannel
  Description��    ɾ������̨RTPͨ��
  Input��          chanHdl: ͨ�����, ��CreateSwitchChannel()����
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 DeleteSwitchRtpChannel(EINT32 chanHdl);

/************************************************************************
  Function��       SendSwitchRtpPkg
  Description��    ����̨��ָ��ͨ������RTP���ݰ�
  Input��          chanHdl: ͨ�����, ��CreateSwitchChannel()����
                   trafType: ��������
                   pData: ����ָ��
                   len: ���ݳ���
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 SendSwitchRtpPkg(EINT32 chanHdl, ECHAR trafType, ECHAR *pData, EUINT32 len);

/************************************************************************
  Function��       SetSequenceFirstFlag
  Description��    ��ͨ���շ����Ա仯�����ݰ������кŽ��������������Ӧ�������ݰ����м�¼ֵ
  Input��          chanHdl: ͨ�����, ��CreateSwitchChannel()����
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern void SetSequenceFirstFlag(EINT32 chanHdl);

/************************************************************************
  Function��       FindChanHdlByMultiIp
  Description��    �����鲥��ַ����chanHdl���ṩ����̨
  Input��          multicastIpAddr: �鲥��ַ
  Output��         ��
  Return��         �ɹ���ͨ�����, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 FindChanHdlByMultiIp(EUINT32 multicastIpAddr);


/************************************************************************
  Function��       SetSndDownFunction
  Description��    ���õ���̨RTP���ݰ�������
  Input��          function: RECV_Switch_RTP_FUNCTION���͵��������ݰ����ͺ���
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
//RTP���ݰ����²㴦����ָ������
typedef EINT32 (* RECV_Switch_RTP_FUNCTION)(EINT32 chanHdl, EUCHAR trafType, ECHAR *pData, EUINT32 len);
extern EINT32 SetSndDownFunction(RECV_Switch_RTP_FUNCTION function);

typedef EINT32 (* RECV_VIDEO_MULTI_RTP_FUNCTION)(EUINT32 callId, EUCHAR trafType, ECHAR *pData, EUINT32 len, EUINT8 markFlag);
extern EINT32 SetVideoMultiRtpFun(RECV_VIDEO_MULTI_RTP_FUNCTION function);
typedef EINT32 (* RECV_VIDEO_UNI_RTP_FUNCTION)(EUINT32 callId, EUCHAR trafType, ECHAR *pData, EUINT32 len, EUINT8 markFlag);
extern EINT32 SetVideoUniRtpFun(RECV_VIDEO_UNI_RTP_FUNCTION function);




typedef  EINT32 (* recvGreFunc_t)(EUINT32 key, EUINT32 seqNum, ECHAR *pData, EUINT32 len);
/************************************************************************
Function��       RegGreRecvFunc
Description��    ע�ᴦ��ECN�����ݵĽӿں���
Input��			 recvGreFunc_t ��Ҫע��ĺ���ָ��
Output��         ��
Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
Others��         ��
************************************************************************/
extern EINT32 RegGreRecvFunc(recvGreFunc_t function);

/************************************************************************
Function��       CreateGreChan
Description��    ����һ����ЧGreͨ������
Input��          ssi:�տ�Э���ssi��snApi:sndcpЭ���snApi��key:greЭ��key��pBuf��greͨ�������������Ϣ��len:pBuf�ĳ���
Output��         ��
Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
Others��         �����Чͨ�����Ѿ����ھ���ssi��snApi��key��ͨ������������ɾ����Ȼ���ٽ���
************************************************************************/
extern EINT32 CreateGreChan(EUINT32 ssi, ECHAR snApi, EUINT32 key, ECHAR *pBuf, EUINT32 len);

/************************************************************************
Function��       DelGreChanByKey
Description��    ����key��ɾ����ص�GREͨ��,����ͨ������ssi��snApi��ƥ���ͨ��Ҳɾ��
Input��          key��Ҫɾ����GREͨ��key
Output��         ��
Return��         �ɹ���ETOK,  ʧ�ܣ�ETERROR
Others��         ��
************************************************************************/
extern EINT32 DelGreChanByKey (EUINT32 key);

/************************************************************************
Function��       DelGreChanBySsiSnApi
Description��    ����ssi/snApi��ɾ����ص�GREͨ��,����ͨ������key��ƥ���ͨ��Ҳɾ��
Input��          key��Ҫɾ����GREͨ��key
Output��         ��
Return��         �ɹ���ETOK,  ʧ�ܣ�ETERROR
Others��         ��
************************************************************************/
extern EINT32 DelGreChanBySsiSnapi(EUINT32 ssi, ECHAR snApi);


/************************************************************************
Function��       DelGreChanBySsi
Description��    ����ssi��ɾ����ص�GREͨ��,����ͨ������key��ƥ���ͨ��Ҳɾ��
Input��          key��Ҫɾ����GREͨ��key
Output��         ��
Return��         �ɹ���ETOK,  ʧ�ܣ�ETERROR
Others��         ��
************************************************************************/
extern EINT32 DelGreChanBySsi(EUINT32 ssi);


/************************************************************************
Function��       GetPreGreChanByKey
Description��    ��ȡ��keyֵ��ͬ��greͨ��
Input��          key��Greͨ��keyֵ
Output��         pGreChanIn: ����ͨ����Ϣ��ָ��
Return��         �ɹ���ETOK, ʧ�ܣ�NULL
Others��         �ѽ����ź�������
************************************************************************/
extern EINT32 GetGreChanByKey(EUINT32 key, GRE_CHAN *pGreChanIn);

/************************************************************************
Function��       GetGreChanBySsi
Description��    ��ȡ��ssi/snApi��ͬ��greͨ��
Input��          ssi��Ҫ���ҵ�ͨ��ssi��snApi��Ҫ����ͨ����snApi
Output��         pGreChanIn: ����ͨ����Ϣ��ָ��
Return��         �ɹ���ETOK, ʧ�ܣ�NULL
Others��         �ѽ����ź�������
************************************************************************/
extern EINT32 GetGreChanBySsi(EUINT32 ssi, ECHAR snApi, GRE_CHAN *pGreChan);
/************************************************************************
Function��       FindGreChanByKey
Description��    �ж�greͨ���Ƿ񱸴���
Input��          key��Greͨ��keyֵ
Output��         ��
Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
Others��         �Ѿ��ź�������
************************************************************************/
extern EINT32 FindGreChanByKey(EUINT32 key);

/************************************************************************
Function��       FindGreKeyBySsi
Description��    ����ssi/snApiͨ����keyֵ
Input��          ssi��Greͨ��ssi��snApi��Greͨ����snApi
Output��         ��
Return��         �ɹ���Ҫ���ҵ�keyֵ, ʧ�ܣ�ETERROR
Others��         �Ѿ��ź�������
************************************************************************/
extern EINT32 FindGreKeyBySsi(EUINT32 ssi, ECHAR snApi);

/************************************************************************
Function��       SendGreFunc
Description��    ��ECN��������
Input��			 key:gre key��seqnum��ʱ��ţ�pData:��ECN�˷��͵����ݣ�len:pData�ĳ���
Output��         ��
Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
Others��        ��ģ��������ģ����ã�����MS�˽��յ������ݾ�������ECN��,�ṩ��B1�ӿ�
************************************************************************/
extern EINT32 SendGreFunc (EUINT32 key, EUINT32 seqNum, ECHAR *pData, EUINT16 len);

/************************************************************************
Function��       GetGreChanTable
Description��    ��ȡgreͨ����
Input��
Output��         ��
Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
Others��
************************************************************************/
extern EINT32 GetGreChanTable(ECHAR *pBuf, EUINT32 *pCount);

//add by jinjing
#ifdef WINDOWS
/************************************************************************
  Function��       CreateVideoMulRtpChan
  Description��    ����rtpͨ��
  Input��          callId: callId     multiIp:�鲥��ַ
                   mode: 1:send  2:recv  3:send & recv
  Return��         �ɹ�: ETOK    ʧ��: ETERROR
************************************************************************/

EINT32 CreateVideoMulRtpChan(EUINT32 callId, EUINT32 multiIp, EUINT8 mode);

/************************************************************************
  Function��       ModifyVideoMulRtpMode
  Description��    �޸�rtp ͨ��mode
  Input��          multiIp:�鲥��ַ
                   mode: 1:send  2:recv  3:send & recv
  Return��         �ɹ�: ETOK    ʧ��: ETERROR
************************************************************************/

EINT32 ModifyVideoMulRtpMode(EUINT32 multiIp, EINT8 mode);

/************************************************************************
  Function��       DelVideoMulRtpChan
  Description��    ɾ��rtp ͨ��
  Input��          multiIp:�鲥��ַ
  Return��         �ɹ�: ETOK    ʧ��: ETERROR
************************************************************************/

EINT32 DelVideoMulRtpChan(EUINT32 multiIp);

/************************************************************************
  Function��       SendVideoMulRtpPkg
  Description��    �����鲥��
  Input��          multiIp: �鲥��ַ   trafType:���� (1:h264)
                   pData:����ָ��   len:����    markFlag:rtp��ͷ�е�mark
  Return��         �ɹ�: ETOK    ʧ��: ETERROR
************************************************************************/

EINT32 SendVideoMulRtpPkg(EUINT32 multiIp, EUINT8 trafType, EINT8 *pData, EUINT32 len, EUINT8 markFlag);

/************************************************************************
  Function��       CreateVideoUniRtpChan
  Description��    ����rtpͨ��
  Input��          callId: callId     multiIp:�鲥��ַ
                   mode: 1:send  2:recv  3:send & recv
  Return��         �ɹ�: ETOK    ʧ��: ETERROR
************************************************************************/

EINT32 CreateVideoUniRtpChan(EUINT32 callId, EUINT32 multiIp, EUINT8 mode);

/************************************************************************
  Function��       ModifyVideoUniRtpMode
  Description��    �޸�rtp ͨ��mode
  Input��          multiIp:�鲥��ַ
                   mode: 1:send  2:recv  3:send & recv
  Return��         �ɹ�: ETOK    ʧ��: ETERROR
************************************************************************/

EINT32 ModifyVideoUniRtpMode(EUINT32 multiIp, EUINT8 mode);

/************************************************************************
  Function��       DelVideoUniRtpChan
  Description��    ɾ��rtp ͨ��
  Input��          multiIp:�鲥��ַ
  Return��         �ɹ�: ETOK    ʧ��: ETERROR
************************************************************************/

EINT32 DelVideoUniRtpChan(EUINT32 multiIp);

/************************************************************************
  Function��       SendVideoUniRtpPkg
  Description��    ���͵�����
  Input��          multiIp: �鲥��ַ   trafType:���� (1:h264)
                   pData:����ָ��   len:����    markFlag:rtp��ͷ�е�mark
  Return��         �ɹ�: ETOK    ʧ��: ETERROR
************************************************************************/

EINT32 SendVideoUniRtpPkg(EUINT32 multiIp, EUINT8 trafType, EINT8 *pData, EUINT32 len, EUINT8 markFlag);



#endif
#ifdef LARGE_CALL_DEBUG

/************************************************************************
  Function��       InitBearLargeCallModule
  Description��  ��ʼ�����ģ��
  Input��
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 InitBearLargeCallModule();

/************************************************************************
  Function��       SendLargeCallRtpPkg
  Description��   ͨ��large call rtp ͨ�������鲥����
  Input��          	callId: ͨ�����, ��CreateSwitchChannel()����
                   		trafType: ��������
                   		pData: ����ָ��
                  		 len: ���ݳ���
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 SendLargeCallRtpPkg(EINT32 callId, ECHAR trafType, ECHAR *pData, EUINT32 len);

/************************************************************************
  Function��       LargeCallCreateRtpChan
  Description��   Ϊ���������ṩ��rtp�������
  Input��      	callid: ͨ���ı�־
  				mode:ͨ��������1��ֻ���ͣ�2ֻ����
  				multicast:�鲥��ַ
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern EINT32 CreateLargeCallRtpChan(EUINT16 callId, EUINT32 multicastIp, ECHAR mode);
/************************************************************************
  Function��       DelLargeCallAllRtpChan
  Description�� ɾ�����е�large call rtpͨ��
  Input��
  				multicastIp:�鲥��ַ
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern EINT32 DelLargeCallAllRtpChan();
/************************************************************************
  Function��       DelLargeCallRtpChanByCallId
  Description��ͨ��callidɾ��large call rtp ͨ��
  Input��
  				multicastIp:�鲥��ַ
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern EINT32 DelLargeCallRtpChanByCallId(ECHAR callId);
/************************************************************************
  Function��       DelLargeCallRtpChanByMulticast
  Description��  ͨ���鲥��ַɾ��large call rtp ͨ��
  Input��
  				multicastIp:�鲥��ַ
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern EINT32 DelLargeCallRtpChanByMulticast(EUINT32 multicastIp);
#endif

#ifdef LIB_PSS
//���Ļ�վ����rtp���������д������ṹ
typedef EINT32 (*DEAL_UNITCAST_RTP_PKT_FUNC)(ECHAR *pData, EUINT16 length, EUCHAR bsrId, EUCHAR slot, EUINT type);

/************************************************************************
  Function��       SendPrimitivePktToSyncBsc
  Description��   ��ͬƵͬ����վ����rtp�����
  Input��            pbuf: ���͵�buf�ṹ, len�������ݳ���
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 SendPrimitivePktToSyncBsc(ECHAR *pBuf, EUINT16 len);

/************************************************************************
  Function��       	SetCenterBscFrameSeq
  Description��   �ӻ�վ���ȡͬ��֡���
  Input��          	���Ļ�վͬ��֡��

  Output��         	��
  Return��
				��
  Others��         	��
************************************************************************/
extern void SetCenterBscFrameSeq(EUINT32 seq);


/************************************************************************
  Function��       SelectRightRtpPkt
  Description��  �ӵ���rtp�������б���ѡ����ʵ�rtp���ݰ�����
  Input��            ��
  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern void SendCenterBsRtpPkt(EUINT16 slot);

/************************************************************************
  Function��       	SetDealUnitcastRtpPktFunc
  Description��    ���õ���������ӿ�
  Input��
  				func:������������
  Output��         	��
  Return��
  				ETOK:�ɹ�
  				ETERROR:ʧ��
  Others��         	��
************************************************************************/
extern EINT32 SetDealUnitcastRtpPktFunc(DEAL_UNITCAST_RTP_PKT_FUNC func);

#endif

#ifdef LIB_PDT

//ͬƵͬ����վ���������鲥�������ṹ
typedef EINT32 (*DEAL_PRIMITIVE_PKT_FUNC)(ECHAR *pBuf, EUINT16 bufLen);
/************************************************************************
  Function��       	SetDealPrimitivePktFunc
  Description��    ����ͬƵͬ����վ�ദ����������ݰ�
  Input��
  				func: ����ӿ�
  Output��         	��
  Return��
  				ETOK:�ɹ�
  				ETERROR:ʧ��
  Others��         	��
************************************************************************/
extern EINT32 SetDealPrimitivePktFunc(DEAL_PRIMITIVE_PKT_FUNC func);


#endif
#ifdef __cplusplus
}
#endif

#endif //__BEARBSC_H__

