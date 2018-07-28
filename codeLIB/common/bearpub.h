/************************************************************************
Copyright (C), 2009-2010, Eastcom.
File name：      socketLib.h
Author：          huangzd
Date：             09.7.17
Description：    对不同操作系统的socket接口进行封装，对上层提供统一socket接口
Others：         无
  *************************************************************************/
#ifndef __BEARPUB_H__
#define __BEARPUB_H__

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
                            函数申明
*************************************************************************/
/*---------------------------socket support---------------------------------*/
/************************************************************************
  Function：       TCPIP_init
  Description：    对TCPIP协议进行初始化
  Input：          无
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 TCPIP_init(void);

/************************************************************************
  Function：       TCPIP_discard
  Description：    TCPIP协议终止程序
  Input：          无
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 TCPIP_discard(void);

/************************************************************************
  Function：       CloseSocket
  Description：    关闭一个Socket
  Input：          id:Socket句柄
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 CloseSocket(EUINT32 id);

/************************************************************************
  Function：       OpenRawSocket
  Description：    打开一个原始Socket
  Input：          protocol：接收的IP数据包类型
  Output：         无
  Return：         成功：Socket 句柄, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 OpenRawSocket(EINT32 protocol);

/************************************************************************
  Function：       OpenSocket
  Description：    打开一个Socket
  Input：          type：WSOCK_STREAM：stream socket，WSOCK_DGRAM：datagram socket，
                    WSOCK_RAW：raw-protocol interface
  Output：         无
  Return：         成功：Socket 句柄, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 OpenSocket(EINT32 type);

/************************************************************************
  Function：       SetSocketNonblock
  Description：    将Socket设置为非阻塞方式
  Input：          id:Socket句柄
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 SetSocketNonblock(EUINT32 id);

/************************************************************************
Function：       SetSocketLoosRoute
Description：    将Socket设置为松散路由模式
Input：          id:Socket句柄, addr:指向路由IP地址列表的指针, num:路由表中路由地址的个数
Output：         无
Return：         成功：ETOK, 失败：ETERROR
Others：         无
************************************************************************/
extern EINT32 SetSocketLoosRoute(EUINT32 id, EUINT32 *addr, EUINT32 num);

/************************************************************************
  Function：       BindSocket
  Description：    将Socket与本地端口绑定
  Input：          id:Socket句柄, port: 端口
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 BindSocket(EUINT32 id, EUINT16 port);

/************************************************************************
  Function：       BindSrcIpSocket
  Description：    将Socket与本地端口绑定
  Input：          id: Socket句柄
                   srcIp: ip地址
                   port: 端口
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 BindSrcIpSocket(EUINT32 id, EUINT32 srcIp, EUINT16 port);

/************************************************************************
  Function：       ListenSocket
  Description：    启动Socket监听
  Input：          id:Socket句柄
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 ListenSocket(EUINT32 id);

/************************************************************************
  Function：       SetSocketQos
  Description：    设置socket的qos类型
  Input：          id:Socket句柄; buf[]: 缓存; qos:qos类型;
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 SetSocketQos(EUINT32 id, EUINT32 qos);

/************************************************************************
  Function：       AcceptSocket
  Description：    接受客户端的请求
  Input：          id:Socket句柄;
  Output：         pClientIpAddr: 客户端IP地址
  Return：         成功：新建的Socket句柄 , 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 AcceptSocket(EUINT32 id, EUINT32 *pClientIpAddr);

/************************************************************************
  Function：       ConnectSocket
  Description：    客户端呼叫服务器
  Input：          id:Socket句柄; remoteIpAddr: 服务器IP地址;port:端口
  Output：         无
  Return：         成功：ETOK , 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 ConnectSocket(EUINT32 id, EUINT32 remoteIpAddr, EUINT16 port);

/************************************************************************
  Function：       ReadFrame
  Description：    接收帧数据
  Input：          id:Socket句柄; len:缓冲区的长度
  Output：         buf[]: 缓存; pRemoteIpAddr: 数据帧源IP地址
  Return：         成功：大于0，接收到实际的数据字节数, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 ReadFrame(EUINT32 id,  ECHAR buf[],  EUINT32 len, EUINT32 *pRemoteIpAddr);

/************************************************************************
  Function：       SendFrame
  Description：    发送帧数据
  Input：          id:Socket句柄; buf[]: 缓存; len:缓冲区的长度;
                   remoteIpAddr: 数据帧目的IP地址;port:端口
  Output：         无
  Return：         成功: 发送的实际数据字节数, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 SendFrame(EUINT32 id, ECHAR buf[], EUINT32 len, EINT32 remoteIpAddr, EUINT16 port);

/************************************************************************
  Function：       ReadStream
  Description：    接收帧数据的缓冲区
  Input：          id:Socket句柄; buf[]: 缓存; len:缓冲区的长度;
  Output：         无
  Return：         成功：大于0，成功，接收到实际的数据字节数, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 ReadStream(EUINT32 id, ECHAR buf[], EINT32 len);

/************************************************************************
  Function：       SendStream
  Description：    发送帧数据
  Input：          id:Socket句柄; buf[]: 缓存; len:缓冲区的长度;
  Output：         无
  Return：         成功：大于0，成功，发送的实际数据字节数, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 SendStream(EUINT32 id ,ECHAR buf[], EINT32 len);

/************************************************************************
  Function：       GetIpAddr
  Description：    将ASCII码形式的IP地址转换成整型
  Input：          s:指向IP地址ASCII码形式的指针
  Output：         无
  Return：         IP地址的整数类型
  Others：         无
************************************************************************/
extern EUINT32 GetIpAddr(ECHAR *s);

/************************************************************************
  Function：       GetIpStr
  Description：    将整型的IP地址转换成ASCII码形式
  Input：          ipAddr:整数类型的IP地址
  Output：         s:指向IP地址ASCII码形式的指针
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 GetIpStr(EUINT32 ipAddr, ECHAR *s);

/*----------------------------multicast--------------------------------*/
/************************************************************************
  Function：       OpenMultiSock
  Description：    设置socket的组播发送接口地址及发送组播包的特性
  Input：          sId: 需要发送组播的socket句柄；ipAddr：默认发送组播包接口地址
  Output：         无
  Return：         成功ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 OpenMultiSock(EUINT32 sId, EUINT32 ipAddr);

/************************************************************************
  Function：       JoinMultiGroup
  Description：    将socket加入指定的组播
  Input：           recvIpAddr: 进行组播通讯端口的IP地址
                    multiIpAddr：组播地址；
                    sId：需要加入组播的socket
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 JoinMultiGroup(EUINT32 recvIpAddr, EUINT32 multiIpAddr, EUINT32 sId);

/************************************************************************
  Function：       LeaveMultiGroup
  Description：    将socket脱离指定的组播
  Input：          recvIpAddr: 进行组播通讯端口的IP地址
                    multiIpAddr：组播地址;
                    sId：需要脱离组播的socket
  Output：         无
  Return：         成功：ETOK, 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 LeaveMultiGroup(EUINT32 recvIpAddr, EUINT32 multiIpAddr, EUINT32 sId);

/*----------------------------memoryPoll--------------------------------*/
#define MAX_BUF_NUM     10

typedef struct MP_BUF_CONFIG_t          //MP_BUF初始化参数列表
{
    EUINT32 mpBufSize;                  //MP_BUF大小,4字节为单位
    EUINT32 mpBufNum;                   //MP_BUF数量
} MP_BUF_CONFIG;

typedef struct MP_CONFIG_t              //Memory Pool初始化参数
{
    EUINT32 mpBlkNum;                   //MP_BLK数量
    EUINT32 mpBufTypes;                 //MP_BUF大小种类
    struct MP_BUF_CONFIG_t *mpBufCfgList;  //MP_BUF初始化参数列表
} MP_CONFIG;

typedef struct MP_CTL_t              //Memory pool的控制结构
{
    struct MP_BLK_t *mpBlkFreeHdr;   //指向MP_BLK的链表头
    struct MP_BLK_t *mpBlkFreeTail;  //指向MP_BLK的链表尾
    EUINT32 mpBlkFreeNum;            //空闲MP_BLK数量
    EUINT32 mpBlkNum;                //MP_BLK总数
#ifdef ET_SDU_TRACE
    EUINT32 minMpBlkCount;           //MP_BLK最小剩余个数
#endif //ET_SDU_TRACE
    struct MP_SLAB_t *mpSlabList;    //指向MP_SLAB链表
    EUINT32 mpSlabNum;               //MP_SLAB数量
    void *mpAddrList[MAX_BUF_NUM];   //分配缓存的地址列表
} MP_CTL;

/************************************************************************
  Function：       InitMemPool
  Description：    初始化SDU内存池
  Input：          pMpConfig: 初始化参数
  Output：         无
  Return：         成功：ETOK；失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 InitMemPool(MP_CONFIG *pMpConfig);

/************************************************************************
  Function：       FreeMemPool
  Description：    注销SUD缓存管理模块
  Input：          无
  Output：         无
  Return：         成功：ETOK; 失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 FreeMemPool (void);

/************************************************************************
  Function：       GetSdu
  Description：    获取一个SDU数据块,加入跟踪信息
  Input：          bitLen: 数据块大小
  Output：         无
  Return：         成功：SDU数据块指针；失败：NULL
  Others：         无
************************************************************************/
#ifdef ET_SDU_TRACE
extern MP_BLK *SubGetSdu(EUINT32 bitLen, ECHAR *fileName, EUINT32 fileLine);
#define GetSdu(bitLen) SubGetSdu(bitLen, __FILE__, __LINE__)
#else
extern MP_BLK *GetMpBlkWithBuf(EUINT32 bitLen);
#define GetSdu(bitLen) GetMpBlkWithBuf(bitLen)
#endif //ET_SDU_TRACE

/************************************************************************
  Function：       FreeSdu
  Description：    释放SDU数据包
  Input：          pSrcMpBlk: SDU数据包指针
  Output：         无
  Return：         成功：ETOK；失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 FreeSdu(MP_BLK *pSrcMpBlk);

/************************************************************************
  Function：       CutSduHdr
  Description：    去数据包头
  Input：          pSrcMpBlk：源SDU数据包指针的指针；
                   bitLen：去除的数据长度
  Output：         pSrcMpBlk：新SDU数据包指针的指针
  Return：         成功：ETOK；失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 CutSduHdr(MP_BLK **pSrcMpBlk, EUINT32 bitLen);

/************************************************************************
  Function：       CutSduTail
  Description：    去数据包尾
  Input：          pSrcMpBlk: 源SDU数据包指针
                   bitLen：去除的数据长度
  Output：         无
  Return：         成功：ETOK；失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 CutSduTail(MP_BLK *pSrcMpBlk, EUINT32 bitLen);

/************************************************************************
  Function：       CloneSdu
  Description：    共享SDU数据包
  Input：          pSrcMpBlk: 源SDU数据包指针
                   bitOffset: 共享数据起始偏移量
                   bitLen: 共享数据长度
  Output：         无
  Return：         成功：共享SDU数据包指针；失败：NULL
  Others：         无
************************************************************************/
#if defined ET_SDU_TRACE
MP_BLK *SubCloneSdu(MP_BLK *pSrcMpBlk, EUINT32 bitOffset, EUINT32 bitLen, ECHAR *fileName, EUINT32 fileLine);
#define CloneSdu(pSrcMpBlk, bitOffset, bitLen) SubCloneSdu(pSrcMpBlk, bitOffset, bitLen, __FILE__, __LINE__);
#else
MP_BLK *CloneSdu(MP_BLK *pSrcMpBlk, EUINT32 bitOffset, EUINT32 bitLen);
#endif

/************************************************************************
  Function：       UniteSdu
  Description：    合并SDU数据包
  Input：          pFisrtMpBlk：第一个源SDU数据包指针，即合并后SDU数据包指针
                   pFisrtMpBlk：第二个源SDU数据包指针
  Output：         无
  Return：         成功：ETOK；失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 UniteSdu(MP_BLK *pFisrtMpBlk, MP_BLK *pSecondMpBlk);

/************************************************************************
  Function：       CopySduToBuf
  Description：    将SDU数据包复制到缓存数据
  Input：          pSrcMpBlk: 源SDU数据包
                   pBuf：读数据缓存指针
                   byteLen: 读缓存字节数
  Output：         无
  Return：         成功：读取数据的长度；失败：0
  Others：         无
************************************************************************/
extern EINT32 CopySduToBuf(MP_BLK *pSrcMpBlk, EUINT8 *pBuf, EUINT32 byteLen);

/************************************************************************
  Function：       CopySduToBufBit
  Description：    将SDU数据包中指定数据段复制到缓存数据
  Input：          pSrcMpBlk: 源SDU数据包
                   bitOffset: 读取数据起始偏移量
                   bitLen: 读取位数
                   pBuf：读数据缓存指针
  Output：         无
  Return：         成功：ETOK；失败：ETERROR
  Others：         无
************************************************************************/
extern EINT32 CopySduToBufBit(MP_BLK *pSrcMpBlk, EUINT32 bitOffset, EUINT32 bitLen, EUINT8 *pBuf);

/************************************************************************
  Function：       CopyBufToSdu
  Description：    将缓存数据复制到SDU数据包
  Input：          pBuf: 源数据指针
                   bitLen: 源数据长度
  Output：         无
  Return：         成功：SDU数据包指针；失败：NULL
  Others：         无
************************************************************************/
#ifdef ET_SDU_TRACE
MP_BLK *SubCopyBufToSdu(EUINT8 *pBuf, EUINT32 bitLen, ECHAR *fileName, EUINT32 fileLine);
#define CopyBufToSdu(pBuf, bitLen) SubCopyBufToSdu(pBuf, bitLen, __FILE__, __LINE__)
#else
extern MP_BLK *CopyBufToSdu(EUINT8 *pBuf, EUINT32 bitLen);
#endif //ET_SDU_TRACE

/************************************************************************
Function：       EncodeCurr32
Description：    将位于32位字节中的有效数据写入目的SDU中
Input：          pDesMpBlk: 目的SDU
                 data: 源数据，低位对齐
                 bitLen: 有效位数
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
extern EINT32 EncodeCurr32(MP_BLK *pDesMpBlk, EUINT32 data, EUINT32 bitLen);

/************************************************************************
Function：       ModifyCurr32
Description：    修改数据块中当前位置的数据
Input：          pDesMpBlk: 目的SDU
                 data: 源数据，低位对齐
                 bitLen: 有效位数
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
EINT32 ModifyCurr32(MP_BLK *pDesMpBlk, EUINT32 data, EUINT32 bitLen);

/************************************************************************
Function：       EncodeTail32
Description：    将位于32位字节中的有效数据添加到目的SDU数据包的尾部
Input：          pDesMpBlk: 目的SDU
                 data: 源数据，低位对齐
                 bitLen: 有效位数
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
/*extern EINT32 EncodeTail32(MP_BLK *pDesMpBlk, EUINT32 data, EUINT32 bitLen);*/

/************************************************************************
Function：       DeleteCurr
Description：    从当前偏移位开始向上删除bitLen位，删除位不清零
Input：          pDesMpBlk: 目的SDU
                 bitLen: 删除位数
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
extern EINT32 DeleteCurr(MP_BLK *pSrcMpBlk, EUINT32 bitLen);

/************************************************************************
Function：       FillZeroCurr
Description：    从当前偏移位开始填充bitLen位0
Input：          pSrcMpBlk: 目的SDU
                 bitLen: 清零位数
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
extern EINT32 FillZeroCurr(MP_BLK *pDesMpBlk, EUINT32 bitLen);

/************************************************************************
Function：       DecodeCurr32
Description：    从源SDU中的读取小于32位的有效数据
Input：          pSrcMpBlk: 源SDU
                 bitLen: bitLen有效位数
Output：         ret: 成功: ETOK 失败: ETERROR
Return：         读取的数据
Others：         无
************************************************************************/
extern EUINT32 DecodeCurr32(MP_BLK *pSrcMpBlk, EUINT32 bitLen, EINT32 *ret);

/************************************************************************
Function：       SetEncodePos
Description：    设置SDU的当前写入位置，范围限制在一个数据块中
Input：          pSrcMpBlk: 源SDU数据块指针
                 bitOffset: 新的写入位置起始偏移量
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
extern EINT32 SetEncodePos(MP_BLK *pSrcMpBlk, EUINT32 bitOffset);

/************************************************************************
Function：       SetDecodePos
Description：    设置SDU的当前读取位置
Input：          pSrcMpBlk: 源SDU数据包指针
                 bitOffset: 源SDU数据包中读取数据的起始位置偏移量
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
extern EINT32 SetDecodePos(MP_BLK *pSrcMpBlk, EUINT32 bitOffset);

/************************************************************************
Function：       PreLeftBlank
Description：    从当前写入位置开始预留bitLen位
Input：          pSrcMpBlk: 源SDU数据块指针
                 bitLen: 源SDU数据块中读取数据的启始位置偏移量
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
extern EINT32 PreLeftBlank(MP_BLK *pSrcMpBlk, EUINT32 bitLen);

/************************************************************************
Function：       FillLeftBlank
Description：    填充预留的空隙
Input：          pSrcMpBlk: 源SDU数据块指针
                 data: 写入数据，低位对齐
                 bitLen: 写入长度
Output：         无
Return：         成功: ETOK 失败: ETERROR
Others：         无
************************************************************************/
extern EINT32 FillLeftBlank(MP_BLK *pSrcMpBlk, EUINT32 data, EUINT32 bitLen);

/************************************************************************
  Function：       CalculateChecksum
  Description：    计算数据包校验和
  Input：
                   pData:需要计算校验的数据部分
                   len: 数据部分的长度
  Output：         无
  Return：         校验和
  Others：         无
************************************************************************/
EUINT16 CalculateChecksum(ECHAR *pData, EUINT32 len);

/************************************************************************
  Function：       ReadFromTo
  Description：    使用recvmsg接收数据包，使得可以获取ip头的目标地址
  Input：
                   s: 接收套接字
                   pRecvBuf: 存放数据的缓冲区
                   bufLen: 缓冲区大小
                   pSrcIp: 数据包的源端地址(网络字节序)
                   pDstIp: 数据包的目的地址(网络字节序)
  Output：         无
  Return：         成功: 接收数据的长度;失败: ETERROR
  Others：         此接口用于linux\vxworks\unix
************************************************************************/
EINT32 ReadFromTo(EUINT32 s, void *pRecvBuf,
                  EUINT16 bufLen, EUINT32 *pSrcIp, EUINT32 *pDstIp);
/************************************************************************
Function：       BindSctpSrcip
Description：   绑定sctp源IP地址
Input：
Output：         无
Return：         成功：ETOK, 失败：ETERROR
Others：         无
************************************************************************/
extern void BindSctpSrcIp(EUINT32 ip);
/************************************************************************
  Function：       SetB2PeerIP
  Description：    设置B2模式下，对端设备IP地址
  Input：          B2模式下对端IP地址ipAddr

  Output：         无
  Return：         无
  Others：         无
************************************************************************/
extern void SetB2PeerIP(EINT32 ipAddr);
/************************************************************************
  Function：       GetB2PeerIP
  Description：    获得B2模式下，对端设备IP地址
  Input：

  Output：         无
  Return：         对端B2IP地址
  Others：
************************************************************************/
extern EINT32 GetB2PeerIP();

/************************************************************************
  Function：       SetIcpChanSelect
  Description：    设置当前模式为B2模式
  Input：

  Output：         无
  Return：         对端B2IP地址
  Others：
************************************************************************/
extern void SetIcpChanSelect(EUINT32 flag);
/************************************************************************
  Function：       GetB2PeerIP
  Description：    获得当前是否是B2模式
  Input：

  Output：         无
  Return：         对端B2IP地址
  Others：
************************************************************************/
extern EINT32 GetIcpChanSelect();

/************************************************************************
  Function：       		  OpenSctpChan
  Description：  		  打开SCTP通道
  Input：          	     srcPort:源端口号
                         srcIP:源IP地址
                         dstPort:目的端口号
                         dstIP:目的IP地址
  Output：         				无
  Return：        	  成功：chanId；失败：0
  Others：         				无
************************************************************************/
extern EUINT32 OpenSctpChan(EUINT16 srcPort,EUINT32 srcIp,EUINT16 dstPort, EUINT32 dstIp);

/************************************************************************
  Function：       	OpenSctpServerChan
  Description：  		打开服务器端SCTP  通道
  Input：          	      srcPort:源端口号
                         		srcIP:源IP地址
                         		dstPort:目的端口号
                         		dstIP:目的IP地址
  Output：         		  无
  Return：        	  成功：chanId；失败：0
  Others：         		 无
************************************************************************/
extern EUINT32 OpenSctpServerChan(EUINT16 srcPort,EUINT32 srcIp,EUINT16 dstPort, EUINT32 dstIp);


/************************************************************************
  Function：       		  CloseSctpChan
  Description：  		  关闭SCTP通道
  Input：          	    srcPort:源端口号
                        srcIP:源IP地址
                        dstPort:目的端口号
                        dstIP:目的IP地址
  Output：         				无
  Return：        	  成功：chanId ；失败：0
  Others：         				无
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
  Function：      GetSctpChannelState
  Description：   向上层提供状态报告函数
  Input：         chanid: SCTP通道ID
  Output：        无
  Return：        GETSCTP_STATE_CLOSED  0
                  GETSCTP_STATE_OPEN  3
  Others：        无
************************************************************************/

extern EINT32 GetSctpChannelState(EUINT32 chanid);

#if 0
/************************************************************************
  Function：      RegSctpReportStateCallBack
  Description：   注册SCTP状态回调函数
  Input：         chanid: SCTP通道ID
                  pReportState: 状态报文发送函数
  Output：        无
  Return：        CHANID表示成功，0表示失败。
  Others：        无
************************************************************************/
extern EUINT32 RegSctpReportStateCallBack(EUINT32 chanId, ReportState pReportState);

/************************************************************************
  Function：      RegSctpReportDataCallBack
  Description：   注册SCTP回调函数
  Input：         chanid: SCTP通道ID
                  pReportData:DATA报文发送函数
  Output：        无
  Return：        chanId表示成功，0表示失败。
  Others：        无
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

