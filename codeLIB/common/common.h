#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "sys.h"
#include "etUtil.h"

#include "dbpub.h"
#include "oampub.h"
#include "ospub.h"
//#include "etwindows.h"
#include "oambsc.h"
#include "bearBsc.h"
#include "bearpub.h"
#include "ctrlbsc.h"

#define _DEBUG


//#include <stack>

extern char *GetECNPrimCfgEthernet();


#ifdef WINDOWS
#define PPAL_LOGPRINT_ERROR(str)                        printf("[ERROR:PPAL]  %s [%s:%d]\r\n", str, __FILE__, __LINE__)
#define PPAL_LOGPRINT_ERROR_P1(str, P1)                 printf("[ERROR:PPAL]  %s%d  [%s:%d]\r\n", str, P1, __FILE__, __LINE__)
#define PPAL_LOGPRINT_INFO( str)                        printf("[INFO:PPAL]   %s ", str)
#define PPAL_LOGPRINT_MULTINFO(fmt, params)             printf(fmt, params)
#else
#define PPAL_LOGPRINT_ERROR(str)                        //PrintfLog(LOG_ERROR, FID_PPAL, "[ERROR:PPAL]  %s [%s:%d]\r\n", str, __FILE__, __LINE__)
#define PPAL_LOGPRINT_ERROR_P1(str, P1)                 printf("[ERROR:PPAL]  %s%d  [%s:%d]\r\n", str, P1, __FILE__, __LINE__)
#define PPAL_LOGPRINT_INFO( str)                        printf("[INFO:PPAL]   %s ", str)
#define PPAL_LOGPRINT_MULTINFO(fmt, params)             printf(fmt, params)
#endif

#ifdef WINDOWS
#define PPAL_LOG_INFO(fmt)                              printf("              " fmt)
#define PPAL_LOG_PRM1(fmt, P1)                          printf("              " fmt, P1)
#define PPAL_LOG_PRM2(fmt, P1, P2)                      printf("              " fmt, P1, P2)
#define PPAL_LOG_PRM3(fmt, P1, P2, P3)                  printf("              " fmt, P1, P2, P3)
#define PPAL_LOG_PRM4(fmt, P1, P2, P3, P4)              printf("              " fmt, P1, P2, P3, P4)
#define PPAL_LOG_PRM5(fmt, P1, P2, P3, P4, P5)          printf("              " fmt, P1, P2, P3, P4, P5)
#define PPAL_LOG_PRM6(fmt, P1, P2, P3, P4, P5, P6)      printf("              " fmt, P1, P2, P3, P4, P5, P6)
#define PPAL_LOG_PRM7(fmt, P1, P2, P3, P4, P5, P6,P7)   printf("              " fmt, P1, P2, P3, P4, P5, P6,P7)
#define PPAL_LOG_SDU(sdu, fmt)                          //PrintfLogSDU(LOG_INFO, FID_LLCP, sdu, fmt)
#define PPAL_LOG_PKT(data, len, fmt)                    //PrintfLogPkt(LOG_INFO, FID_LLCP, data, len, fmt)
#else
#define PPAL_LOG_INFO(fmt)                              printf("" fmt)
#define PPAL_LOG_PRM1(fmt, P1)                          printf("" fmt, P1)
#define PPAL_LOG_PRM2(fmt, P1, P2)                      printf("" fmt, P1, P2)
#define PPAL_LOG_PRM3(fmt, P1, P2, P3)                  printf("" fmt, P1, P2, P3)
#define PPAL_LOG_PRM4(fmt, P1, P2, P3, P4)              printf("" fmt, P1, P2, P3, P4)
#define PPAL_LOG_PRM5(fmt, P1, P2, P3, P4, P5)          printf("" fmt, P1, P2, P3, P4, P5)
#define PPAL_LOG_PRM6(fmt, P1, P2, P3, P4, P5, P6)      printf("" fmt, P1, P2, P3, P4, P5, P6)
#define PPAL_LOG_PRM7(fmt, P1, P2, P3, P4, P5, P6,P7)   printf("" fmt, P1, P2, P3, P4, P5, P6,P7)
#define PPAL_LOG_SDU(sdu, fmt)                          //PrintfLogSDU(LOG_INFO, FID_PPAL, sdu, fmt)
#define PPAL_LOG_PKT(data, len, fmt)                    //PrintfLogPkt(LOG_INFO, FID_PPAL, data, len, fmt)
#endif

#endif

