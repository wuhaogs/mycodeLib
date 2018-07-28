#ifndef __MY_CODE_H__
#define __MY_CODE_H__
#include "common.h"

//#define ET_PACK_ALIGN(x) __attribute__((packed, aligned(x)))

#define PPAL_CALL_IND_HASH_TABLE_MAX  32
#define PPAL_PKT_HASH_TABLE_MAX       32
#define PPAL_PKT_STATUS_POOL_LEN      150

typedef struct  
{
    EUCHAR h_verlen;                 //4位首部长度+4位IP版本号 
    EUCHAR tos;   
    EINT16 total_len;                //16位总长度（字节） 
    EINT16 ident;                    //16位标识 
    EINT16 frag_and_flags;           //3位标志位 
    EUCHAR ttl;                      //8位生存时间 TTL 
    EUCHAR proto;                    //8位协议 (TCP, UDP 或其他) 
    EINT16 checksum;                 //16位IP首部校验和 
    EUINT32 sourceIP;                //32位源IP地址 
    //ECHAR data1[1]; 
    EUINT32 destIP;                  //32位目的IP地址 
    ECHAR data[0];                   //数据启始字节
} ET_PACK_ALIGN(1) IP_PKG;

typedef struct  
{
    EUCHAR h_verlen;                 //4位首部长度+4位IP版本号 
    EUCHAR tos;                      //8位服务类型TOS 
    EINT16 total_len;                //16位总长度（字节） 
    EINT16 ident;                    //16位标识 
    EINT16 frag_and_flags;           //3位标志位 
    EUCHAR ttl;                      //8位生存时间 TTL 
    EUCHAR proto;                    //8位协议 (TCP, UDP 或其他) 
    EINT16 checksum;                 //16位IP首部校验和 
    EUINT32 sourceIP;                //32位源IP地址 
    //ECHAR data1[1];    
    EUINT32 destIP;                  //32位目的IP地址 
    ECHAR data[0];                   //数据启始字节
} IP_PKG1;
typedef enum
{
    PKT_IDLE                    = 0,     /* IDLE状态 */
    WAIT_D_PDGRANT               = 1,     /* 等待数据信道分配响应 */
    WAIT_C_ACKU_IND             = 2,
    WAIT_TRANSFER_DATA          = 3,     /* 准备数据传输 */
    WAIT_P_PROTECT              = 4,
    WAIT_P_MAINT                = 5,
    WAIT_P_AHOY                 = 6,
    WAIT_P_ACKU                 = 7,
    WAIT_P_DACKU                = 8,
    WAIT_P_PCLEAR               = 9
}PKT_STATUS_e;

typedef struct
{
    NODE            pPktCalledSta;            /* 在PktCallAddrHash表中指向前后状态机 */
    NODE            pPktEvtTagSta;            /* 在PktEventTagHash表中指向前后状态机 */
    EINT32          uiPktCalledTimerHandle;   /* CalledStatus定时器 */
    EUINT32         uiCallingAddr;            /* 主叫地址 */
    EUINT32         uiCalledAddr;             /* 被叫地址 */
    EUINT32         uiSel;                    /* 记录主叫事件标签 */
    EUINT32         uiTel;                    /* 记录被叫事件标签 */
    EUCHAR          unTimeSlot;               /* 业务信道时隙号 */
    EUCHAR          unBsrId;                  /* 标示bsr板号 */
    EUCHAR          unAddrType;               /* MS地址类型IG */
    PKT_STATUS_e    ePktStatus;               /* 记录被叫方的呼叫状态 */
    EUCHAR          unChanType;               /* 分组信道类型，0为共享型分组信道，1为专用型分组信道*/

}PPAL_PKT_CALLED_STATUS_t;

typedef struct Student
{
    int data;
    struct Student *next;
}mynode;

typedef struct DStudent
{
    int data;
    struct DStudent *next;
    struct DStudent *pre;
}mydnode;

typedef struct LNode
{
    int data;
    struct LNode *link;

}myLNode,*LinkList;

typedef struct linkqueue
{
    mynode *first, *rear;
}myqueue;

typedef struct stackqueue
{
    mynode *zhandi, *top;
}myqueueStack;

typedef struct stackx
{
    mynode *top;
    int length;
}myStackX;


typedef struct
{
    NODE ptestNode;
    EUINT32 uiSaddr;
    EUINT8  unBsrID;
    EUINT8  uiTimeslot;
}TEST_NODE_T;

//16进制字符转换为数值
EUCHAR a2x(EUCHAR ch);

//将字符串数组转化成普通字节数组
EINT32 ArrayString2Byte(EUCHAR *str2,EUCHAR *str1);

//初始化分组被叫地址哈希表
EINT32 InitPktCalledAddrHashTable();

//初始化分组被叫标签哈希表
EINT32 InitPktCalledEvtTagHashTable();

//初始化分组被叫缓存池
EINT32 InitPktCalledStatusPool();

//恢复分组被叫缓存池
EINT32	RestorePktCalledStaPool();

//根据地址查找分组被叫地址状态机
EINT32 SearchPktCalledSta(PPAL_PKT_CALLED_STATUS_t **ppPktSta, EUINT32 uiCalledAddr);

//根据标签查找分组被叫标签状态机，添加节点地址的时候，有地址偏移，故查找的时候需要地址偏移
EINT32 SearchPktCalledStaFromEvtTag(PPAL_PKT_CALLED_STATUS_t **ppPktSta,EUINT32 uiEventTag);

//从分组被叫缓存池中获取一块地址
PPAL_PKT_CALLED_STATUS_t  *GetPktCalledStaFromPool();

//从分组被叫地址哈希表中删除一个节点地址并向缓存池中返还一个节点
EINT32 DeletePktStaFromCalledAddrHash(PPAL_PKT_CALLED_STATUS_t  *pCalledSta);

//从分组被叫标签哈希表中删除一个节点地址并向缓存池中返还一个节点
EINT32 DeletePktStaFromCalledEvtTagHash(PPAL_PKT_CALLED_STATUS_t  *pPktSta);

//添加一个节点地址到分组被叫地址哈希表
EINT32 AddPktStaToCalledAddrHash(PPAL_PKT_CALLED_STATUS_t *pCalledSta);

//添加一个节点地址到分组被叫标签哈希表
EINT32 AddPktEvtTagToCalledAddrHash(PPAL_PKT_CALLED_STATUS_t *pCalledSta);

//根据地址获取其索引值
EUINT32 GetPPALPktCallAddrHashIndex(EUINT32 uiAddr);

//根据标签获取其索引值
EUINT32 GetPPALPktEvtTagHashIndex(EUINT32 uiEventTag);

//向分组被叫缓存池中返还一个节点
EINT32 PutPktCalledStaToPool(PPAL_PKT_CALLED_STATUS_t *pCalledSta);

//初始化分组被叫业务
void InitTestList();

//单链表的建立
mynode *create();
//但链表测长
int lengthS(mynode *head);
//单链表打印
void printS(mynode *head);
mynode *create1();


//单链表删除节点
mynode *delS(mynode *head, int num);
//单链表添加到结点尾，返回新加入的结点，即新的结点尾
mynode *insertTailS(mynode *tail, int num);
//获取单链表的尾结点
mynode *GetTailS(mynode *head);
//创建单链表，返回头节点
mynode *createS();
//单链表的排序,返回头结点
mynode *sortS(mynode *head);
//单链表的逆置，返回头结点
mynode *reverseS(mynode *head);
void searchmid(mynode *head, mynode *mid);

//双链表的添加，添加到尾部,返回新加入的结点
mydnode *insertTailD(mydnode *tail, int num);
//创建双链表，返回头节点
extern mydnode *createD();
//双链表的删除，返回头结点
mydnode *delD(mydnode *head, int num);
//获取双链表的尾结点
mydnode *GetTailD(mydnode *head);
//双链表测长
int lengthD(mydnode *head);
//双链表打印
void printD(mydnode *head);

//队列入队,先进先出，向队尾添加一个数据
myqueue *insertQueue(myqueue *HQ, int x);
//队列出队，从队头删除一个数据
myqueue *delQueue(myqueue *HQ);

//入栈，先进后出，栈顶压入一个数据
myqueueStack *push1(myqueueStack *HQ, int x);
//出栈，栈顶弹出一个数据
myqueueStack *pop1(myqueueStack *HQ);

//判断系统大小端模式
EINT32 GetSystemEndianMode();


#endif
