#include "common.h"
#include "mycode.h"


LIST g_pktCalledStatusPool;
PPAL_PKT_CALLED_STATUS_t		*g_pktCalledStuPoolHead	= NULL;
LIST g_pktCalledEvtTagHashTable[PPAL_PKT_HASH_TABLE_MAX];
LIST g_pktCalledAddrHashTable [PPAL_PKT_HASH_TABLE_MAX];

//16进制字符转换为数值
EUCHAR a2x(EUCHAR ch)
{
    switch(ch)
    {
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'A':
    case 'a':
        return 10;
    case 'B':
    case 'b':
        return 11;
    case 'C':
    case 'c':
        return 12;
    case 'D':
    case 'd':
        return 13;
    case 'E':
    case 'e':
        return 14;
    case 'F':
    case 'f':
        return 15;
    default:
        break;
    }
    return 0;
}
#if 1
/************************************************************************
* Function     :ArrayString2Byte
* Description : 字符转换为普通字节数组
* Input         :str1
* Output        :str2
* Return       : 无
*
* Others       :2015.07.15,str2分配的数组长度>str1/2
************************************************************************/
EINT32 ArrayString2Byte(EUCHAR *str2,EUCHAR *str1)
{
    //将字符串数组转化成字节数组
    //char str1[] = "B0002328FFFEC0FC0001";
    //char str2[12];
    int i=0;
    if(NULL==str1 || NULL==str2)
    {
        return -1;
    }
    while(str1[i])
    {
        str2[i >> 1] = (a2x(str1[i]) << 4) | a2x(str1[i + 1]);
        i += 2;
    }
    str2[i >> 1] = '\0';
    return 0;
}

//初始化分组被叫地址哈希表
EINT32 InitPktCalledAddrHashTable()
{
    EUINT32 i = 0;

    for (i = 0; i < PPAL_PKT_HASH_TABLE_MAX; i++)
    {
        /* 初始化哈希表 */
        lstInit(&g_pktCalledAddrHashTable[i]);
    }

    return ETOK;
}

//初始化分组被叫标签哈希表
EINT32 InitPktCalledEvtTagHashTable()
{
    EUINT32 i = 0;

    for (i = 0; i < PPAL_PKT_HASH_TABLE_MAX; i++)
    {
        /* 初始化哈希表 */
        lstInit(&g_pktCalledEvtTagHashTable[i]);
    }

    return ETOK;
}
//初始化分组被叫缓存池
EINT32 InitPktCalledStatusPool()
{
    EUINT32 i = 0;
    PPAL_PKT_CALLED_STATUS_t *pCalledSta    = NULL;
    PPAL_PKT_CALLED_STATUS_t *pAllCalledSta = NULL;

    /* 初始化g_pktCallingStatusPool链表 */
    lstInit(&g_pktCalledStatusPool);

    pAllCalledSta = (PPAL_PKT_CALLED_STATUS_t *)malloc(sizeof(PPAL_PKT_CALLED_STATUS_t) * PPAL_PKT_STATUS_POOL_LEN);
    if (NULL == pAllCalledSta)
    {
        //PPAL_LOGPRINT_ERROR("Memory allocation pAllPktCalledSta has been failed");
        return ETERROR;
    }

    pCalledSta = pAllCalledSta;

    /* 保存头节点地址 */
    g_pktCalledStuPoolHead = pAllCalledSta;

    for (i = 0; i < PPAL_PKT_STATUS_POOL_LEN; i++)
    {
        /* 初始化新申请节点 */
        memset(pCalledSta, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

        /* 加入到缓冲池链表结尾  */
        lstAdd(&g_pktCalledStatusPool, (NODE *)pCalledSta);

        pCalledSta++;
    }

    return ETOK;
}

//恢复分组被叫缓存池
EINT32	RestorePktCalledStaPool()
{
    EUINT32 i = 0;
    PPAL_PKT_CALLED_STATUS_t *pCalledSta    = NULL;

    PPAL_LOGPRINT_ERROR("Lucky Boy! Init Pkt Called pool!\n");

    InitPktCalledAddrHashTable();
    InitPktCalledEvtTagHashTable();

    /* 初始化g_pktStatusPool链表 */
    lstInit(&g_pktCalledStatusPool);

    pCalledSta = g_pktCalledStuPoolHead;
    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Lucky Boy! pkt called pool head is null!\n");
        return ETERROR;
    }

    for (i = 0; i < PPAL_PKT_STATUS_POOL_LEN; i++)
    {
        /* 初始化新申请节点 */
        memset(pCalledSta, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

        /* 加入到缓冲池链表结尾  */
        lstAdd(&g_pktCalledStatusPool, (NODE *)pCalledSta);

        pCalledSta++;
    }

    return ETOK;
}

//根据地址查找分组被叫地址状态机
EINT32 SearchPktCalledSta(PPAL_PKT_CALLED_STATUS_t **ppPktSta, EUINT32 uiCalledAddr)
{
    EUINT32 uiIndex = 0;
    PPAL_PKT_CALLED_STATUS_t *pCalledStaTmp = NULL;
    PPAL_PKT_CALLED_STATUS_t *pStaTmp		= NULL;

    /* 获取index值 */
    uiIndex = GetPPALPktCallAddrHashIndex(uiCalledAddr);
    pCalledStaTmp = (PPAL_PKT_CALLED_STATUS_t *)lstFirst(&g_pktCalledAddrHashTable[uiIndex]);

    PPAL_LOG_INFO("SearchPktCalledSta\n");
    PPAL_LOG_PRM2("find pPktCalledSta  EventTag Index    = %d,uiCalledAddr = %d.\n",uiIndex,uiCalledAddr);

    while(NULL != pCalledStaTmp)
    {
        PPAL_LOG_PRM1("fistNodeAddr:%p\n",pCalledStaTmp);

        if(pCalledStaTmp->uiCalledAddr == uiCalledAddr)
        {
            PPAL_LOGPRINT_INFO("PktCalledStatus is in pktCalledAddrHashTable\n");
            *ppPktSta = pCalledStaTmp;

            return ETOK;
        }
        else if (pCalledStaTmp->uiCalledAddr == 0)
        {
            PPAL_LOG_PRM1("0 地址 pPktCalledSta Index = %d\n", uiIndex);

            pStaTmp = pCalledStaTmp;
            pCalledStaTmp = (PPAL_PKT_CALLED_STATUS_t*)lstNext((NODE*)pCalledStaTmp);

            lstDelete(&g_pktCalledAddrHashTable[uiIndex], (NODE *)pStaTmp);
            /* 将状态机置为空闲 */
            memset(pStaTmp, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

            /* 将空闲状态机放回内存池 */
            if(ETERROR == PutPktCalledStaToPool(pStaTmp))
            {
                PPAL_LOGPRINT_ERROR("Function PutPktCalledStaToPool has been failed");
                return ETERROR;
            }

            continue;
        }

        pCalledStaTmp = (PPAL_PKT_CALLED_STATUS_t*)lstNext((NODE*)pCalledStaTmp);
    }

    PPAL_LOGPRINT_INFO("PktCalledStatus is not in PktCalledHashTable\n");

    return ETERROR;
}

//根据标签查找分组被叫标签状态机，添加节点地址的时候，有地址偏移，故查找的时候需要地址偏移
EINT32 SearchPktCalledStaFromEvtTag(PPAL_PKT_CALLED_STATUS_t **ppPktSta,EUINT32 uiEventTag)
{
    EUINT32 uiIndex = 0;
    NODE    *pNodeTmp = NULL;
    PPAL_PKT_CALLED_STATUS_t *pPktStaTmp = NULL;

    PPAL_LOGPRINT_INFO("SearchPktCalledStaFromEvtTag\n");

    /* 获取index值 */
    uiIndex  = GetPPALPktEvtTagHashIndex(uiEventTag);
    pNodeTmp = lstFirst(&g_pktCalledEvtTagHashTable[uiIndex]);

    PPAL_LOG_PRM2("find pPktCalledSta  EventTag Index    = %d,sel = %d\n",uiIndex,uiEventTag);

    while(NULL != pNodeTmp)
    {
        pPktStaTmp = (PPAL_PKT_CALLED_STATUS_t *)(pNodeTmp-1); /*地址偏移*/

        PPAL_LOG_PRM1("fistNodeAddr:%p\n",pPktStaTmp);

        if(pPktStaTmp->uiTel == uiEventTag)
        {
            PPAL_LOGPRINT_INFO(    "PktStatus is in pktHashTable\n");
            *ppPktSta = pPktStaTmp;

            return ETOK;
        }

        PPAL_LOG_PRM1("pPktStaTmp->uiTel = %d\n", pPktStaTmp->uiTel);

        pNodeTmp = lstNext(pNodeTmp);
    }
    PPAL_LOGPRINT_INFO("EventTag is not in pktCalledHashTable\n");

    return ETERROR;
}

//从分组被叫缓存池中获取一块地址
PPAL_PKT_CALLED_STATUS_t  *GetPktCalledStaFromPool()
{
    PPAL_PKT_CALLED_STATUS_t *pCalledSta = NULL;

    /* 从 g_pktCalledStatusPool 内存池中获取第一个节点并从内存池中删除 */
    pCalledSta = (PPAL_PKT_CALLED_STATUS_t*)lstGet(&g_pktCalledStatusPool);

    /* g_pktCalledStatusPool 内存池为空，未获取到节点 */
    if (NULL == pCalledSta)
    {
        if( ETOK == RestorePktCalledStaPool() )
            pCalledSta = (PPAL_PKT_CALLED_STATUS_t*)lstGet(&g_pktCalledStatusPool);

        return pCalledSta;
    }

    /* 初始化内存空间 */
    memset(pCalledSta, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

    return pCalledSta;
}

//从分组被叫地址哈希表中删除一个节点地址并向缓存池中返还一个节点
EINT32 DeletePktStaFromCalledAddrHash(PPAL_PKT_CALLED_STATUS_t  *pCalledSta)
{
    EUINT32 uiIndex = 0;

    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Function parameter pPktDataCalledSta is NULL");
        return ETERROR;
    }

    uiIndex = GetPPALPktCallAddrHashIndex(pCalledSta->uiCalledAddr);

    PPAL_LOG_PRM1("删除 pPktDataCalledSta  Index    = %d\n", uiIndex);

    lstDelete(&g_pktCalledAddrHashTable[uiIndex], (NODE*)pCalledSta);

    /* 将状态机置为空闲 */
    memset(pCalledSta, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

    /* 将空闲状态机放回内存池 */
    if(ETERROR == PutPktCalledStaToPool(pCalledSta))
    {
        PPAL_LOGPRINT_ERROR("Function PutPktCalledStaToPool has been failed");
        return ETERROR;
    }

    return ETOK;
}

//从分组被叫标签哈希表中删除一个节点地址并向缓存池中返还一个节点
EINT32 DeletePktStaFromCalledEvtTagHash(PPAL_PKT_CALLED_STATUS_t  *pPktSta)
{
    EUINT32 uiIndex  = 0;
    NODE   *pNodeTmp = NULL;

    if (NULL == pPktSta)
    {
        PPAL_LOGPRINT_ERROR("Function parameter pPktSta is NULL");
        return ETERROR;
    }
    uiIndex = GetPPALPktEvtTagHashIndex(pPktSta->uiTel);

    PPAL_LOG_PRM1("删除 pPktCalledSta  eventTag Index    = %d\n", uiIndex);

    pNodeTmp = &(pPktSta->pPktEvtTagSta);

    if (NULL != pNodeTmp)
    {
        lstDelete(&g_pktCalledEvtTagHashTable[uiIndex], pNodeTmp);
        pNodeTmp = NULL;
    }

    return ETOK;
}

//添加一个节点地址到分组被叫地址哈希表
EINT32 AddPktStaToCalledAddrHash(PPAL_PKT_CALLED_STATUS_t *pCalledSta)
{
    EUINT32 uiIndex = 0;

    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Function parameter pPktCalledSta is NULL");
        return ETERROR;
    }

    /* 获取index值 */
    uiIndex = GetPPALPktCallAddrHashIndex(pCalledSta->uiCalledAddr);

    PPAL_LOG_PRM2("add pPktCalledSta  Index = %d,called addr=%d.\n", uiIndex,pCalledSta->uiCalledAddr);

    /* 添加到g_pktCalledAddrHashTable */
    lstAdd(&g_pktCalledAddrHashTable[uiIndex], (NODE*)pCalledSta);

    PPAL_LOG_PRM1("addnode addr:%p\n",(NODE*)pCalledSta);

    return ETOK;
}

//添加一个节点地址到分组被叫标签哈希表
EINT32 AddPktEvtTagToCalledAddrHash(PPAL_PKT_CALLED_STATUS_t *pCalledSta)
{
    EUINT32 uiIndex = 0;
    NODE   *pNodeTmp = 0;

    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Function parameter pPktCalledSta is NULL");
        return ETERROR;
    }

    /* 获取index值 */
    uiIndex = GetPPALPktEvtTagHashIndex(pCalledSta->uiTel);

    PPAL_LOG_PRM2("add pPktCalledSta  EventTag Index    = %d,Tel = %d\n", uiIndex, pCalledSta->uiTel);

    pNodeTmp = &(pCalledSta->pPktEvtTagSta);  /*地址偏移*/

    PPAL_LOG_PRM1("addnode addr:%p\n",pNodeTmp);

    /* 添加到g_pktCalledEvtTagHashTable */
    lstAdd(&g_pktCalledEvtTagHashTable[uiIndex], pNodeTmp);

    return ETOK;
}

//根据地址获取其索引值
EUINT32 GetPPALPktCallAddrHashIndex(EUINT32 uiAddr)
{
    EUINT32 uiIndex = 0;

    uiIndex = uiAddr & (PPAL_PKT_HASH_TABLE_MAX - 1);

    return uiIndex;
}

//根据标签获取其索引值
EUINT32 GetPPALPktEvtTagHashIndex(EUINT32 uiEventTag)
{
    EUINT32 uiIndex = 0;

    uiIndex = uiEventTag & (PPAL_PKT_HASH_TABLE_MAX - 1);

    return uiIndex;
}

//向分组被叫缓存池中返还一个节点
EINT32 PutPktCalledStaToPool(PPAL_PKT_CALLED_STATUS_t *pCalledSta)
{
    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Function parameter pPktCalledSta is NULL");
        return ETERROR;
    }

    lstAdd(&g_pktCalledStatusPool, (NODE*)pCalledSta);

    return ETOK;
}
//初始化分组被叫业务
void InitTestList()
{
    InitPktCalledAddrHashTable();
    InitPktCalledEvtTagHashTable();
    InitPktCalledStatusPool();
}
//单链表的建立
mynode *create()
{
    mynode *head=NULL, *p=NULL, *s=NULL;
    int x, cycle = 1;
    head = (mynode *)malloc(sizeof(mynode));
    p = head;
    while (cycle)
    {
        printf("\nplease input the data:");
        scanf("%d",&x);
        if (x!=0)
        {
            s = (mynode *)malloc(sizeof(mynode));
            s->data = x;
            printf("\n%d",s->data);

            p->next = s;
            p = s;
            printf("\npdta:%d", p->data);


        }
        else
        {
            cycle = 0;
        }
    }
    head = head->next;
    p->next = NULL;
    printf("\n yyy %d",head->data);

    return head;
}


//单链表测长
int lengthS(mynode *head)
{
    int n = 0;
    mynode *p = head;
    while (p != NULL)
    {
        p = p->next;
        n++;
    }
    return n;
}
//单链表打印
void printS(mynode *head)
{
    mynode *p;
    int n=lengthS(head);

    printf("\nprintf,these %d record are:\n", n);

    p = head;
    while (p!=NULL)
    {
        printf(" %d  ",p->data);
        p = p->next;

    }
    printf("\nprintf over\n");
}
//单链表删除节点
mynode *delS(mynode *head,int num)
{
    mynode *p1 =NULL;
    mynode *p2 =NULL;
    p1 = head;
    while (num!=p1->data&&p1->next!=NULL)
    {
        p2 = p1;
        p1 = p1->next;

    }
    //跳出循环的时候，P1指向目标结点，即将要删除的结点,P2指向目标结点的前一个结点
    if (num == p1->data)
    {
        if(p1==head)
        {
            head = p1->next;
            free(p1);
        }
        else
        {
            p2->next = p1->next;
        }
    }
    else
    {
        printf("\n %d could not been found",num);
    }
    return head;
}
//单链表添加节点
mynode *insert(mynode *head,int num)
{
    mynode *p0 =NULL;
    mynode *p1 =NULL;
    mynode *p2 =NULL;
    //*p2;
    p1 = head;
    p0 = (mynode *)malloc(sizeof(mynode));
    p0->data = num;
    while(p0->data > p1->data && p1->next !=NULL)
    {
        //大于P1的结点单独存于P2
        p2 = p1; p1 = p1->next;
    }
    if(p0->data <= p1->data)
    {
        if(head == p1)
        {
            //插入头节点之前
            p0->next = p1; head = p0;
        }
        else
        {
            //插入中间结点
            p2->next = p0; p0->next = p1;
        }
    }
    else
    {
        //插入尾结点
        p1->next = p0; p0->next = NULL;
    }
    return head;
}
//单链表添加到结点尾，返回新加入的结点，即新的结点尾
mynode *insertTailS(mynode *tail, int num)
{
    //pn是新加入的结点
    mynode *pn, *p;

    p = tail;
    pn = (mynode *)malloc(sizeof(mynode));
    pn->data = num;

    if (p==NULL)
    {
        pn->next = NULL;
        return pn;
    }
    //插入尾结点
    p->next = pn; pn->next = NULL;

    return pn;
}
//获取单链表的尾结点
mynode *GetTailS(mynode *head)
{
    mynode *p;
    p = head;
    if (p == NULL || p->next == NULL)
    {
        return p;
    }
    while (p->next != NULL)
    {
        p = p->next;
    }
    //跳出循环，即找到尾结点
    return p;
}
//创建单链表，返回头节点
mynode *createS()
{
    mynode *head = NULL, *p = NULL, *tail;
    int x, cycle = 1;

    while (cycle)
    {
        printf("\nplease input the data:");
        scanf("%d", &x);
        if (x != 0)
        {
            //p结点的下一个结点加入一个结点，值为x，返回此新结点
            tail = insertTailS(p, x);
            if(tail!= NULL)
            {
                //若最开始P结点为空，新加入的结点即是头结点
                if (p == NULL)
                {
                    head = tail;
                }
                //p指向尾结点，开始新一轮输入
                p = tail;
                printf("\ntail:%d",p->data);
            }

        }
        else
        {
            cycle = 0;
        }
    }
    p->next = NULL;
    printf("\n head is %d.\n", head->data);

    return head;
}
//单链表的排序,返回头结点
mynode *sortS(mynode *head)
{
    mynode *p  =NULL;
    //mynode *p2 =NULL;
    //mynode *p3 =NULL;

    int n, temp,j,i;
    n = lengthS(head);
    if(head==NULL || head->next==NULL)
    {
        return head;
    }
    p = head;
    for (j = 1; j < n;++j)
    {
        p = head;
        for (i = 0; i < n - j;++i)
        {
            if(p->data > p->next->data)
            {
                temp = p->data; p->data = p->next->data; p->next->data = temp;
            }
            p = p->next;
        }
    }
    return head;
}
//单链表的逆置，返回头结点
mynode *reverseS(mynode *head)
{
    mynode *p1, *p2, *p3;
    if (head ==NULL || head->next ==NULL)
    {
        return head;
    }
    //P1,P2,P2->NExT
    p1 = head;
    p2 = p1->next;
    while (p2)
    {
        p3 = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p3;
    }
    head->next = NULL;
    head = p1;
    return head;
}
void searchmid(mynode *head,mynode *mid)
{
    mynode *temp = head;
    while (head->next->next!=NULL)
    {
        //head 每次移动两个位置，temp每次移动一个位置，当head到达最后一个结点的时候，temp就是中间结点。
        head = head->next->next;
        temp = temp->next;
        mid = temp;
    }
}
//双链表的添加，添加到尾部,返回新加入的结点
mydnode *insertTailD(mydnode *tail,int num)
{
    //pn是新加入的结点
    mydnode *pn, *p;
    //顺序P，pn（新）
    p = tail;

    pn = (mydnode *)malloc(sizeof(mydnode));
    pn->data = num;

    if (p == NULL)
    {
        pn->next = NULL;
        pn->pre = NULL;
        return pn;
    }
    //插入尾结点
    p->next = pn; pn->pre = p; pn->next = NULL;

    return pn;

}
//获取双链表的尾结点
mydnode *GetTailD(mydnode *head)
{
    mydnode *p;
    p = head;
    if (p == NULL || p->next == NULL)
    {
        return p;
    }
    while (p->next!=NULL)
    {
        p = p->next;
    }
    //跳出循环，即找到尾结点
    return p;

}
//双链表的删除，返回头结点
mydnode *delD(mydnode *head, int num)
{
    mydnode *p1;
    //*p2;
    p1 = head;
    if (p1 == NULL)
    {
        printf("head is null.\n");
        return NULL;
    }
    while (num != p1->data && p1->next != NULL)
    {
        printf("p:%d. num=%d\n", p1->data, num);
        p1 = p1->next;


    }
    //跳出循环的时候，P1指向目标结点
    if (num == p1->data)
    {
        //printf("head:%d,p1:%d\n",head->data,p1->data);
        if (p1 == head)
        {
            printf("del head\n");
            //删除头结点
            head = head->next; head->pre = NULL; free(p1);
        }
        else if (p1->next==NULL)
        {

            printf("del tail\n");
            //删除尾结点,即为目标结点的前一个结点找后继结点
            p1->pre->next = NULL;  free(p1);

        }
        else
        {
            printf("del middle\n");
            //删除中间结点p1，p1->pre,p1,p1->next

            p1->pre->next = p1->next;  p1->next->pre = p1->pre;
            free(p1);
        }
    }
    else
    {
        printf("\n %d could not been found", num);
    }
    printf("delD suc,return %d.\n", head->data);
    return head;

}
//创建双链表，返回头节点
mydnode *createD()
{
    mydnode *head = NULL, *p = NULL, *tail;
    int x, cycle = 1;
    //head = (dnode *)malloc(sizeof(dnode));
    //p = head;
    while (cycle)
    {
        printf("\ndouble linked list please input the data:");
        scanf("%d", &x);
        if (x != 0)
        {
            //p结点的下一个结点加入一个结点，值为x，返回此新结点
            tail = insertTailD(p, x);
            if (tail != NULL)
            {
                ////若最开始P结点为空，新加入的结点即是头结点
                if (p == NULL)
                {
                    head = tail;
                }
                //p指向尾结点，开始新一轮输入
                p = tail;
                printf("\ntail:%d", p->data);
            }

        }
        else
        {
            cycle = 0;
        }
    }
    p->next = NULL;
    //head = head->next;
    //head->pre = NULL;
    printf("\n head is %d.\n", head->data);

    return head;
}
//双链表测长
int lengthD(mydnode *head)
{
    int n = 0;
    mydnode *p = head;
    while (p != NULL)
    {
        p = p->next;
        n++;
    }
    return n;
}
//双链表打印
void printD(mydnode *head)
{
    mydnode *p;
    int n = lengthD(head);

    printf("\nprintf,these %d record are:\n", n);

    p = head;
    while (p != NULL)
    {
        printf(" %d  ", p->data);
        p = p->next;

    }
    printf("\nprintf over\n");
}
//队列入队,先进先出，向队尾添加一个数据
myqueue *insertQueue(myqueue *HQ,int x)
{
    mynode *s;
    s = (mynode *)malloc(sizeof(mynode));
    s->data = x;
    s->next = NULL;

    if (HQ->rear== NULL)
    {
        //队列为空，队头 队尾 都指向新结点
        HQ->first = s;     HQ->rear = s;
    }
    else
    {
        //队列不为空，插入队尾，HQ->rear,s
        HQ->rear->next = s;
        //新的队尾
        HQ->rear = s;

    }
    return HQ;

}
//队列出队，从队头删除一个数据
myqueue *delQueue(myqueue *HQ)
{
    mynode *p;
    int x;
    //队头为空
    if (HQ->first==NULL)
    {
        printf("\n yichu");
    }
    else
    {
        x = HQ->first->data;//获取队头数据
        p = HQ->first;//指向队头地址
        if(HQ->first == HQ->rear)
        {
            //队头和队尾指向同一地址，说明队列中只有一个结点，游标重合
            HQ->first = NULL; HQ->rear = NULL;
            free(p);
        }
        else
        {
            //队头指向下一个结点，删除原队头
            HQ->first = HQ->first->next;
            free(p);
        }
    }
    return HQ;
}
//入栈，先进后出，栈顶压入一个数据
myqueueStack *push1(myqueueStack *HQ,int x)
{
    mynode *s;
    //*p;
    s = (mynode *)malloc(sizeof(mynode));
    s->data = x;
    s->next = NULL;
    if (HQ->zhandi == NULL)
    {
        //栈为空
        HQ->zhandi = NULL; HQ->top = NULL;
    }
    else
    {
        //s,top;由栈底向上增长，添加到栈顶下一个
        HQ->top->next=s;
        HQ->top = s;

    }

    return HQ;
}
//出栈，栈顶弹出一个数据
myqueueStack *pop1(myqueueStack *HQ)
{
    mynode *p;
    int x;
    if (HQ->zhandi == NULL)
    {
        printf("\n yichu");
    }
    else
    {
        x = HQ->zhandi->data;
        p = HQ->zhandi;
        if (HQ->zhandi == HQ->top)
        {
            HQ->zhandi = NULL;
            HQ->top = NULL;
        }
        else
        {
            while (p->next!= HQ->top)
            {
                p = p->next;
            }
            //找到栈顶前一个元素
            HQ->top = p;
            HQ->top->next = NULL;
        }

    }
    return HQ;
}
//入栈
mynode *pushX(mynode *top,int x)
{
    mynode *s;
    s = (mynode *)malloc(sizeof(mynode));
    s->data = x;
    s->next = top;//插入栈顶
    top = s;//修改栈顶指针
    return top;
}

mynode *popX(mynode * top)
{
    mynode *p;
    int x;
    if (top == NULL)
    {
        return NULL;//栈为空 无元素弹出
    }
    else
    {
        p = top;//保存栈顶指针与p中
        x = top->data;//存栈顶元素
        top = top->next;//修改栈顶指针
        free(p);//释放弹出的元素结点空间
        return top;
    }
}

//判断系统大小端模式
EINT32 GetSystemEndianMode()
{
    char x0,x1;
    EUINT16 x=0x1122;
    x0=((char*)&x)[0]; //低地址单元
    x1=((char*)&x)[1]; //高地址单元

    if (0X11 == x0)
    {
        printf("BIG_ENDIAN\n");
        return 0;
    }
    if (0X22 == x0)
    {
        printf("LITTLE_ENDIAN\n");
        return 1;
    }
    return -1;
}

#endif
#define EPS 0.000001
void isZero(double d)
{
    if (d >= -EPS && d <= EPS)
    {
    //d是0处理
    }
}


#if 0
//execute shell command
//执行一个shell命令，输出结果逐行存储在resvec中，并返回行数
int myexec(const char *cmd, vector<string> &resvec)
{
    resvec.clear();
    FILE *pp = popen(cmd, "r"); //建立管道
    if (!pp) {
        return -1;
    }
    char tmp[1024]; //设置一个合适的长度，以存储每一行输出
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        if (tmp[strlen(tmp) - 1] == '\n') {
            tmp[strlen(tmp) - 1] = '\0'; //去除换行符
        }
        resvec.push_back(tmp);
    }
    pclose(pp); //关闭管道
    return resvec.size();
}
#endif

#ifdef _DEBUG
void initMycode_T()
{
     GetSystemEndianMode();
}
#endif


