/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */

#ifndef __COMMON_H_
#define __COMMON_H_

#include <windows.h>
#include <tchar.h> 
#include <commctrl.h>
#include <windowsx.h>
#include <stdint.h>
#include <stdio.h>

#include "defs.h"
#include "app_property.h"

#define    ARRAY_SIZE(array_name)    (sizeof(array_name)/sizeof(array_name[0]))

void add_tip(HWND htip_control, HWND hwnd, TCHAR *tips);

static inline HANDLE launch_thread(LPTHREAD_START_ROUTINE ThreadFunc, LPVOID lpParameter)
{
    HANDLE hThrd;
    DWORD threadId;
    
    hThrd = CreateThread(NULL,
        0,
        ThreadFunc,
        lpParameter,
        0,
        &threadId );
    return hThrd;

}

#endif

