/* 
 * ������Ϊ��ѡ���Դ������
 * �������İ�Ȩ(����Դ�뼰�����Ʒ����汾)��һ�й������С�
 * ����������ʹ�á�������������
 * ��Ҳ�������κ���ʽ���κ�Ŀ��ʹ�ñ�����(����Դ�뼰�����Ʒ����汾)���������κΰ�Ȩ���ơ�
 * =====================
 * ����: ������
 * ����: sunmingbao@126.com
 */

#ifndef __APP_PROPERTY_H_
#define __APP_PROPERTY_H_

#include <tchar.h>

//�û��޸�-begin --->
#define    APP_NAME       "windows���򿪷����"
#define    APP_VERSION    {'0','5','0','0'}

#define    szAuthor    TEXT("������")
#define    szCompany   TEXT("ZTE����")
#define    szEmail     TEXT("sunmingbao@126.com")
#define    szContact   TEXT("QQ:7743896")

#define    DOC_FILE_SUFFIX    "abc"  /* Ӧ�ó����ĵ���׺�� */
//<--- �û��޸�-end



/* ��������ͨ�������޸� */
extern const TCHAR     szAppName[];
extern const char      version[];
#define    DOC_FILE_FILTER    APP_NAME" file (*."DOC_FILE_SUFFIX")\0*."DOC_FILE_SUFFIX"\0\0"

#endif
