#include "exam.h"

#define MAX_HASH_ID   1024
#define MAX_PDT_USER_NUM  100000

LIST g_usr_hashtable[MAX_HASH_ID];
PDT_USER_HASH_TBL_CTRL_t g_tUserHashCtrl;


EINT32 initUserHashMem(void)
{
	PDT_USER_DATA_NODE_t  *pUserDataNode = NULL;

	EUINT32 i = 0;
	EUINT32 uiUserPoolMemSize = MAX_PDT_USER_NUM * sizeof(PDT_USER_HASH_TBL_CTRL_t);


	if (ETTRUE == g_tUserHashCtrl.initFlag)
    {
        printf("PDC ERROR(initUserHashMem): user hash Mem has already init\r\n");
        return ETOK;
    }
    memset(&g_tUserHashCtrl,0,sizeof(g_tUserHashCtrl));


	g_tUserHashCtrl.totalByte = uiUserPoolMemSize;

	printf("g_tUserHashCtrl.totalByte = %d Byte\n",g_tUserHashCtrl.totalByte);

	g_tUserHashCtrl.pMem = ALLOCDMM(g_tUserHashCtrl.totalByte);

    if(NULL == g_tUserHashCtrl.pMem)
    {
        printf("NULL == g_tUserHashCtrl.pMem\n");
		return ETERROR;
    }

    for ( i=0; i < MAX_PDT_USER_NUM; i++)
    {
        pUserDataNode = (PDT_USER_DATA_NODE_t*)(g_tUserHashCtrl.pMem
            + i * sizeof(PDT_USER_DATA_NODE_t));

        memset(pUserDataNode, 0, sizeof(PDT_USER_DATA_NODE_t));

        lstAdd((LIST*)(&g_tUserHashCtrl.freeMemPool), (NODE*)pUserDataNode);
        if(0 == i)
        {
            g_tUserHashCtrl.pMemPoolHead=(void*)pUserDataNode;
        }
    }


    g_tUserHashCtrl.initFlag = ETTRUE;

    return ETOK;
}
void  *GetNodeFromFreeMemPool()
{

    void *pNode = NULL;

    pNode = (void *)lstGet(&g_tUserHashCtrl.freeMemPool);

    if (NULL == pNode)
    {
        //内存池为空
        printf("notice:the table mem pool is empty!!!");
        return NULL;
    }
    return pNode;
}

EINT32 PutFreeNodeToFreeMemPool(void *pNode)
{
    if (NULL == pNode)
    {
        printf("input paramter error.");
        return ETERROR;
    }

    printf("return node(%p)to mem pool.",pNode);

    /* Put free node to free mem pool */
    lstAdd(&g_tUserHashCtrl.freeMemPool, (NODE*)pNode);

    return ETOK;
}


EINT32 InitUserHashTable()
{
    EUINT32 i = 0;

    for(; i < MAX_HASH_ID; i++)
    {
        lstInit(&g_usr_hashtable[i]);
    }

    return ETOK;
}

EINT32 AddNodeToUserHashTable(EUINT32 uiHashID, void *precord)
{
    if (NULL == precord)
    {
        printf("input paramter precord error(%d).",uiHashID);
        return ETERROR;
    }
    if(uiHashID >= MAX_HASH_ID)
	{
	    printf("input paramter type error(%d).",uiHashID);
	    return ETERROR;
	}

    lstAdd(&g_usr_hashtable[uiHashID], (NODE*)precord);

    printf("the table(%d) add  node(%p)",uiHashID,precord);

    return ETOK;
}

EINT32 DelNodeFromUserHashTable(EUINT32 uiHashID, void *precord)
{
    if (NULL == precord)
    {
        printf("input paramter precord error(%d).",uiHashID);
        return ETERROR;
    }
    if(uiHashID >= MAX_HASH_ID)
	{
	    printf("input paramter type error(%d).",uiHashID);
	    return ETERROR;
	}

    lstDelete(&g_usr_hashtable[uiHashID], (NODE*)precord);

    printf("the table(%d) delete node(%p)",uiHashID,precord);


    /* Put free node to free mem pool */
    if( ETOK != PutFreeNodeToFreeMemPool(precord) )
    {
        return ETERROR;
    }
    return ETOK;
}

EUINT32 GetHashIndex(EUINT32 uiAddr)
{
    EUINT32 uiIndex = 0;

    uiIndex = uiAddr & (MAX_HASH_ID - 1);

    return uiIndex;
}

EINT32 SearchPdtUser(void **pprecord, EUINT32 uiSSI)
{
    PDT_USER_DATA_NODE_t *pUserNode = NULL;
    EUINT32 uiHashID = 0;

    void *pNode        = NULL;

    if (NULL == pprecord || 0 == uiSSI)
    {
        printf("table input pprecord or key(%u) error.",uiSSI);
        return ETERROR;
    }

    uiHashID = GetHashIndex(uiSSI);

    pNode = (void *)lstFirst(&g_usr_hashtable[uiHashID]);
    while(pNode)
    {
        pUserNode = (PDT_USER_DATA_NODE_t  *)pNode;

        if(uiSSI == pUserNode->tUserInfo.uiSSI)
        {
            printf("pdt user(ID:%u) was  found!",uiSSI);
            *pprecord = pNode;

            return ETOK;
        }

        pNode = (void *)lstNext((NODE*)pNode);
    }

    printf("pdt user(ID:%u) was not found!",uiSSI);

    return ETERROR;
}


EINT32 AddPdtUser(PDT_USER_INFO_t *ptUserInfo)
{

    EUINT32 uiHashID = 0;
    PDT_USER_DATA_NODE_t *pUserNode = NULL;
    void *pNode = NULL;
    EINT32  iChkTblRet = ETERROR;

    if(NULL == ptUserInfo)
    {
        return ETERROR;
    }


    iChkTblRet = SearchPdtUser(&pNode,ptUserInfo->uiSSI);

    if(ETOK == iChkTblRet)
    {
        //用户存在
        return ETERROR;
    }

    pNode = GetNodeFromFreeMemPool();
    if(NULL == pNode)
    {
        return ETERROR;
    }
    pUserNode = (PDT_USER_DATA_NODE_t*)pNode;

    memcpy(&(pUserNode->tUserInfo),ptUserInfo,sizeof(*ptUserInfo));


    printf("add pdt user info(ssi:%d,bsid:%d,RoamFalg:%d)!",
      pUserNode->tUserInfo.uiSSI,pUserNode->tUserInfo.uiBsID,pUserNode->tUserInfo.uiRoamFalg);


    uiHashID = GetHashIndex(ptUserInfo->uiSSI);

    if(ETOK != AddNodeToUserHashTable(uiHashID,pNode))
    {
        return ETERROR;
    }
    return ETOK;
}

EINT32 DelPdtUser(EUINT32 uiSSI)
{
    PDT_USER_DATA_NODE_t *pUserNode = NULL;
    void *pNode = NULL;
    EINT32  iChkTblRet = ETERROR;
    EUINT32 uiHashID = 0;

    if(0 == uiSSI)
    {
        return ETERROR;
    }

    iChkTblRet = SearchPdtUser(&pNode,uiSSI);

    if(ETOK != iChkTblRet)
    {
        //用户不存在
        printf("pdt user info(ssi:%d) not exist!\n",uiSSI);
        return ETERROR;
    }
    pUserNode =(PDT_USER_DATA_NODE_t *)pNode;

    memset(pUserNode,0,sizeof(*pUserNode));

    uiHashID = GetHashIndex(uiSSI);

    if(ETOK != DelNodeFromUserHashTable(uiHashID, pNode))
    {
        return ETERROR;
    }

    printf("del pdt user info(ssi:%d) suc!\n",uiSSI);

    return ETOK;
}


EINT32 CheckPdtUserIfRoam(EUINT32 uiSSI,EUINT32 *puiRoamFalg)
{
    PDT_USER_DATA_NODE_t *pUserNode = NULL;
    void *pNode = NULL;
    EINT32  iChkTblRet = ETERROR;

    if(0 == uiSSI)
    {
        return ETERROR;
    }

    iChkTblRet = SearchPdtUser(&pNode,uiSSI);

    if(ETOK != iChkTblRet)
    {
        //用户不存在
        printf("pdt user info(ssi:%d)  not exist!\n",uiSSI);
        return ETERROR;
    }

    pUserNode =(PDT_USER_DATA_NODE_t *)pNode;
    if(pUserNode->tUserInfo.uiRoamFalg)
    {
        *puiRoamFalg = 1;
    }
    else
    {
        *puiRoamFalg = 0;
    }
    printf("pdt user info(ssi:%d) was found !\n",uiSSI);
    return ETOK;
}

EINT32 initPdtUserModule(void)
{
    static EUINT32 s_uiInitFlag = 0;

    if(s_uiInitFlag)
    {
        printf("init error\n");
		return ETERROR;
    }
    if( ETOK != initUserHashMem() )
    {
        printf("init user hash Tbl Mem fail\n");
		return ETERROR;
    }

    InitUserHashTable();

    s_uiInitFlag = 1;

    return ETOK;
}

