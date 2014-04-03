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

void fw_text_out_full(HDC hdc, int x, int y, int height
    ,COLORREF bg, COLORREF fg, TCHAR *text, int len)
{
    HFONT  h_old_font;
    LOGFONT lf ;
    
    memset(&lf, 0, sizeof(lf));
    lf.lfCharSet = 1;

    lf.lfHeight = height;
    lf.lfPitchAndFamily = FIXED_PITCH;
    lf.lfWeight  = FW_BLACK;

    
    h_old_font = SelectObject (hdc, CreateFontIndirect(&lf)) ;

    SetBkMode(hdc, OPAQUE);
    SetBkColor(hdc, bg) ;
    SetTextColor(hdc, fg) ;
    TextOut(hdc, x, y, text, len) ; 

    DeleteObject(SelectObject(hdc, h_old_font)) ;
}

void fw_text_out_full_trans(HDC hdc, int x, int y, int height
    ,COLORREF fg, TCHAR *text, int len)
{
    HFONT  h_old_font;
    LOGFONT lf ;
    
    memset(&lf, 0, sizeof(lf));
    lf.lfCharSet = 1;

    lf.lfHeight = height;
    lf.lfPitchAndFamily = FIXED_PITCH;
    lf.lfWeight  = FW_BLACK;

    
    h_old_font = SelectObject(hdc, CreateFontIndirect(&lf)) ;

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, fg) ;
    TextOut(hdc, x, y, text, len) ; 

    DeleteObject(SelectObject(hdc, h_old_font)) ;
}

int fw_text_get_char_width(int height)
{
    HFONT  h_old_font;
    LOGFONT lf ;
    HDC hdc = CreateIC(TEXT ("DISPLAY"), NULL, NULL, NULL) ;
    TEXTMETRIC textmetric;
    
    memset(&lf, 0, sizeof(lf));
    lf.lfCharSet = 1;

    lf.lfHeight = height;
    lf.lfPitchAndFamily = FIXED_PITCH;
    lf.lfWeight  = FW_BLACK;


    
    h_old_font = SelectObject (hdc, CreateFontIndirect(&lf)) ;
    GetTextMetrics(hdc, &textmetric) ;
    DeleteObject(SelectObject(hdc, h_old_font)) ;
    DeleteDC(hdc) ;

    return textmetric.tmAveCharWidth ;

}


