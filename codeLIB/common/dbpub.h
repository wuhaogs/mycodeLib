#ifndef _DBPUB_H
#define _DBPUB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sys.h"

#ifdef LDAP_SCOPE_BASE
#undef LDAP_SCOPE_BASE

#endif
#ifdef LDAP_SCOPE_ONELEVEL
#undef LDAP_SCOPE_ONELEVEL

#endif
#ifdef LDAP_SCOPE_SUBTREE
#undef LDAP_SCOPE_SUBTREE

#endif

#ifdef LDAP_MSG_ONE
#undef LDAP_MSG_ONE
#endif


#ifdef LDAP_MSG_ALL
#undef LDAP_MSG_ALL
#endif

#ifdef LDAP_MSG_RECEIVED
#undef LDAP_MSG_RECEIVED
#endif


#define LDAP_SCOPE_BASE	    (0x00)
#define LDAP_SCOPE_ONELEVEL (0x01)
#define LDAP_SCOPE_SUBTREE	(0x02)

#define LDAP_MSG_ONE	    (0x00)
#define LDAP_MSG_ALL	    (0x01)
#define LDAP_MSG_RECEIVED	(0x02)




/*Initializes an LDAP session associated with an LDAP server and returns
a pointer to a session
handle.
host:
host: 主机
Port:服务器端口号

Return : 指向LDAP结构的指针
*/

extern void* LdapInit(const char *defhost, int defport );
/*
// Asynchronously authenticates an entry to the directory.
ld : 	指向LDAP结构的指针
dn: 	DN（如“cn=admin,dc=example,dc=com”）
passwd:	服务器端密码
return: Message ID of operation or -1
*/

extern int LdapSimpleBind( void *ld, const char *who,
                   const char *passwd );

/*
Synchronously searches the directory.

异步检索LDAP服务器
参数：
ld		ldap句柄
base	要检索的DN
scope	定义检索范围
		LDAP_SCOPE_BASE(0x00)	检索由DN定义的整个目录结构
		LDAP_SCOPE_ONELEVEL(0x01)	检索本级目录
		LDAP_SCOPE_SUBTREE(0x02)		 检索由DN定义的整个子树
filter	过滤器
attrs	定义检索哪几个属性
attrsonly定义是否仅返回属性还是连同属性值一起返回
		zero		返回属性和值
		非零	只返回值

返回值：
		>0		操作消息ID
		-１		失败

 * Example:
 *    char    *attrs[] = { "mail", "title", 0 };
 *    msgid = ldap_search( ld, "c=us@o=UM", LDAP_SCOPE_SUBTREE, "cn~=bob",
 *        attrs, attrsonly );
 */

 extern int LdapSearch(
           void     *ld,
           const char     *base,
           int     scope,
           const char     *filter,
           char     **attrs,
     int     attrsonly);


 /*
 * ldap_result - wait for an ldap result response to a message from the
 * ldap server.  If msgid is -1, any message will be accepted, otherwise
 * ldap_result will wait for a response with msgid.  If all is 0 the
 * first message with id msgid will be accepted, otherwise, ldap_result
 * will wait for all responses with id msgid and then return a pointer to
 * the entire list of messages.  This is only useful for search responses,
 * which can be of two message types (zero or more entries, followed by an
 * ldap result).  The type of the first message received is returned.
 * When waiting, any messages that have been abandoned are discarded.

 *获取之前异步操作的结果。

参数：
ld:		指向LDAP会话指针
msgid：由之前操作返回的消息ID
all：	定义调用一次LdapResult函数有多少条记录被返回
		LDAP_MSG_ONE(0x00)	一次调用返回一条记录
		LDAP_MSG_ALL(0x01)	在返回所有检索记录前LdapResult不会返回
		LDAP_MSG_RECEIVED(0x02)	LdapResult返回时(timeout)所收到的所有记录	timeout
		设置LdapResult返回等待时间
result	检索结果返回到这里
返回值：
0x00	超时
-１		失败

 * Example:
 *    ldap_result( s, msgid, all, timeout, result )
 */
 extern int LdapResult(
           void         *ld,
           int         msgid,
           int         all,
           struct timeval    *timeout,
           void        **result
           );

 /*

 获取记录的个数。
 参数：
 ld:	 LDAP结构指针
 chain	 检索结果链指针

 返回值　：
 -1：		 执行失败
 >0:		 记录的个数

 */

 extern int LdapCountEntries(void *ld, void *chain);

/*

获取第一个记录。
参数：
ld:		LDAP结构指针
chain	检索结果链指针

返回值　：
NULL：	没有记录或LdapFirstEntry执行失败
>0			指向下一条记录的指针

*/
 extern void* LdapFirstEntry( void *ld,
    void *chain );



/*
Returns string values of a specified attribute from an entry.
ld:    	LDAP会话指针 .
entry:	LDAP first entry 指针
attr	属性字段
return 与属性对应的值

  */
 extern char ** LdapGetValues( void *ld,void *entry,
  const char *target );


/*
释放字符串数组的内存

参数：
vals:		字符串数组

返回值：无
*/
extern void LdapValueFree( char **vals );

/*
打印ldap错误信息

参数：
ld:		LDAP会话指针
s:		要打印的错误说明

返回值：
无
*/
extern void LdapError( void *ld, const char *s );

/*
释放消息链上的所有消息结点。

参数：
lm:		消息链指针

返回值：
>0x60		成功
0x00		什么也没做
*/
extern int LdapMsgFree( void *lm );

/*
* ldap_memfree() is needed to ensure that memory allocated by the C runtime
* assocated with libldap is freed by the same runtime code.
LDAP的释放内存函数

参数：
s:		要释放的内存首地址

返回值：
无

*/
extern void LdapMemFree( void *s );

/*
释放LDAP会话，关闭连接，释放所有与LDAP会话相关的资源。

参数：
ld:		LDAP会话指针

返回值：
0x00		执行成功；
！=０		执行失败
*/
extern int LdapUnbind( void *ld );


/*
释放berElement结构体变量

参数：
ber		berElement结构体指针变量
freebuf	内部缓存标志位：１，释放内部缓存；０，不释放内部缓存。

返回值：
无
*/
extern void BerFree( void *ber, int freebuf );


/*
从结果链中返回一条记录的DN

参数：
ld:		LDAP会话
entry:	从ldap_first_entry 或ldap_next_entry获得的LDAP消息指针

返回值：
>0		指向DN字符串的指针
NULL	failure

*/
extern char* LdapGetDn( void *ld, void *entry );

/*
返回一条记录中的第一个属性

参数：
ld：	LDAP会话指针
entry:	LDAP消息记录
ber:	指向berElement的指针

返回值：
NULL		失败或没有属性值
>0			指向记录中第一条属性的指针
*/


extern char* LdapFirstAttribute( void *ld, void *entry,void **ber);
/*
获取下一条记录
参数：
ld:		LDAP结构指针
entry:	LDAP消息链

返回值　：
NULL：	没有记录或LdapFirstEntry执行失败
>0			指向下一条记录的指针

*/
extern char* LdapNextAttribute (void* ld, void* entry,void* ber);



/*获取下一条记录
参数：
ld:		LDAP结构指针
entry:	LDAP消息链

返回值　：
NULL：	没有记录或LdapFirstEntry执行失败
>0			指向下一条记录的指针
*/
extern void *LdapNextEntry (void *ld, void *entry);


/*获取ldap操作错误码
参数：
ld:		LDAP结构指针

返回值　：
<0	执行失败
>0	ldap操作错误码
*/

extern int LdapGetErrno(void* ld);

/*
设置RS标志位
*/
extern void setLdapRsFlag();

#ifdef __cplusplus
}
#endif

#endif

