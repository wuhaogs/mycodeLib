#ifndef __MY_CODE_H__
#define __MY_CODE_H__
#include "common.h"

//#define ET_PACK_ALIGN(x) __attribute__((packed, aligned(x)))

#define PPAL_CALL_IND_HASH_TABLE_MAX  32
#define PPAL_PKT_HASH_TABLE_MAX       32
#define PPAL_PKT_STATUS_POOL_LEN      150

typedef struct  
{
    EUCHAR h_verlen;                 //4λ�ײ�����+4λIP�汾�� 
    EUCHAR tos;   
    EINT16 total_len;                //16λ�ܳ��ȣ��ֽڣ� 
    EINT16 ident;                    //16λ��ʶ 
    EINT16 frag_and_flags;           //3λ��־λ 
    EUCHAR ttl;                      //8λ����ʱ�� TTL 
    EUCHAR proto;                    //8λЭ�� (TCP, UDP ������) 
    EINT16 checksum;                 //16λIP�ײ�У��� 
    EUINT32 sourceIP;                //32λԴIP��ַ 
    //ECHAR data1[1]; 
    EUINT32 destIP;                  //32λĿ��IP��ַ 
    ECHAR data[0];                   //������ʼ�ֽ�
} ET_PACK_ALIGN(1) IP_PKG;

typedef struct  
{
    EUCHAR h_verlen;                 //4λ�ײ�����+4λIP�汾�� 
    EUCHAR tos;                      //8λ��������TOS 
    EINT16 total_len;                //16λ�ܳ��ȣ��ֽڣ� 
    EINT16 ident;                    //16λ��ʶ 
    EINT16 frag_and_flags;           //3λ��־λ 
    EUCHAR ttl;                      //8λ����ʱ�� TTL 
    EUCHAR proto;                    //8λЭ�� (TCP, UDP ������) 
    EINT16 checksum;                 //16λIP�ײ�У��� 
    EUINT32 sourceIP;                //32λԴIP��ַ 
    //ECHAR data1[1];    
    EUINT32 destIP;                  //32λĿ��IP��ַ 
    ECHAR data[0];                   //������ʼ�ֽ�
} IP_PKG1;
typedef enum
{
    PKT_IDLE                    = 0,     /* IDLE״̬ */
    WAIT_D_PDGRANT               = 1,     /* �ȴ������ŵ�������Ӧ */
    WAIT_C_ACKU_IND             = 2,
    WAIT_TRANSFER_DATA          = 3,     /* ׼�����ݴ��� */
    WAIT_P_PROTECT              = 4,
    WAIT_P_MAINT                = 5,
    WAIT_P_AHOY                 = 6,
    WAIT_P_ACKU                 = 7,
    WAIT_P_DACKU                = 8,
    WAIT_P_PCLEAR               = 9
}PKT_STATUS_e;

typedef struct
{
    NODE            pPktCalledSta;            /* ��PktCallAddrHash����ָ��ǰ��״̬�� */
    NODE            pPktEvtTagSta;            /* ��PktEventTagHash����ָ��ǰ��״̬�� */
    EINT32          uiPktCalledTimerHandle;   /* CalledStatus��ʱ�� */
    EUINT32         uiCallingAddr;            /* ���е�ַ */
    EUINT32         uiCalledAddr;             /* ���е�ַ */
    EUINT32         uiSel;                    /* ��¼�����¼���ǩ */
    EUINT32         uiTel;                    /* ��¼�����¼���ǩ */
    EUCHAR          unTimeSlot;               /* ҵ���ŵ�ʱ϶�� */
    EUCHAR          unBsrId;                  /* ��ʾbsr��� */
    EUCHAR          unAddrType;               /* MS��ַ����IG */
    PKT_STATUS_e    ePktStatus;               /* ��¼���з��ĺ���״̬ */
    EUCHAR          unChanType;               /* �����ŵ����ͣ�0Ϊ�����ͷ����ŵ���1Ϊר���ͷ����ŵ�*/

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

//16�����ַ�ת��Ϊ��ֵ
EUCHAR a2x(EUCHAR ch);

//���ַ�������ת������ͨ�ֽ�����
EINT32 ArrayString2Byte(EUCHAR *str2,EUCHAR *str1);

//��ʼ�����鱻�е�ַ��ϣ��
EINT32 InitPktCalledAddrHashTable();

//��ʼ�����鱻�б�ǩ��ϣ��
EINT32 InitPktCalledEvtTagHashTable();

//��ʼ�����鱻�л����
EINT32 InitPktCalledStatusPool();

//�ָ����鱻�л����
EINT32	RestorePktCalledStaPool();

//���ݵ�ַ���ҷ��鱻�е�ַ״̬��
EINT32 SearchPktCalledSta(PPAL_PKT_CALLED_STATUS_t **ppPktSta, EUINT32 uiCalledAddr);

//���ݱ�ǩ���ҷ��鱻�б�ǩ״̬������ӽڵ��ַ��ʱ���е�ַƫ�ƣ��ʲ��ҵ�ʱ����Ҫ��ַƫ��
EINT32 SearchPktCalledStaFromEvtTag(PPAL_PKT_CALLED_STATUS_t **ppPktSta,EUINT32 uiEventTag);

//�ӷ��鱻�л�����л�ȡһ���ַ
PPAL_PKT_CALLED_STATUS_t  *GetPktCalledStaFromPool();

//�ӷ��鱻�е�ַ��ϣ����ɾ��һ���ڵ��ַ���򻺴���з���һ���ڵ�
EINT32 DeletePktStaFromCalledAddrHash(PPAL_PKT_CALLED_STATUS_t  *pCalledSta);

//�ӷ��鱻�б�ǩ��ϣ����ɾ��һ���ڵ��ַ���򻺴���з���һ���ڵ�
EINT32 DeletePktStaFromCalledEvtTagHash(PPAL_PKT_CALLED_STATUS_t  *pPktSta);

//���һ���ڵ��ַ�����鱻�е�ַ��ϣ��
EINT32 AddPktStaToCalledAddrHash(PPAL_PKT_CALLED_STATUS_t *pCalledSta);

//���һ���ڵ��ַ�����鱻�б�ǩ��ϣ��
EINT32 AddPktEvtTagToCalledAddrHash(PPAL_PKT_CALLED_STATUS_t *pCalledSta);

//���ݵ�ַ��ȡ������ֵ
EUINT32 GetPPALPktCallAddrHashIndex(EUINT32 uiAddr);

//���ݱ�ǩ��ȡ������ֵ
EUINT32 GetPPALPktEvtTagHashIndex(EUINT32 uiEventTag);

//����鱻�л�����з���һ���ڵ�
EINT32 PutPktCalledStaToPool(PPAL_PKT_CALLED_STATUS_t *pCalledSta);

//��ʼ�����鱻��ҵ��
void InitTestList();

//������Ľ���
mynode *create();
//������ⳤ
int lengthS(mynode *head);
//�������ӡ
void printS(mynode *head);
mynode *create1();


//������ɾ���ڵ�
mynode *delS(mynode *head, int num);
//��������ӵ����β�������¼���Ľ�㣬���µĽ��β
mynode *insertTailS(mynode *tail, int num);
//��ȡ�������β���
mynode *GetTailS(mynode *head);
//��������������ͷ�ڵ�
mynode *createS();
//�����������,����ͷ���
mynode *sortS(mynode *head);
//����������ã�����ͷ���
mynode *reverseS(mynode *head);
void searchmid(mynode *head, mynode *mid);

//˫�������ӣ���ӵ�β��,�����¼���Ľ��
mydnode *insertTailD(mydnode *tail, int num);
//����˫��������ͷ�ڵ�
extern mydnode *createD();
//˫�����ɾ��������ͷ���
mydnode *delD(mydnode *head, int num);
//��ȡ˫�����β���
mydnode *GetTailD(mydnode *head);
//˫����ⳤ
int lengthD(mydnode *head);
//˫�����ӡ
void printD(mydnode *head);

//�������,�Ƚ��ȳ������β���һ������
myqueue *insertQueue(myqueue *HQ, int x);
//���г��ӣ��Ӷ�ͷɾ��һ������
myqueue *delQueue(myqueue *HQ);

//��ջ���Ƚ������ջ��ѹ��һ������
myqueueStack *push1(myqueueStack *HQ, int x);
//��ջ��ջ������һ������
myqueueStack *pop1(myqueueStack *HQ);

//�ж�ϵͳ��С��ģʽ
EINT32 GetSystemEndianMode();


#endif
