/************************************************************************
Copyright (C), 2009-2010, Eastcom.
File name:   error.c
Author:      network
Date:        2018.07.19
Description: �׳�������Ŀ
Others:
*************************************************************************/
#include "common.h"

void fun1(char *p)
{
   p=(char*)malloc(100);
}
void ttfun1()
{
    char *str=NULL;

    /*
    ���ú�,�����ڲ��β�p�ı���,
    �������ز�����ı�ʵ��str,����str��Ȼ�ǿ�.
    ��Ҫ�ı�str,fun1�����β���Ҫʹ�ö���ָ��.
    */
    fun1(str);
    /* notice:str�ǿ�ָ�� */
    strcpy(str, "hello world1\n");
    printf(str);
}

//char p[]="hello world2\n";

char *fun2()
{
   char p1[]="hello world2\n";
   return p1;
}
void ttfun2()
{
   char *str=NULL;
   /* ���ú�,�������ص���һ����ַ */
   str=fun2();
   printf(str);
}

void initError_T()
{
    //ttfun1();
     ttfun2();
}


