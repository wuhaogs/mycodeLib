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
host: ����
Port:�������˿ں�

Return : ָ��LDAP�ṹ��ָ��
*/

extern void* LdapInit(const char *defhost, int defport );
/*
// Asynchronously authenticates an entry to the directory.
ld : 	ָ��LDAP�ṹ��ָ��
dn: 	DN���硰cn=admin,dc=example,dc=com����
passwd:	������������
return: Message ID of operation or -1
*/

extern int LdapSimpleBind( void *ld, const char *who,
                   const char *passwd );

/*
Synchronously searches the directory.

�첽����LDAP������
������
ld		ldap���
base	Ҫ������DN
scope	���������Χ
		LDAP_SCOPE_BASE(0x00)	������DN���������Ŀ¼�ṹ
		LDAP_SCOPE_ONELEVEL(0x01)	��������Ŀ¼
		LDAP_SCOPE_SUBTREE(0x02)		 ������DN�������������
filter	������
attrs	��������ļ�������
attrsonly�����Ƿ���������Ի�����ͬ����ֵһ�𷵻�
		zero		�������Ժ�ֵ
		����	ֻ����ֵ

����ֵ��
		>0		������ϢID
		-��		ʧ��

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

 *��ȡ֮ǰ�첽�����Ľ����

������
ld:		ָ��LDAP�Ựָ��
msgid����֮ǰ�������ص���ϢID
all��	�������һ��LdapResult�����ж�������¼������
		LDAP_MSG_ONE(0x00)	һ�ε��÷���һ����¼
		LDAP_MSG_ALL(0x01)	�ڷ������м�����¼ǰLdapResult���᷵��
		LDAP_MSG_RECEIVED(0x02)	LdapResult����ʱ(timeout)���յ������м�¼	timeout
		����LdapResult���صȴ�ʱ��
result	����������ص�����
����ֵ��
0x00	��ʱ
-��		ʧ��

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

 ��ȡ��¼�ĸ�����
 ������
 ld:	 LDAP�ṹָ��
 chain	 ���������ָ��

 ����ֵ����
 -1��		 ִ��ʧ��
 >0:		 ��¼�ĸ���

 */

 extern int LdapCountEntries(void *ld, void *chain);

/*

��ȡ��һ����¼��
������
ld:		LDAP�ṹָ��
chain	���������ָ��

����ֵ����
NULL��	û�м�¼��LdapFirstEntryִ��ʧ��
>0			ָ����һ����¼��ָ��

*/
 extern void* LdapFirstEntry( void *ld,
    void *chain );



/*
Returns string values of a specified attribute from an entry.
ld:    	LDAP�Ựָ�� .
entry:	LDAP first entry ָ��
attr	�����ֶ�
return �����Զ�Ӧ��ֵ

  */
 extern char ** LdapGetValues( void *ld,void *entry,
  const char *target );


/*
�ͷ��ַ���������ڴ�

������
vals:		�ַ�������

����ֵ����
*/
extern void LdapValueFree( char **vals );

/*
��ӡldap������Ϣ

������
ld:		LDAP�Ựָ��
s:		Ҫ��ӡ�Ĵ���˵��

����ֵ��
��
*/
extern void LdapError( void *ld, const char *s );

/*
�ͷ���Ϣ���ϵ�������Ϣ��㡣

������
lm:		��Ϣ��ָ��

����ֵ��
>0x60		�ɹ�
0x00		ʲôҲû��
*/
extern int LdapMsgFree( void *lm );

/*
* ldap_memfree() is needed to ensure that memory allocated by the C runtime
* assocated with libldap is freed by the same runtime code.
LDAP���ͷ��ڴ溯��

������
s:		Ҫ�ͷŵ��ڴ��׵�ַ

����ֵ��
��

*/
extern void LdapMemFree( void *s );

/*
�ͷ�LDAP�Ự���ر����ӣ��ͷ�������LDAP�Ự��ص���Դ��

������
ld:		LDAP�Ựָ��

����ֵ��
0x00		ִ�гɹ���
��=��		ִ��ʧ��
*/
extern int LdapUnbind( void *ld );


/*
�ͷ�berElement�ṹ�����

������
ber		berElement�ṹ��ָ�����
freebuf	�ڲ������־λ�������ͷ��ڲ����棻�������ͷ��ڲ����档

����ֵ��
��
*/
extern void BerFree( void *ber, int freebuf );


/*
�ӽ�����з���һ����¼��DN

������
ld:		LDAP�Ự
entry:	��ldap_first_entry ��ldap_next_entry��õ�LDAP��Ϣָ��

����ֵ��
>0		ָ��DN�ַ�����ָ��
NULL	failure

*/
extern char* LdapGetDn( void *ld, void *entry );

/*
����һ����¼�еĵ�һ������

������
ld��	LDAP�Ựָ��
entry:	LDAP��Ϣ��¼
ber:	ָ��berElement��ָ��

����ֵ��
NULL		ʧ�ܻ�û������ֵ
>0			ָ���¼�е�һ�����Ե�ָ��
*/


extern char* LdapFirstAttribute( void *ld, void *entry,void **ber);
/*
��ȡ��һ����¼
������
ld:		LDAP�ṹָ��
entry:	LDAP��Ϣ��

����ֵ����
NULL��	û�м�¼��LdapFirstEntryִ��ʧ��
>0			ָ����һ����¼��ָ��

*/
extern char* LdapNextAttribute (void* ld, void* entry,void* ber);



/*��ȡ��һ����¼
������
ld:		LDAP�ṹָ��
entry:	LDAP��Ϣ��

����ֵ����
NULL��	û�м�¼��LdapFirstEntryִ��ʧ��
>0			ָ����һ����¼��ָ��
*/
extern void *LdapNextEntry (void *ld, void *entry);


/*��ȡldap����������
������
ld:		LDAP�ṹָ��

����ֵ����
<0	ִ��ʧ��
>0	ldap����������
*/

extern int LdapGetErrno(void* ld);

/*
����RS��־λ
*/
extern void setLdapRsFlag();

#ifdef __cplusplus
}
#endif

#endif

