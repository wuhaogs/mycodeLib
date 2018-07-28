#ifndef __EXAM_H__
#define __EXAM_H__
#include "common.h"

#define MAX_ALLIAS_NAME_LEN  10

typedef struct
{
    EUINT32 uiSSI;
    EUINT8  strAllias[MAX_ALLIAS_NAME_LEN];
    EUINT32 uiNowGrp;
    EUINT32 uiBsID;
    EUINT32 uiRoamFalg;
}PDT_USER_INFO_t;

typedef struct
{
    NODE pNode;
    PDT_USER_INFO_t tUserInfo;
    #if 0
    EUINT32 uiSSI;
    EUINT8  strAllias[MAX_ALLIAS_NAME_LEN];
    EUINT32 uiNowGrp;
    EUINT32 uiBsID;
    EUINT32 uiRoamFalg;
    #endif
}PDT_USER_DATA_NODE_t;



typedef struct
{
    EBOOL  initFlag;
    EUINT32 totalByte;
    ECHAR   *pMem;
	ETSEM_ID mutexSem;
	LIST    freeMemPool;
	void   *pMemPoolHead;

}PDT_USER_HASH_TBL_CTRL_t;

#endif
