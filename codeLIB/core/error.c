/************************************************************************
Copyright (C), 2009-2010, Eastcom.
File name:   error.c
Author:      network
Date:        2018.07.19
Description: 易出错编程题目
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
    调用后,函数内部形参p改变了,
    函数返回并不会改变实参str,所以str依然是空.
    若要改变str,fun1函数形参需要使用二级指针.
    */
    fun1(str);
    /* notice:str是空指针 */
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
   /* 调用后,函数返回的是一个地址 */
   str=fun2();
   printf(str);
}

void initError_T()
{
    //ttfun1();
     ttfun2();
}


