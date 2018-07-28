#include "common.h"
#include "mycode.h"


LIST g_pktCalledStatusPool;
PPAL_PKT_CALLED_STATUS_t		*g_pktCalledStuPoolHead	= NULL;
LIST g_pktCalledEvtTagHashTable[PPAL_PKT_HASH_TABLE_MAX];
LIST g_pktCalledAddrHashTable [PPAL_PKT_HASH_TABLE_MAX];

//16�����ַ�ת��Ϊ��ֵ
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
* Description : �ַ�ת��Ϊ��ͨ�ֽ�����
* Input         :str1
* Output        :str2
* Return       : ��
*
* Others       :2015.07.15,str2��������鳤��>str1/2
************************************************************************/
EINT32 ArrayString2Byte(EUCHAR *str2,EUCHAR *str1)
{
    //���ַ�������ת�����ֽ�����
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

//��ʼ�����鱻�е�ַ��ϣ��
EINT32 InitPktCalledAddrHashTable()
{
    EUINT32 i = 0;

    for (i = 0; i < PPAL_PKT_HASH_TABLE_MAX; i++)
    {
        /* ��ʼ����ϣ�� */
        lstInit(&g_pktCalledAddrHashTable[i]);
    }

    return ETOK;
}

//��ʼ�����鱻�б�ǩ��ϣ��
EINT32 InitPktCalledEvtTagHashTable()
{
    EUINT32 i = 0;

    for (i = 0; i < PPAL_PKT_HASH_TABLE_MAX; i++)
    {
        /* ��ʼ����ϣ�� */
        lstInit(&g_pktCalledEvtTagHashTable[i]);
    }

    return ETOK;
}
//��ʼ�����鱻�л����
EINT32 InitPktCalledStatusPool()
{
    EUINT32 i = 0;
    PPAL_PKT_CALLED_STATUS_t *pCalledSta    = NULL;
    PPAL_PKT_CALLED_STATUS_t *pAllCalledSta = NULL;

    /* ��ʼ��g_pktCallingStatusPool���� */
    lstInit(&g_pktCalledStatusPool);

    pAllCalledSta = (PPAL_PKT_CALLED_STATUS_t *)malloc(sizeof(PPAL_PKT_CALLED_STATUS_t) * PPAL_PKT_STATUS_POOL_LEN);
    if (NULL == pAllCalledSta)
    {
        //PPAL_LOGPRINT_ERROR("Memory allocation pAllPktCalledSta has been failed");
        return ETERROR;
    }

    pCalledSta = pAllCalledSta;

    /* ����ͷ�ڵ��ַ */
    g_pktCalledStuPoolHead = pAllCalledSta;

    for (i = 0; i < PPAL_PKT_STATUS_POOL_LEN; i++)
    {
        /* ��ʼ��������ڵ� */
        memset(pCalledSta, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

        /* ���뵽����������β  */
        lstAdd(&g_pktCalledStatusPool, (NODE *)pCalledSta);

        pCalledSta++;
    }

    return ETOK;
}

//�ָ����鱻�л����
EINT32	RestorePktCalledStaPool()
{
    EUINT32 i = 0;
    PPAL_PKT_CALLED_STATUS_t *pCalledSta    = NULL;

    PPAL_LOGPRINT_ERROR("Lucky Boy! Init Pkt Called pool!\n");

    InitPktCalledAddrHashTable();
    InitPktCalledEvtTagHashTable();

    /* ��ʼ��g_pktStatusPool���� */
    lstInit(&g_pktCalledStatusPool);

    pCalledSta = g_pktCalledStuPoolHead;
    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Lucky Boy! pkt called pool head is null!\n");
        return ETERROR;
    }

    for (i = 0; i < PPAL_PKT_STATUS_POOL_LEN; i++)
    {
        /* ��ʼ��������ڵ� */
        memset(pCalledSta, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

        /* ���뵽����������β  */
        lstAdd(&g_pktCalledStatusPool, (NODE *)pCalledSta);

        pCalledSta++;
    }

    return ETOK;
}

//���ݵ�ַ���ҷ��鱻�е�ַ״̬��
EINT32 SearchPktCalledSta(PPAL_PKT_CALLED_STATUS_t **ppPktSta, EUINT32 uiCalledAddr)
{
    EUINT32 uiIndex = 0;
    PPAL_PKT_CALLED_STATUS_t *pCalledStaTmp = NULL;
    PPAL_PKT_CALLED_STATUS_t *pStaTmp		= NULL;

    /* ��ȡindexֵ */
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
            PPAL_LOG_PRM1("0 ��ַ pPktCalledSta Index = %d\n", uiIndex);

            pStaTmp = pCalledStaTmp;
            pCalledStaTmp = (PPAL_PKT_CALLED_STATUS_t*)lstNext((NODE*)pCalledStaTmp);

            lstDelete(&g_pktCalledAddrHashTable[uiIndex], (NODE *)pStaTmp);
            /* ��״̬����Ϊ���� */
            memset(pStaTmp, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

            /* ������״̬���Ż��ڴ�� */
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

//���ݱ�ǩ���ҷ��鱻�б�ǩ״̬������ӽڵ��ַ��ʱ���е�ַƫ�ƣ��ʲ��ҵ�ʱ����Ҫ��ַƫ��
EINT32 SearchPktCalledStaFromEvtTag(PPAL_PKT_CALLED_STATUS_t **ppPktSta,EUINT32 uiEventTag)
{
    EUINT32 uiIndex = 0;
    NODE    *pNodeTmp = NULL;
    PPAL_PKT_CALLED_STATUS_t *pPktStaTmp = NULL;

    PPAL_LOGPRINT_INFO("SearchPktCalledStaFromEvtTag\n");

    /* ��ȡindexֵ */
    uiIndex  = GetPPALPktEvtTagHashIndex(uiEventTag);
    pNodeTmp = lstFirst(&g_pktCalledEvtTagHashTable[uiIndex]);

    PPAL_LOG_PRM2("find pPktCalledSta  EventTag Index    = %d,sel = %d\n",uiIndex,uiEventTag);

    while(NULL != pNodeTmp)
    {
        pPktStaTmp = (PPAL_PKT_CALLED_STATUS_t *)(pNodeTmp-1); /*��ַƫ��*/

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

//�ӷ��鱻�л�����л�ȡһ���ַ
PPAL_PKT_CALLED_STATUS_t  *GetPktCalledStaFromPool()
{
    PPAL_PKT_CALLED_STATUS_t *pCalledSta = NULL;

    /* �� g_pktCalledStatusPool �ڴ���л�ȡ��һ���ڵ㲢���ڴ����ɾ�� */
    pCalledSta = (PPAL_PKT_CALLED_STATUS_t*)lstGet(&g_pktCalledStatusPool);

    /* g_pktCalledStatusPool �ڴ��Ϊ�գ�δ��ȡ���ڵ� */
    if (NULL == pCalledSta)
    {
        if( ETOK == RestorePktCalledStaPool() )
            pCalledSta = (PPAL_PKT_CALLED_STATUS_t*)lstGet(&g_pktCalledStatusPool);

        return pCalledSta;
    }

    /* ��ʼ���ڴ�ռ� */
    memset(pCalledSta, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

    return pCalledSta;
}

//�ӷ��鱻�е�ַ��ϣ����ɾ��һ���ڵ��ַ���򻺴���з���һ���ڵ�
EINT32 DeletePktStaFromCalledAddrHash(PPAL_PKT_CALLED_STATUS_t  *pCalledSta)
{
    EUINT32 uiIndex = 0;

    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Function parameter pPktDataCalledSta is NULL");
        return ETERROR;
    }

    uiIndex = GetPPALPktCallAddrHashIndex(pCalledSta->uiCalledAddr);

    PPAL_LOG_PRM1("ɾ�� pPktDataCalledSta  Index    = %d\n", uiIndex);

    lstDelete(&g_pktCalledAddrHashTable[uiIndex], (NODE*)pCalledSta);

    /* ��״̬����Ϊ���� */
    memset(pCalledSta, 0, sizeof(PPAL_PKT_CALLED_STATUS_t));

    /* ������״̬���Ż��ڴ�� */
    if(ETERROR == PutPktCalledStaToPool(pCalledSta))
    {
        PPAL_LOGPRINT_ERROR("Function PutPktCalledStaToPool has been failed");
        return ETERROR;
    }

    return ETOK;
}

//�ӷ��鱻�б�ǩ��ϣ����ɾ��һ���ڵ��ַ���򻺴���з���һ���ڵ�
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

    PPAL_LOG_PRM1("ɾ�� pPktCalledSta  eventTag Index    = %d\n", uiIndex);

    pNodeTmp = &(pPktSta->pPktEvtTagSta);

    if (NULL != pNodeTmp)
    {
        lstDelete(&g_pktCalledEvtTagHashTable[uiIndex], pNodeTmp);
        pNodeTmp = NULL;
    }

    return ETOK;
}

//���һ���ڵ��ַ�����鱻�е�ַ��ϣ��
EINT32 AddPktStaToCalledAddrHash(PPAL_PKT_CALLED_STATUS_t *pCalledSta)
{
    EUINT32 uiIndex = 0;

    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Function parameter pPktCalledSta is NULL");
        return ETERROR;
    }

    /* ��ȡindexֵ */
    uiIndex = GetPPALPktCallAddrHashIndex(pCalledSta->uiCalledAddr);

    PPAL_LOG_PRM2("add pPktCalledSta  Index = %d,called addr=%d.\n", uiIndex,pCalledSta->uiCalledAddr);

    /* ��ӵ�g_pktCalledAddrHashTable */
    lstAdd(&g_pktCalledAddrHashTable[uiIndex], (NODE*)pCalledSta);

    PPAL_LOG_PRM1("addnode addr:%p\n",(NODE*)pCalledSta);

    return ETOK;
}

//���һ���ڵ��ַ�����鱻�б�ǩ��ϣ��
EINT32 AddPktEvtTagToCalledAddrHash(PPAL_PKT_CALLED_STATUS_t *pCalledSta)
{
    EUINT32 uiIndex = 0;
    NODE   *pNodeTmp = 0;

    if (NULL == pCalledSta)
    {
        PPAL_LOGPRINT_ERROR("Function parameter pPktCalledSta is NULL");
        return ETERROR;
    }

    /* ��ȡindexֵ */
    uiIndex = GetPPALPktEvtTagHashIndex(pCalledSta->uiTel);

    PPAL_LOG_PRM2("add pPktCalledSta  EventTag Index    = %d,Tel = %d\n", uiIndex, pCalledSta->uiTel);

    pNodeTmp = &(pCalledSta->pPktEvtTagSta);  /*��ַƫ��*/

    PPAL_LOG_PRM1("addnode addr:%p\n",pNodeTmp);

    /* ��ӵ�g_pktCalledEvtTagHashTable */
    lstAdd(&g_pktCalledEvtTagHashTable[uiIndex], pNodeTmp);

    return ETOK;
}

//���ݵ�ַ��ȡ������ֵ
EUINT32 GetPPALPktCallAddrHashIndex(EUINT32 uiAddr)
{
    EUINT32 uiIndex = 0;

    uiIndex = uiAddr & (PPAL_PKT_HASH_TABLE_MAX - 1);

    return uiIndex;
}

//���ݱ�ǩ��ȡ������ֵ
EUINT32 GetPPALPktEvtTagHashIndex(EUINT32 uiEventTag)
{
    EUINT32 uiIndex = 0;

    uiIndex = uiEventTag & (PPAL_PKT_HASH_TABLE_MAX - 1);

    return uiIndex;
}

//����鱻�л�����з���һ���ڵ�
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
//��ʼ�����鱻��ҵ��
void InitTestList()
{
    InitPktCalledAddrHashTable();
    InitPktCalledEvtTagHashTable();
    InitPktCalledStatusPool();
}
//������Ľ���
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


//������ⳤ
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
//�������ӡ
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
//������ɾ���ڵ�
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
    //����ѭ����ʱ��P1ָ��Ŀ���㣬����Ҫɾ���Ľ��,P2ָ��Ŀ�����ǰһ�����
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
//��������ӽڵ�
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
        //����P1�Ľ�㵥������P2
        p2 = p1; p1 = p1->next;
    }
    if(p0->data <= p1->data)
    {
        if(head == p1)
        {
            //����ͷ�ڵ�֮ǰ
            p0->next = p1; head = p0;
        }
        else
        {
            //�����м���
            p2->next = p0; p0->next = p1;
        }
    }
    else
    {
        //����β���
        p1->next = p0; p0->next = NULL;
    }
    return head;
}
//��������ӵ����β�������¼���Ľ�㣬���µĽ��β
mynode *insertTailS(mynode *tail, int num)
{
    //pn���¼���Ľ��
    mynode *pn, *p;

    p = tail;
    pn = (mynode *)malloc(sizeof(mynode));
    pn->data = num;

    if (p==NULL)
    {
        pn->next = NULL;
        return pn;
    }
    //����β���
    p->next = pn; pn->next = NULL;

    return pn;
}
//��ȡ�������β���
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
    //����ѭ�������ҵ�β���
    return p;
}
//��������������ͷ�ڵ�
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
            //p������һ��������һ����㣬ֵΪx�����ش��½��
            tail = insertTailS(p, x);
            if(tail!= NULL)
            {
                //���ʼP���Ϊ�գ��¼���Ľ�㼴��ͷ���
                if (p == NULL)
                {
                    head = tail;
                }
                //pָ��β��㣬��ʼ��һ������
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
//�����������,����ͷ���
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
//����������ã�����ͷ���
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
        //head ÿ���ƶ�����λ�ã�tempÿ���ƶ�һ��λ�ã���head�������һ������ʱ��temp�����м��㡣
        head = head->next->next;
        temp = temp->next;
        mid = temp;
    }
}
//˫�������ӣ���ӵ�β��,�����¼���Ľ��
mydnode *insertTailD(mydnode *tail,int num)
{
    //pn���¼���Ľ��
    mydnode *pn, *p;
    //˳��P��pn���£�
    p = tail;

    pn = (mydnode *)malloc(sizeof(mydnode));
    pn->data = num;

    if (p == NULL)
    {
        pn->next = NULL;
        pn->pre = NULL;
        return pn;
    }
    //����β���
    p->next = pn; pn->pre = p; pn->next = NULL;

    return pn;

}
//��ȡ˫�����β���
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
    //����ѭ�������ҵ�β���
    return p;

}
//˫�����ɾ��������ͷ���
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
    //����ѭ����ʱ��P1ָ��Ŀ����
    if (num == p1->data)
    {
        //printf("head:%d,p1:%d\n",head->data,p1->data);
        if (p1 == head)
        {
            printf("del head\n");
            //ɾ��ͷ���
            head = head->next; head->pre = NULL; free(p1);
        }
        else if (p1->next==NULL)
        {

            printf("del tail\n");
            //ɾ��β���,��ΪĿ�����ǰһ������Һ�̽��
            p1->pre->next = NULL;  free(p1);

        }
        else
        {
            printf("del middle\n");
            //ɾ���м���p1��p1->pre,p1,p1->next

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
//����˫��������ͷ�ڵ�
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
            //p������һ��������һ����㣬ֵΪx�����ش��½��
            tail = insertTailD(p, x);
            if (tail != NULL)
            {
                ////���ʼP���Ϊ�գ��¼���Ľ�㼴��ͷ���
                if (p == NULL)
                {
                    head = tail;
                }
                //pָ��β��㣬��ʼ��һ������
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
//˫����ⳤ
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
//˫�����ӡ
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
//�������,�Ƚ��ȳ������β���һ������
myqueue *insertQueue(myqueue *HQ,int x)
{
    mynode *s;
    s = (mynode *)malloc(sizeof(mynode));
    s->data = x;
    s->next = NULL;

    if (HQ->rear== NULL)
    {
        //����Ϊ�գ���ͷ ��β ��ָ���½��
        HQ->first = s;     HQ->rear = s;
    }
    else
    {
        //���в�Ϊ�գ������β��HQ->rear,s
        HQ->rear->next = s;
        //�µĶ�β
        HQ->rear = s;

    }
    return HQ;

}
//���г��ӣ��Ӷ�ͷɾ��һ������
myqueue *delQueue(myqueue *HQ)
{
    mynode *p;
    int x;
    //��ͷΪ��
    if (HQ->first==NULL)
    {
        printf("\n yichu");
    }
    else
    {
        x = HQ->first->data;//��ȡ��ͷ����
        p = HQ->first;//ָ���ͷ��ַ
        if(HQ->first == HQ->rear)
        {
            //��ͷ�Ͷ�βָ��ͬһ��ַ��˵��������ֻ��һ����㣬�α��غ�
            HQ->first = NULL; HQ->rear = NULL;
            free(p);
        }
        else
        {
            //��ͷָ����һ����㣬ɾ��ԭ��ͷ
            HQ->first = HQ->first->next;
            free(p);
        }
    }
    return HQ;
}
//��ջ���Ƚ������ջ��ѹ��һ������
myqueueStack *push1(myqueueStack *HQ,int x)
{
    mynode *s;
    //*p;
    s = (mynode *)malloc(sizeof(mynode));
    s->data = x;
    s->next = NULL;
    if (HQ->zhandi == NULL)
    {
        //ջΪ��
        HQ->zhandi = NULL; HQ->top = NULL;
    }
    else
    {
        //s,top;��ջ��������������ӵ�ջ����һ��
        HQ->top->next=s;
        HQ->top = s;

    }

    return HQ;
}
//��ջ��ջ������һ������
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
            //�ҵ�ջ��ǰһ��Ԫ��
            HQ->top = p;
            HQ->top->next = NULL;
        }

    }
    return HQ;
}
//��ջ
mynode *pushX(mynode *top,int x)
{
    mynode *s;
    s = (mynode *)malloc(sizeof(mynode));
    s->data = x;
    s->next = top;//����ջ��
    top = s;//�޸�ջ��ָ��
    return top;
}

mynode *popX(mynode * top)
{
    mynode *p;
    int x;
    if (top == NULL)
    {
        return NULL;//ջΪ�� ��Ԫ�ص���
    }
    else
    {
        p = top;//����ջ��ָ����p��
        x = top->data;//��ջ��Ԫ��
        top = top->next;//�޸�ջ��ָ��
        free(p);//�ͷŵ�����Ԫ�ؽ��ռ�
        return top;
    }
}

//�ж�ϵͳ��С��ģʽ
EINT32 GetSystemEndianMode()
{
    char x0,x1;
    EUINT16 x=0x1122;
    x0=((char*)&x)[0]; //�͵�ַ��Ԫ
    x1=((char*)&x)[1]; //�ߵ�ַ��Ԫ

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
    //d��0����
    }
}


#if 0
//execute shell command
//ִ��һ��shell������������д洢��resvec�У�����������
int myexec(const char *cmd, vector<string> &resvec)
{
    resvec.clear();
    FILE *pp = popen(cmd, "r"); //�����ܵ�
    if (!pp) {
        return -1;
    }
    char tmp[1024]; //����һ�����ʵĳ��ȣ��Դ洢ÿһ�����
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        if (tmp[strlen(tmp) - 1] == '\n') {
            tmp[strlen(tmp) - 1] = '\0'; //ȥ�����з�
        }
        resvec.push_back(tmp);
    }
    pclose(pp); //�رչܵ�
    return resvec.size();
}
#endif

#ifdef _DEBUG
void initMycode_T()
{
     GetSystemEndianMode();
}
#endif


