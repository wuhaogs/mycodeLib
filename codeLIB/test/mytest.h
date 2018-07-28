#ifndef __TEST_H__
#define __TEST_H__
#include "common.h"

typedef struct bitstruct
{
    int b1 : 5;
    int : 2;
    int b2 : 2;
}BitStruct;
typedef struct Struct
{
    EUCHAR b1;
    EUCHAR b2;
    //EUCHAR b3;
    //EUCHAR b4;
}Struct;

EINT32 PpalTestHashListaddlist(EUINT32 uiTaddr,EUINT32 uiTel);

EINT32 PpalTestHashListSearchStatus(EUINT32 uiTaddr,EUINT32 uiTel);

void TestList(EUINT32 uiTaddr,EUINT32 uiTel);

//Œª”Ú¥Û–°∂À≤‚ ‘
void testBitStruct();
//≤‚ ‘µ•¡¥±Ì
void testlistS();
//≤‚ ‘À´¡¥±Ì
void testlistD();
//≤‚ ‘∂”¡–
void testqueue();
//≤‚ ‘’ª
void teststack();


#endif
