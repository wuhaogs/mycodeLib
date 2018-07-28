/************************************************************************
Copyright (C), 2009-2010, Eastcom.
File name��      socketLib.h
Author��          huangzd
Date��             09.7.17
Description��    �Բ�ͬ����ϵͳ��socket�ӿڽ��з�װ�����ϲ��ṩͳһsocket�ӿ�
Others��         ��
  *************************************************************************/
#ifndef __BEARPUB_H__
#define __BEARPUB_H__

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
#ifndef SOCK_STREAM
#define    ESOCK_STREAM    1        //TCP
#define    ESOCK_DGRAM     2        //UDP
#define    ESOCK_RAW       3
#else
#define    ESOCK_STREAM    SOCK_STREAM        //TCP
#define    ESOCK_DGRAM     SOCK_DGRAM        //UDP
#define    ESOCK_RAW       SOCK_RAW
#endif

#if	defined ET_BIG_ENDIAN
#define	etHtonl(x)    (x)
#define	etNtohl(x)    (x)
#define	etHtons(x)    (x)
#define	etNtohs(x)    (x)
#elif defined ET_LITTLE_ENDIAN
#define etHtonl(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))
#define etNtohl(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))
#define etHtons(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))
#define etNtohs(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))
#endif //ET_LITTLE_ENDIAN

//the tag of IpQos
#define QOS_VAL(x,y) ((x<<3)+(y<<1))
enum
{
	QOS_BEST,
	QOS_AF11= QOS_VAL(1,1),
	QOS_AF12= QOS_VAL(1,2),
	QOS_AF13= QOS_VAL(1,3),
	QOS_AF21= QOS_VAL(2,1),
	QOS_AF22= QOS_VAL(2,2),
	QOS_AF23= QOS_VAL(2,3),
	QOS_AF31= QOS_VAL(3,1),
	QOS_AF32= QOS_VAL(3,2),
	QOS_AF33= QOS_VAL(3,3),
	QOS_AF41= QOS_VAL(4,1),
	QOS_AF42= QOS_VAL(4,2),
	QOS_AF43= QOS_VAL(4,3),
	QOS_EF= QOS_VAL(5,3),
	QOS_INC= QOS_VAL(6,0),
	QOS_NC= QOS_VAL(7,0),
    QOS_PRIORITY_1 = QOS_VAL(1,0),
    QOS_PRIORITY_2 = QOS_VAL(2,0),
    QOS_PRIORITY_3 = QOS_VAL(3,0),
	QOS_PRIORITY_4 = QOS_VAL(4,0)
};

/************************************************************************
                            ��������
*************************************************************************/
/*---------------------------socket support---------------------------------*/
/************************************************************************
  Function��       TCPIP_init
  Description��    ��TCPIPЭ����г�ʼ��
  Input��          ��
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 TCPIP_init(void);

/************************************************************************
  Function��       TCPIP_discard
  Description��    TCPIPЭ����ֹ����
  Input��          ��
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 TCPIP_discard(void);

/************************************************************************
  Function��       CloseSocket
  Description��    �ر�һ��Socket
  Input��          id:Socket���
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 CloseSocket(EUINT32 id);

/************************************************************************
  Function��       OpenRawSocket
  Description��    ��һ��ԭʼSocket
  Input��          protocol�����յ�IP���ݰ�����
  Output��         ��
  Return��         �ɹ���Socket ���, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 OpenRawSocket(EINT32 protocol);

/************************************************************************
  Function��       OpenSocket
  Description��    ��һ��Socket
  Input��          type��WSOCK_STREAM��stream socket��WSOCK_DGRAM��datagram socket��
                    WSOCK_RAW��raw-protocol interface
  Output��         ��
  Return��         �ɹ���Socket ���, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 OpenSocket(EINT32 type);

/************************************************************************
  Function��       SetSocketNonblock
  Description��    ��Socket����Ϊ��������ʽ
  Input��          id:Socket���
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 SetSocketNonblock(EUINT32 id);

/************************************************************************
Function��       SetSocketLoosRoute
Description��    ��Socket����Ϊ��ɢ·��ģʽ
Input��          id:Socket���, addr:ָ��·��IP��ַ�б��ָ��, num:·�ɱ���·�ɵ�ַ�ĸ���
Output��         ��
Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
Others��         ��
************************************************************************/
extern EINT32 SetSocketLoosRoute(EUINT32 id, EUINT32 *addr, EUINT32 num);

/************************************************************************
  Function��       BindSocket
  Description��    ��Socket�뱾�ض˿ڰ�
  Input��          id:Socket���, port: �˿�
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 BindSocket(EUINT32 id, EUINT16 port);

/************************************************************************
  Function��       BindSrcIpSocket
  Description��    ��Socket�뱾�ض˿ڰ�
  Input��          id: Socket���
                   srcIp: ip��ַ
                   port: �˿�
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 BindSrcIpSocket(EUINT32 id, EUINT32 srcIp, EUINT16 port);

/************************************************************************
  Function��       ListenSocket
  Description��    ����Socket����
  Input��          id:Socket���
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 ListenSocket(EUINT32 id);

/************************************************************************
  Function��       SetSocketQos
  Description��    ����socket��qos����
  Input��          id:Socket���; buf[]: ����; qos:qos����;
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 SetSocketQos(EUINT32 id, EUINT32 qos);

/************************************************************************
  Function��       AcceptSocket
  Description��    ���ܿͻ��˵�����
  Input��          id:Socket���;
  Output��         pClientIpAddr: �ͻ���IP��ַ
  Return��         �ɹ����½���Socket��� , ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 AcceptSocket(EUINT32 id, EUINT32 *pClientIpAddr);

/************************************************************************
  Function��       ConnectSocket
  Description��    �ͻ��˺��з�����
  Input��          id:Socket���; remoteIpAddr: ������IP��ַ;port:�˿�
  Output��         ��
  Return��         �ɹ���ETOK , ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 ConnectSocket(EUINT32 id, EUINT32 remoteIpAddr, EUINT16 port);

/************************************************************************
  Function��       ReadFrame
  Description��    ����֡����
  Input��          id:Socket���; len:�������ĳ���
  Output��         buf[]: ����; pRemoteIpAddr: ����֡ԴIP��ַ
  Return��         �ɹ�������0�����յ�ʵ�ʵ������ֽ���, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 ReadFrame(EUINT32 id,  ECHAR buf[],  EUINT32 len, EUINT32 *pRemoteIpAddr);

/************************************************************************
  Function��       SendFrame
  Description��    ����֡����
  Input��          id:Socket���; buf[]: ����; len:�������ĳ���;
                   remoteIpAddr: ����֡Ŀ��IP��ַ;port:�˿�
  Output��         ��
  Return��         �ɹ�: ���͵�ʵ�������ֽ���, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 SendFrame(EUINT32 id, ECHAR buf[], EUINT32 len, EINT32 remoteIpAddr, EUINT16 port);

/************************************************************************
  Function��       ReadStream
  Description��    ����֡���ݵĻ�����
  Input��          id:Socket���; buf[]: ����; len:�������ĳ���;
  Output��         ��
  Return��         �ɹ�������0���ɹ������յ�ʵ�ʵ������ֽ���, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 ReadStream(EUINT32 id, ECHAR buf[], EINT32 len);

/************************************************************************
  Function��       SendStream
  Description��    ����֡����
  Input��          id:Socket���; buf[]: ����; len:�������ĳ���;
  Output��         ��
  Return��         �ɹ�������0���ɹ������͵�ʵ�������ֽ���, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 SendStream(EUINT32 id ,ECHAR buf[], EINT32 len);

/************************************************************************
  Function��       GetIpAddr
  Description��    ��ASCII����ʽ��IP��ַת��������
  Input��          s:ָ��IP��ַASCII����ʽ��ָ��
  Output��         ��
  Return��         IP��ַ����������
  Others��         ��
************************************************************************/
extern EUINT32 GetIpAddr(ECHAR *s);

/************************************************************************
  Function��       GetIpStr
  Description��    �����͵�IP��ַת����ASCII����ʽ
  Input��          ipAddr:�������͵�IP��ַ
  Output��         s:ָ��IP��ַASCII����ʽ��ָ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 GetIpStr(EUINT32 ipAddr, ECHAR *s);

/*----------------------------multicast--------------------------------*/
/************************************************************************
  Function��       OpenMultiSock
  Description��    ����socket���鲥���ͽӿڵ�ַ�������鲥��������
  Input��          sId: ��Ҫ�����鲥��socket�����ipAddr��Ĭ�Ϸ����鲥���ӿڵ�ַ
  Output��         ��
  Return��         �ɹ��oETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 OpenMultiSock(EUINT32 sId, EUINT32 ipAddr);

/************************************************************************
  Function��       JoinMultiGroup
  Description��    ��socket����ָ�����鲥
  Input��           recvIpAddr: �����鲥ͨѶ�˿ڵ�IP��ַ
                    multiIpAddr���鲥��ַ��
                    sId����Ҫ�����鲥��socket
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 JoinMultiGroup(EUINT32 recvIpAddr, EUINT32 multiIpAddr, EUINT32 sId);

/************************************************************************
  Function��       LeaveMultiGroup
  Description��    ��socket����ָ�����鲥
  Input��          recvIpAddr: �����鲥ͨѶ�˿ڵ�IP��ַ
                    multiIpAddr���鲥��ַ;
                    sId����Ҫ�����鲥��socket
  Output��         ��
  Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 LeaveMultiGroup(EUINT32 recvIpAddr, EUINT32 multiIpAddr, EUINT32 sId);

/*----------------------------memoryPoll--------------------------------*/
#define MAX_BUF_NUM     10

typedef struct MP_BUF_CONFIG_t          //MP_BUF��ʼ�������б�
{
    EUINT32 mpBufSize;                  //MP_BUF��С,4�ֽ�Ϊ��λ
    EUINT32 mpBufNum;                   //MP_BUF����
} MP_BUF_CONFIG;

typedef struct MP_CONFIG_t              //Memory Pool��ʼ������
{
    EUINT32 mpBlkNum;                   //MP_BLK����
    EUINT32 mpBufTypes;                 //MP_BUF��С����
    struct MP_BUF_CONFIG_t *mpBufCfgList;  //MP_BUF��ʼ�������б�
} MP_CONFIG;

typedef struct MP_CTL_t              //Memory pool�Ŀ��ƽṹ
{
    struct MP_BLK_t *mpBlkFreeHdr;   //ָ��MP_BLK������ͷ
    struct MP_BLK_t *mpBlkFreeTail;  //ָ��MP_BLK������β
    EUINT32 mpBlkFreeNum;            //����MP_BLK����
    EUINT32 mpBlkNum;                //MP_BLK����
#ifdef ET_SDU_TRACE
    EUINT32 minMpBlkCount;           //MP_BLK��Сʣ�����
#endif //ET_SDU_TRACE
    struct MP_SLAB_t *mpSlabList;    //ָ��MP_SLAB����
    EUINT32 mpSlabNum;               //MP_SLAB����
    void *mpAddrList[MAX_BUF_NUM];   //���仺��ĵ�ַ�б�
} MP_CTL;

/************************************************************************
  Function��       InitMemPool
  Description��    ��ʼ��SDU�ڴ��
  Input��          pMpConfig: ��ʼ������
  Output��         ��
  Return��         �ɹ���ETOK��ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 InitMemPool(MP_CONFIG *pMpConfig);

/************************************************************************
  Function��       FreeMemPool
  Description��    ע��SUD�������ģ��
  Input��          ��
  Output��         ��
  Return��         �ɹ���ETOK; ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 FreeMemPool (void);

/************************************************************************
  Function��       GetSdu
  Description��    ��ȡһ��SDU���ݿ�,���������Ϣ
  Input��          bitLen: ���ݿ��С
  Output��         ��
  Return��         �ɹ���SDU���ݿ�ָ�룻ʧ�ܣ�NULL
  Others��         ��
************************************************************************/
#ifdef ET_SDU_TRACE
extern MP_BLK *SubGetSdu(EUINT32 bitLen, ECHAR *fileName, EUINT32 fileLine);
#define GetSdu(bitLen) SubGetSdu(bitLen, __FILE__, __LINE__)
#else
extern MP_BLK *GetMpBlkWithBuf(EUINT32 bitLen);
#define GetSdu(bitLen) GetMpBlkWithBuf(bitLen)
#endif //ET_SDU_TRACE

/************************************************************************
  Function��       FreeSdu
  Description��    �ͷ�SDU���ݰ�
  Input��          pSrcMpBlk: SDU���ݰ�ָ��
  Output��         ��
  Return��         �ɹ���ETOK��ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 FreeSdu(MP_BLK *pSrcMpBlk);

/************************************************************************
  Function��       CutSduHdr
  Description��    ȥ���ݰ�ͷ
  Input��          pSrcMpBlk��ԴSDU���ݰ�ָ���ָ�룻
                   bitLen��ȥ�������ݳ���
  Output��         pSrcMpBlk����SDU���ݰ�ָ���ָ��
  Return��         �ɹ���ETOK��ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 CutSduHdr(MP_BLK **pSrcMpBlk, EUINT32 bitLen);

/************************************************************************
  Function��       CutSduTail
  Description��    ȥ���ݰ�β
  Input��          pSrcMpBlk: ԴSDU���ݰ�ָ��
                   bitLen��ȥ�������ݳ���
  Output��         ��
  Return��         �ɹ���ETOK��ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 CutSduTail(MP_BLK *pSrcMpBlk, EUINT32 bitLen);

/************************************************************************
  Function��       CloneSdu
  Description��    ����SDU���ݰ�
  Input��          pSrcMpBlk: ԴSDU���ݰ�ָ��
                   bitOffset: ����������ʼƫ����
                   bitLen: �������ݳ���
  Output��         ��
  Return��         �ɹ�������SDU���ݰ�ָ�룻ʧ�ܣ�NULL
  Others��         ��
************************************************************************/
#if defined ET_SDU_TRACE
MP_BLK *SubCloneSdu(MP_BLK *pSrcMpBlk, EUINT32 bitOffset, EUINT32 bitLen, ECHAR *fileName, EUINT32 fileLine);
#define CloneSdu(pSrcMpBlk, bitOffset, bitLen) SubCloneSdu(pSrcMpBlk, bitOffset, bitLen, __FILE__, __LINE__);
#else
MP_BLK *CloneSdu(MP_BLK *pSrcMpBlk, EUINT32 bitOffset, EUINT32 bitLen);
#endif

/************************************************************************
  Function��       UniteSdu
  Description��    �ϲ�SDU���ݰ�
  Input��          pFisrtMpBlk����һ��ԴSDU���ݰ�ָ�룬���ϲ���SDU���ݰ�ָ��
                   pFisrtMpBlk���ڶ���ԴSDU���ݰ�ָ��
  Output��         ��
  Return��         �ɹ���ETOK��ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 UniteSdu(MP_BLK *pFisrtMpBlk, MP_BLK *pSecondMpBlk);

/************************************************************************
  Function��       CopySduToBuf
  Description��    ��SDU���ݰ����Ƶ���������
  Input��          pSrcMpBlk: ԴSDU���ݰ�
                   pBuf�������ݻ���ָ��
                   byteLen: �������ֽ���
  Output��         ��
  Return��         �ɹ�����ȡ���ݵĳ��ȣ�ʧ�ܣ�0
  Others��         ��
************************************************************************/
extern EINT32 CopySduToBuf(MP_BLK *pSrcMpBlk, EUINT8 *pBuf, EUINT32 byteLen);

/************************************************************************
  Function��       CopySduToBufBit
  Description��    ��SDU���ݰ���ָ�����ݶθ��Ƶ���������
  Input��          pSrcMpBlk: ԴSDU���ݰ�
                   bitOffset: ��ȡ������ʼƫ����
                   bitLen: ��ȡλ��
                   pBuf�������ݻ���ָ��
  Output��         ��
  Return��         �ɹ���ETOK��ʧ�ܣ�ETERROR
  Others��         ��
************************************************************************/
extern EINT32 CopySduToBufBit(MP_BLK *pSrcMpBlk, EUINT32 bitOffset, EUINT32 bitLen, EUINT8 *pBuf);

/************************************************************************
  Function��       CopyBufToSdu
  Description��    ���������ݸ��Ƶ�SDU���ݰ�
  Input��          pBuf: Դ����ָ��
                   bitLen: Դ���ݳ���
  Output��         ��
  Return��         �ɹ���SDU���ݰ�ָ�룻ʧ�ܣ�NULL
  Others��         ��
************************************************************************/
#ifdef ET_SDU_TRACE
MP_BLK *SubCopyBufToSdu(EUINT8 *pBuf, EUINT32 bitLen, ECHAR *fileName, EUINT32 fileLine);
#define CopyBufToSdu(pBuf, bitLen) SubCopyBufToSdu(pBuf, bitLen, __FILE__, __LINE__)
#else
extern MP_BLK *CopyBufToSdu(EUINT8 *pBuf, EUINT32 bitLen);
#endif //ET_SDU_TRACE

/************************************************************************
Function��       EncodeCurr32
Description��    ��λ��32λ�ֽ��е���Ч����д��Ŀ��SDU��
Input��          pDesMpBlk: Ŀ��SDU
                 data: Դ���ݣ���λ����
                 bitLen: ��Чλ��
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
extern EINT32 EncodeCurr32(MP_BLK *pDesMpBlk, EUINT32 data, EUINT32 bitLen);

/************************************************************************
Function��       ModifyCurr32
Description��    �޸����ݿ��е�ǰλ�õ�����
Input��          pDesMpBlk: Ŀ��SDU
                 data: Դ���ݣ���λ����
                 bitLen: ��Чλ��
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
EINT32 ModifyCurr32(MP_BLK *pDesMpBlk, EUINT32 data, EUINT32 bitLen);

/************************************************************************
Function��       EncodeTail32
Description��    ��λ��32λ�ֽ��е���Ч������ӵ�Ŀ��SDU���ݰ���β��
Input��          pDesMpBlk: Ŀ��SDU
                 data: Դ���ݣ���λ����
                 bitLen: ��Чλ��
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
/*extern EINT32 EncodeTail32(MP_BLK *pDesMpBlk, EUINT32 data, EUINT32 bitLen);*/

/************************************************************************
Function��       DeleteCurr
Description��    �ӵ�ǰƫ��λ��ʼ����ɾ��bitLenλ��ɾ��λ������
Input��          pDesMpBlk: Ŀ��SDU
                 bitLen: ɾ��λ��
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
extern EINT32 DeleteCurr(MP_BLK *pSrcMpBlk, EUINT32 bitLen);

/************************************************************************
Function��       FillZeroCurr
Description��    �ӵ�ǰƫ��λ��ʼ���bitLenλ0
Input��          pSrcMpBlk: Ŀ��SDU
                 bitLen: ����λ��
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
extern EINT32 FillZeroCurr(MP_BLK *pDesMpBlk, EUINT32 bitLen);

/************************************************************************
Function��       DecodeCurr32
Description��    ��ԴSDU�еĶ�ȡС��32λ����Ч����
Input��          pSrcMpBlk: ԴSDU
                 bitLen: bitLen��Чλ��
Output��         ret: �ɹ�: ETOK ʧ��: ETERROR
Return��         ��ȡ������
Others��         ��
************************************************************************/
extern EUINT32 DecodeCurr32(MP_BLK *pSrcMpBlk, EUINT32 bitLen, EINT32 *ret);

/************************************************************************
Function��       SetEncodePos
Description��    ����SDU�ĵ�ǰд��λ�ã���Χ������һ�����ݿ���
Input��          pSrcMpBlk: ԴSDU���ݿ�ָ��
                 bitOffset: �µ�д��λ����ʼƫ����
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
extern EINT32 SetEncodePos(MP_BLK *pSrcMpBlk, EUINT32 bitOffset);

/************************************************************************
Function��       SetDecodePos
Description��    ����SDU�ĵ�ǰ��ȡλ��
Input��          pSrcMpBlk: ԴSDU���ݰ�ָ��
                 bitOffset: ԴSDU���ݰ��ж�ȡ���ݵ���ʼλ��ƫ����
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
extern EINT32 SetDecodePos(MP_BLK *pSrcMpBlk, EUINT32 bitOffset);

/************************************************************************
Function��       PreLeftBlank
Description��    �ӵ�ǰд��λ�ÿ�ʼԤ��bitLenλ
Input��          pSrcMpBlk: ԴSDU���ݿ�ָ��
                 bitLen: ԴSDU���ݿ��ж�ȡ���ݵ���ʼλ��ƫ����
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
extern EINT32 PreLeftBlank(MP_BLK *pSrcMpBlk, EUINT32 bitLen);

/************************************************************************
Function��       FillLeftBlank
Description��    ���Ԥ���Ŀ�϶
Input��          pSrcMpBlk: ԴSDU���ݿ�ָ��
                 data: д�����ݣ���λ����
                 bitLen: д�볤��
Output��         ��
Return��         �ɹ�: ETOK ʧ��: ETERROR
Others��         ��
************************************************************************/
extern EINT32 FillLeftBlank(MP_BLK *pSrcMpBlk, EUINT32 data, EUINT32 bitLen);

/************************************************************************
  Function��       CalculateChecksum
  Description��    �������ݰ�У���
  Input��
                   pData:��Ҫ����У������ݲ���
                   len: ���ݲ��ֵĳ���
  Output��         ��
  Return��         У���
  Others��         ��
************************************************************************/
EUINT16 CalculateChecksum(ECHAR *pData, EUINT32 len);

/************************************************************************
  Function��       ReadFromTo
  Description��    ʹ��recvmsg�������ݰ���ʹ�ÿ��Ի�ȡipͷ��Ŀ���ַ
  Input��
                   s: �����׽���
                   pRecvBuf: ������ݵĻ�����
                   bufLen: ��������С
                   pSrcIp: ���ݰ���Դ�˵�ַ(�����ֽ���)
                   pDstIp: ���ݰ���Ŀ�ĵ�ַ(�����ֽ���)
  Output��         ��
  Return��         �ɹ�: �������ݵĳ���;ʧ��: ETERROR
  Others��         �˽ӿ�����linux\vxworks\unix
************************************************************************/
EINT32 ReadFromTo(EUINT32 s, void *pRecvBuf,
                  EUINT16 bufLen, EUINT32 *pSrcIp, EUINT32 *pDstIp);
/************************************************************************
Function��       BindSctpSrcip
Description��   ��sctpԴIP��ַ
Input��
Output��         ��
Return��         �ɹ���ETOK, ʧ�ܣ�ETERROR
Others��         ��
************************************************************************/
extern void BindSctpSrcIp(EUINT32 ip);
/************************************************************************
  Function��       SetB2PeerIP
  Description��    ����B2ģʽ�£��Զ��豸IP��ַ
  Input��          B2ģʽ�¶Զ�IP��ַipAddr

  Output��         ��
  Return��         ��
  Others��         ��
************************************************************************/
extern void SetB2PeerIP(EINT32 ipAddr);
/************************************************************************
  Function��       GetB2PeerIP
  Description��    ���B2ģʽ�£��Զ��豸IP��ַ
  Input��

  Output��         ��
  Return��         �Զ�B2IP��ַ
  Others��
************************************************************************/
extern EINT32 GetB2PeerIP();

/************************************************************************
  Function��       SetIcpChanSelect
  Description��    ���õ�ǰģʽΪB2ģʽ
  Input��

  Output��         ��
  Return��         �Զ�B2IP��ַ
  Others��
************************************************************************/
extern void SetIcpChanSelect(EUINT32 flag);
/************************************************************************
  Function��       GetB2PeerIP
  Description��    ��õ�ǰ�Ƿ���B2ģʽ
  Input��

  Output��         ��
  Return��         �Զ�B2IP��ַ
  Others��
************************************************************************/
extern EINT32 GetIcpChanSelect();

/************************************************************************
  Function��       		  OpenSctpChan
  Description��  		  ��SCTPͨ��
  Input��          	     srcPort:Դ�˿ں�
                         srcIP:ԴIP��ַ
                         dstPort:Ŀ�Ķ˿ں�
                         dstIP:Ŀ��IP��ַ
  Output��         				��
  Return��        	  �ɹ���chanId��ʧ�ܣ�0
  Others��         				��
************************************************************************/
extern EUINT32 OpenSctpChan(EUINT16 srcPort,EUINT32 srcIp,EUINT16 dstPort, EUINT32 dstIp);

/************************************************************************
  Function��       	OpenSctpServerChan
  Description��  		�򿪷�������SCTP  ͨ��
  Input��          	      srcPort:Դ�˿ں�
                         		srcIP:ԴIP��ַ
                         		dstPort:Ŀ�Ķ˿ں�
                         		dstIP:Ŀ��IP��ַ
  Output��         		  ��
  Return��        	  �ɹ���chanId��ʧ�ܣ�0
  Others��         		 ��
************************************************************************/
extern EUINT32 OpenSctpServerChan(EUINT16 srcPort,EUINT32 srcIp,EUINT16 dstPort, EUINT32 dstIp);


/************************************************************************
  Function��       		  CloseSctpChan
  Description��  		  �ر�SCTPͨ��
  Input��          	    srcPort:Դ�˿ں�
                        srcIP:ԴIP��ַ
                        dstPort:Ŀ�Ķ˿ں�
                        dstIP:Ŀ��IP��ַ
  Output��         				��
  Return��        	  �ɹ���chanId ��ʧ�ܣ�0
  Others��         				��
************************************************************************/
extern EUINT32 CloseSctpChan(EUINT32 chanId);

/******************************************************************
* Function Name:  SendDataBySctp.
* Description:       The user send sctp data by this function.
* Input:                pSctpChan, buf, len, order: sequential data or not.
* Output:		.
* Return:              chanId (sucess), 0(fail).
******************************************************************/
extern EINT32 SendDataBySctp(EUINT32 pChan, EUINT8 *pBuf, EUINT16 len, EUINT8 order);

/************************************************************************
  Function��      GetSctpChannelState
  Description��   ���ϲ��ṩ״̬���溯��
  Input��         chanid: SCTPͨ��ID
  Output��        ��
  Return��        GETSCTP_STATE_CLOSED  0
                  GETSCTP_STATE_OPEN  3
  Others��        ��
************************************************************************/

extern EINT32 GetSctpChannelState(EUINT32 chanid);

#if 0
/************************************************************************
  Function��      RegSctpReportStateCallBack
  Description��   ע��SCTP״̬�ص�����
  Input��         chanid: SCTPͨ��ID
                  pReportState: ״̬���ķ��ͺ���
  Output��        ��
  Return��        CHANID��ʾ�ɹ���0��ʾʧ�ܡ�
  Others��        ��
************************************************************************/
extern EUINT32 RegSctpReportStateCallBack(EUINT32 chanId, ReportState pReportState);

/************************************************************************
  Function��      RegSctpReportDataCallBack
  Description��   ע��SCTP�ص�����
  Input��         chanid: SCTPͨ��ID
                  pReportData:DATA���ķ��ͺ���
  Output��        ��
  Return��        chanId��ʾ�ɹ���0��ʾʧ�ܡ�
  Others��        ��
************************************************************************/
extern EUINT32 RegSctpReportDataCallBack(EUINT32 chanId, ReportData pReportData);
#endif
#ifdef SDU_DEBUG
#define    SduLog     PrintfLog
#define    SduLogPkt  PrintfLogPkt
#else
#define    SduLog
#define    SduLogPkt
#endif //SDU_DEBUG

#define    BEAR_DEBUG
#define OSPF_DEBUG

#ifdef SDU_DEBUG
extern EINT32 __stdcall MpFirstTask(void *threadNo);
extern EINT32 __stdcall MpSecondTask(void *threadNo);
extern EINT32 __stdcall CodeTask(void *threadNo);
extern EINT32 RegSduTestCmd(void);
#endif //SDU_DEBUG

#ifdef __cplusplus
}
#endif //__cplusplus

#define MPBUF_TYPE(size, count) {size, count},

#define DEFAULT_MP_BLK_NUM 1600
#define MPBUF_TYPES {\
    MPBUF_TYPE(200, 400) \
    MPBUF_TYPE(100, 400) \
    MPBUF_TYPE(50, 300) \
    MPBUF_TYPE(30, 300) \
}
extern EUINT32 sduErrorPos;
#define SET_SDU_SIGN(x) {sduErrorPos = x;}

#endif //__BEARPUB_H__

