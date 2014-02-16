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
#include "defs.h"

int scrn_width;  /* 屏幕宽度 */
int scrn_height; /* 屏幕高度 */

int cxChar; /* SYSTEM_FIXED_FONT width */
int cyChar; /* SYSTEM_FIXED_FONT height */

void init_char_size_info()
{
    HDC hdc = CreateIC (TEXT ("DISPLAY"), NULL, NULL, NULL) ;
    TEXTMETRIC textmetric;

    SelectObject (hdc, GetStockObject(SYSTEM_FIXED_FONT)) ;
    GetTextMetrics(hdc, &textmetric) ;
    DeleteObject (SelectObject (hdc, GetStockObject(SYSTEM_FONT))) ;
    DeleteDC (hdc) ;

    cxChar = textmetric.tmAveCharWidth ;
    cyChar = textmetric.tmHeight + textmetric.tmExternalLeading ;

}

int reg_sys_win_classes()
{
    INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_STANDARD_CLASSES|ICC_BAR_CLASSES|ICC_TAB_CLASSES
        |ICC_TREEVIEW_CLASSES|ICC_LISTVIEW_CLASSES;


    InitCommonControlsEx(&icex);
    InitCommonControls();

}

void env_init()
{
    char exe_file_path[MAX_FILE_PATH_LEN];
    char *pchar;
    init_char_size_info();
    CreateDirectory("C:\\WINDOWS\\temp", NULL);
    GetModuleFileName(NULL,  exe_file_path,  sizeof(exe_file_path));
    pchar=strrchr(exe_file_path, '\\');
    *pchar=0;
    SetCurrentDirectory(exe_file_path);

    scrn_width = GetSystemMetrics(SM_CXSCREEN);
    scrn_height = GetSystemMetrics(SM_CYSCREEN);

    reg_sys_win_classes();
}


