#include "common.h"
#include "mytest.h"
//#include "mycode.h"
#include "../core/mycode.h" //否则需要在test目录下的makefile中指定包含core目录下的头文件

#if 1
char *GetECNPrimCfgEthernet2()
{
    static char ipstr[20] = {0};

    memcpy(ipstr,"11.11.11.11",sizeof("11.11.11.11"));

    return ipstr;
}

EINT32 PpalTestHashListaddlist(EUINT32 uiTaddr,EUINT32 uiTel)
{
    //MP_BLK  *pSduCAhoy    = NULL;
    //int kkk=0;
    PPAL_PKT_CALLED_STATUS_t   *pPktCalledSta     = NULL;
    PPAL_PKT_CALLED_STATUS_t   *p2PktCalledSta    = NULL;
    p2PktCalledSta = GetPktCalledStaFromPool();

    /* 获取空闲状态机 */
    pPktCalledSta = GetPktCalledStaFromPool();
    if (NULL == pPktCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Function GetPktCalledStaFromPool has been failed");
        return ETERROR;
    }


    PPAL_LOG_PRM2("1:getpooladdr:%p,%p.\n",pPktCalledSta,p2PktCalledSta);

    p2PktCalledSta->ePktStatus = WAIT_C_ACKU_IND;
    p2PktCalledSta->uiCallingAddr = 0xFFFD01;
    p2PktCalledSta->uiCalledAddr = uiTaddr;
    p2PktCalledSta->unChanType = 1;
    p2PktCalledSta->uiSel      = 0xf;
    p2PktCalledSta->uiTel      = uiTel;

    PPAL_LOG_PRM2("3-1:getpooladdr:%p,%p.\n",&(pPktCalledSta->pPktCalledSta),&(p2PktCalledSta->pPktCalledSta));
    PPAL_LOG_PRM2("4-1:getpooladdr:%p,%p.\n",&(pPktCalledSta->pPktEvtTagSta),&(p2PktCalledSta->pPktEvtTagSta));
    memcpy(pPktCalledSta,p2PktCalledSta,sizeof(PPAL_PKT_CALLED_STATUS_t));

    PPAL_LOG_PRM2("2:getpooladdr:%p,%p.\n",pPktCalledSta,p2PktCalledSta);
    PPAL_LOG_PRM2("3-2:getpooladdr:%p,%p.\n",&(pPktCalledSta->pPktCalledSta),&(p2PktCalledSta->pPktCalledSta));
    PPAL_LOG_PRM2("4-2:getpooladdr:%p,%p.\n",&(pPktCalledSta->pPktEvtTagSta),&(p2PktCalledSta->pPktEvtTagSta));

    PPAL_LOG_INFO("AddPktStaToCalledAddrHash 创建新的状态机\n");
    PPAL_LOG_PRM1("pPktCalledSta.uiCalledAddr    = %d.\n", pPktCalledSta->uiCalledAddr);
    PPAL_LOG_PRM1("pPktCalledSta.ePktStatus      = %d.\n", pPktCalledSta->ePktStatus);

    /* 添加到被叫方哈希表中 */
    if (ETERROR == AddPktStaToCalledAddrHash(pPktCalledSta))
    {
        if (ETERROR == PutPktCalledStaToPool(pPktCalledSta))
        {
            PPAL_LOGPRINT_ERROR("Function PutPktCalledStaToPool has been failed");
            return ETERROR;
        }
        pPktCalledSta = NULL;

        PPAL_LOGPRINT_ERROR("Function AddPktStaToCalledAddrHash has been failed");
        return ETERROR;
    }

    pPktCalledSta->ePktStatus = WAIT_TRANSFER_DATA;
    pPktCalledSta->unChanType = 1;

    if (ETERROR == AddPktEvtTagToCalledAddrHash(pPktCalledSta))
    {
        if (ETERROR == DeletePktStaFromCalledAddrHash(pPktCalledSta))
        {
            PPAL_LOGPRINT_ERROR("Function DeletePktStaFromCalledAddrHash has been failed");
            return ETERROR;
        }
        pPktCalledSta = NULL;

        PPAL_LOGPRINT_ERROR("Function AddPktEvtTagToCalledAddrHash has been failed");
        return ETERROR;
    }
    PPAL_LOGPRINT_INFO(    "AddPktEvtTagToCalledAddrHash success!\n");

    return ETOK;
}

EINT32 PpalTestHashListSearchStatus(EUINT32 uiTaddr,EUINT32 uiTel)
{
    PPAL_PKT_CALLED_STATUS_t *pPktSta = NULL;

    if (ETOK == SearchPktCalledSta(&pPktSta, uiTaddr))
    {
        PPAL_LOG_INFO("SearchPktCalledSta OK.\n\n\n");
    }

    pPktSta = NULL;

    if (ETOK == SearchPktCalledStaFromEvtTag(&pPktSta, uiTel))
    {
        PPAL_LOG_INFO("SearchPktCalledStaFromEvtTag OK.\n\n\n");
    }


    /* 释放状态机 */
    if (ETERROR == DeletePktStaFromCalledEvtTagHash(pPktSta))
    {
        PPAL_LOGPRINT_ERROR("Function DeletePktStaFromCalledEvtTagHash has been failed");
        return ETERROR;
    }
    if (ETERROR == DeletePktStaFromCalledAddrHash(pPktSta))
    {
        PPAL_LOGPRINT_ERROR("Function DeletePktStaFromCalledAddrHash has been failed");
        return ETERROR;
    }
    return ETOK;

}


void TestList(EUINT32 uiTaddr,EUINT32 uiTel)
{
    InitTestList();
    PpalTestHashListaddlist(uiTaddr,uiTel);
    PpalTestHashListSearchStatus(uiTaddr,uiTel);
}

//位域大小端测试
void testBitStruct()
{
    BitStruct b = {0};
    Struct b1 = {0};
    /* a在内存中存放如下：    0X454D0000
      “EMC EXAM”内存中如下：0X454D...
      notice:字符串在内存中顺序存储，大于8字节的数在内存中需要考虑大小端，window是小端。
    */
    EUINT32 a = 0x00004D45;//M、E的ascii值0x4D，0x45
    EUINT32 c = 0x0000CDAB;
    memcpy(&b,"EMC EXAMINATION",sizeof(b));

    printf("M E:0x %x,%x\n",'M','E');
    PPAL_LOG_PRM2("BitStruct:%d,%d\n",b.b1,b.b2);

    memset(&b,0,sizeof(b));

    /* notice：位域内存中存放。
       若是小端，
       16位的系统，数0XABCD存放如下：0X4000：0xCD;0X4001:0XAB;
       位域存储的数比如0XABCD，1010 1011 1100 1101，在内存中每一个字节从低位开始存储：1101 0101 1011 0011。
       注意：先存AB:1101 0101，再存CD:1011 0011
       */
    memcpy(&b,&a,sizeof(b));
    PPAL_LOG_PRM2("a BitStruct:%X,%X\n", b.b1, b.b2);

    memcpy(&b, &c, sizeof(b));
    PPAL_LOG_PRM2("c BitStruct:%X,%X\n", b.b1, b.b2);

    memcpy(&b1, &a, sizeof(b1));

    //PPAL_LOG_PRM4("Struct:[0x%x]%X,[0x%x]%X\n",&b1.b1,b1.b1, &b1.b2, b1.b2);
}
#if 1

//测试单链表
void testlistS()
{
    mynode *head = NULL;

    printf("test single linked list.\n");

    head = createS();
    printS(head);

    head = sortS(head);
    printS(head);

    head = reverseS(head);
    printS(head);
}
//测试双链表

void testlistD()
{
    int cnt = 10;
    mydnode *head;
    int x;
    head=createD();
    printD(head);

    while(cnt)
    {
        printf("\nplease del a node:");
        scanf("%d", &x);

        head = delD(head, x);
        printD(head);

        printf("\nplease insert a node:");
        scanf("%d", &x);

        insertTailD(GetTailD(head), x);
        printD(head);

        cnt--;
    }
}
#endif
//测试队列
void testqueue()
{
    printf("test queue:%d\n",sizeof(myqueue));
}
//测试栈
void teststack()
{
    printf("test queue:%d\n", sizeof(myqueue));
}

void pzhizhen()
{
    //TEST_NODE_T *ptNode= NULL;
    EUINT32 a=0x11;
    //EUINT32 b=0x22;
    EUINT32 c=0x33;

    EUINT32 *p1=&a;
    EUINT32 *p3=&c;

    printf("qian:&a:%p,&c:%p\n",&a,&c);

    printf("qian:p1:%p,p2:%p\n",p1,p3);

    memcpy(p1,p3,4);

    printf("hou :p1:%p,p2:%p\n",p1,p3);
}
#endif
void testfile()
{
	EINT32 fd=0;
	EINT32 fileLen;
	ECHAR pBuf[12];
	fd = OpenBinFile("1.txt", OPEN_FILE_RWA);
	if(fd > 0)
	{
		printf("OpenBinFile ok\n");
		if ((fileLen = WriteBinFile(fd, "1234567890", 10)) == -1)
            return;

        printf("WriteBinFile ok\n");
		if((fileLen = ReadBinFile(fd, pBuf, 12)) > 0)
		{
		printf("ReadBinFile ok\n");
		}
		printf("CloseBinFile ok\n");
		CloseBinFile(fd);
	}
	else
	{
	printf("OpenBinFile fail\n");
	}
}

typedef struct
{
char t1;
}ET_PACK_ALIGN(4) AA1;
typedef struct
{
char t1;
char t2;
}ET_PACK_ALIGN(4) AA2;
typedef struct
{
char  t1;
short t2;
char t3;
}ET_PACK_ALIGN(4) AA3;
typedef struct
{
char  t1;
short t2;
int t3;
}ET_PACK_ALIGN(4) AA4;
//测试柔性数组
void testroushuzu()
{
	printf("sizeof(IP_PKG)=%d\n",sizeof(IP_PKG));
	char buf[1024];
	char test[]={0x00,0x11,0x00,0x33,0x44,0xff};
	char *p;

	IP_PKG *ptPKT=(IP_PKG *)buf;
	if(NULL == ptPKT)
	{
	return;
	}
	//memset(ptPKT->data,0xff,12);
	memcpy(ptPKT->data,test,12);
	//printf("tPKT.data:%d,%d,%d.",ptPKT->data[0],ptPKT->data[1],ptPKT->[11]);

	p=ptPKT->data;

	printf("sizeof(IP_PKG1)=%d\n",sizeof(IP_PKG1));
	printf("sizeof(ptPKT->data)=%d,sizeof(*p)=%d.\n",sizeof(ptPKT->data),sizeof(*p));
	printf("p[0]=%x,p[1]=%x,p[2]=%x,p[3]=%x,p[11]=%x,p[20]=%x,\n",
		p[0],p[1],p[2],p[3],p[11],p[20]);


  	printf("%d,%d,%d,%d\n",
  	sizeof(AA1),sizeof(AA2),sizeof(AA3),sizeof(AA4));
}



#define step 1+1
void plus(int *p)
{
        static int i=0x10;
        int j=0;
		//printf("*p=%d\n ",*p);
        if(NULL==p)
        {
                return;
        }

        i+=2;

        //0-17累加;0-19累加
        for(;j<i*step;++j)
        {
                *p+=j;
        }
        return;
}

void mstest()
{
        int a[4]={1,2,3,4};
        int k;
        plus(a);
        plus(a+1);
        plus(&(a[2]));
        for(k=1;k<4;++k)
        {
                printf("a[%d] = %d",k,a[k]);
        }
        printf("\n");
}

void tt2()
{

	unsigned char  a[10]  = {0};
	unsigned int   b[10]  = {0};
	unsigned long  c[10]  = {0};
	unsigned int i;
	memset(a,1,sizeof(a));
	memset(b,0x0201,sizeof(b));//第二个参数只会取一个字节对b区域进行复位
	memset(c,1,sizeof(c));

	for(i=0;i<10;i++)
	{
	printf("a[%d]=%.8x ",i,a[i]);
	printf("b[%d]=%.8x ",i,b[i]);
	printf("c[%d]=%.8lx\r\n",i,c[i]);//注意lx 对长整型的打印
    }
}
ECHAR *PrintStrIP(EUINT32 uiIP)
{
    static ECHAR s_ipStr[20]	= {0};
    if(GetIpStr(uiIP,s_ipStr) == ETERROR)
    {
    	printf("Error in GetIpStr");
    }
    return s_ipStr;
}
void testIP()
{
   printf("IP1:%s\n",PrintStrIP(0x10223344));
   printf("IP2:%s\n",PrintStrIP(0x11223344));
   printf("IP3:%s\n",PrintStrIP(0x12223344));
   printf("IP4:%s\n",PrintStrIP(0xFFFFFFFF));
   printf("IP5:%s\n",PrintStrIP(0x44332210));
}
void testSwitch()
{
    int i;
    for(i=-1;i<4;i++)
    {
        switch(i)
        {
        case -1:
        printf("testSwitch[%d]\n",i);
        break;

        case 0:
        printf("testSwitch[%d]\n",i);
        break;

        default:
        printf("[default]testSwitch[%d]\n",i);
        break;
        }
    }
}

#ifdef _DEBUG
void initMytest_T()
{
    //TestList(16515088,323);
    //testBitStruct();
    //testlistS();
    //testlistD();
    //testqueue();
    //pzhizhen();
    //testfile();
    //testroushuzu();
    //mstest();
    //tt2();
    testIP();
    //testSwitch();
}
#endif
