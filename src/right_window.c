/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */

#ifdef _USE_SPLITTER_FRAME

#include <windows.h>
#include "common.h"
#include "global_symbols.h"
#include "res.h"

TCHAR szRightWinClassName[] = TEXT ("right_win") ;
HWND    hwnd_right;


LRESULT CALLBACK right_WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc ;
    PAINTSTRUCT ps ;
    HWND    hwnd_sub ;
    RECT		rect ;
    int cxClient, cyClient;
    static HMENU	hMenu ;
    POINT point ;
    int ret;
    TCHAR  buf[32];

    static int edit_iItem=-1 ;
    static int edit_iSubItem;

     LVITEM lv_item;
    switch (message)
    {
        case WM_CREATE:
            hwnd_right = hwnd;

            return 0 ;
            
        case WM_PAINT :
        {
            int cxchar = fw_text_get_char_width(100);
            hdc = BeginPaint (hwnd, &ps) ;
            //draw some thing here
            fw_text_out_full_trans(hdc
            , 50, 100, 100, RGB(0xFB, 0xFE, 0x83)
            , TEXT("Hello"), 5);

            fw_text_out_full(hdc
            , 100, 200, 100, RGB(0xff,0xff,0xff), RGB(0x0,0x0,0xff)
            , TEXT("ZTE"), 3);

            fw_text_out_full(hdc
            , 100+3*cxchar, 200, 100, RGB(0xff,0xff,0xff), RGB(0x0,0x0,0x0)
            , TEXT("中兴"), 4);
                        
            EndPaint (hwnd, &ps) ;
            return 0 ;
        }


    }
    
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

int register_right_win()
{
    WNDCLASS    sub_wndclass;
    sub_wndclass.style      = CS_HREDRAW | CS_VREDRAW;
    sub_wndclass.lpfnWndProc= right_WndProc;
    sub_wndclass.cbClsExtra = 0;
    sub_wndclass.cbWndExtra = 0;
    sub_wndclass.hInstance  = g_hInstance;
    sub_wndclass.hIcon      = LoadIcon (g_hInstance, TEXT("my_frame_icon"));
    sub_wndclass.hCursor    = LoadCursor (NULL, IDC_ARROW);
    sub_wndclass.hbrBackground  = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    sub_wndclass.lpszMenuName   = NULL;
    sub_wndclass.lpszClassName  = szRightWinClassName;


    if (!RegisterClass (&sub_wndclass))
     {
        MessageBox (NULL, TEXT ("Program requires Windows NT!"),
          szAppName, MB_ICONERROR) ;
        return FAIL;
     }

    return SUCCESS;

}
#endif

