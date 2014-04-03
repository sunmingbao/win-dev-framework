/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */

#ifndef __EXT_UTILS_TEXTOUT_H_
#define __EXT_UTILS_TEXTOUT_H_

#include <windows.h>
#include <tchar.h> 
#include <windowsx.h>

void fw_text_out_full(HDC hdc, int x, int y, int height
    ,COLORREF bg, COLORREF fg, TCHAR *text, int len);

void fw_text_out_full_trans(HDC hdc, int x, int y, int height
    ,COLORREF fg, TCHAR *text, int len);

int fw_text_get_char_width(int height);

#endif

