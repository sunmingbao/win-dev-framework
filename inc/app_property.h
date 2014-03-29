/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */

#ifndef __APP_PROPERTY_H_
#define __APP_PROPERTY_H_

#include <tchar.h>

//用户修改-begin --->
#define    APP_NAME       "windows程序开发框架"
#define    APP_VERSION    {'1','0','0','0'}

#define    szAuthor    TEXT("孙明保")
#define    szCompany   TEXT("ZTE中兴")
#define    szEmail     TEXT("sunmingbao@126.com")
#define    szContact   TEXT("QQ:7743896")

#define    DOC_FILE_SUFFIX    "abc"  /* 应用程序文档后缀名 */
//<--- 用户修改-end



/* 以下内容通常无须修改 */
extern const TCHAR     szAppName[];
extern const char      version[];
#define    DOC_FILE_FILTER    APP_NAME" file (*."DOC_FILE_SUFFIX")\0*."DOC_FILE_SUFFIX"\0\0"

#endif

