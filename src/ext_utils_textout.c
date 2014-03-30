/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */
 
#include <windows.h>
#include <tchar.h> 
#include <commctrl.h>
#include <windowsx.h>

#include "ext_utils_textout.h"

void text_out_full(HDC hdc, int x, int y, int size
    ,COLORREF bg, COLORREF fg, TCHAR *text, int len)
{
    SetBkColor (hdc, bg) ;
    SetTextColor(hdc, fg) ;
    TextOut(hdc, x, y, text, len) ; 
}

void text_out_test(HDC hdc)
{
    text_out_full(hdc, 200, 200, 30
    ,RGB(0x00,0x00,0x00), RGB(0xFF,0xFF,0xFF), TEXT("hello"), 5);
}

