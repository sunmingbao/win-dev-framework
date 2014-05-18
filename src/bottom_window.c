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
#include <time.h>

#include "common.h"
#include "global_symbols.h"
#include "app_resource.h"
#include "res.h"

TCHAR szBottomWinClassName[] = TEXT ("bottom_win") ;
HWND    hwnd_bottom;

HWND  hwnd_button_bottom_close;
HWND    hwnd_b2_tab1;

LRESULT CALLBACK bottom_WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc ;
    PAINTSTRUCT ps ;
    HWND    hwnd_sub ;
    RECT		rect ;
    int cxClient, cyClient;
    int tab_height;
    
static HMENU	hMenu ;
    POINT point ;
    
    switch (message)
    {
        case WM_CREATE:
            hwnd_bottom = hwnd;
            hwnd_button_bottom_close =	CreateWindow ( TEXT("button"),TEXT("X"),
   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    20, 20, 30, 30,
    hwnd, (HMENU)ID_BUTTON_BOTTOM_CLOSE,
               g_hInstance, NULL) ;

            hwnd_b2_tab1=CreateWindow (TEXT("edit"), TEXT (""),
                WS_CHILD | WS_BORDER | WS_VISIBLE | WS_VSCROLL | ES_READONLY|ES_MULTILINE|ES_AUTOVSCROLL|ES_WANTRETURN,
                10, 10,
                50, 50,
                hwnd_bottom, NULL, g_hInstance, NULL) ;
            SendMessage(hwnd_b2_tab1, WM_SETFONT, (WPARAM)h_font_32_px, 0);
            return 0 ;

        case WM_SIZE:

      		cxClient = LOWORD (lParam) ;
      		cyClient = HIWORD (lParam) ;


            MoveWindow	(hwnd_button_bottom_close, 	cxClient-25, 0,
                25, 25, TRUE) ;


            MoveWindow(hwnd_b2_tab1, 	0, 0,
                cxClient-25, cyClient, TRUE) ;

            return 0 ;

            
        case 	WM_COMMAND:
            switch (LOWORD(wParam))
            {
                  
                case    ID_BUTTON_BOTTOM_CLOSE:
                    SetFocus(hwnd_right);
       				SendMessage(hwnd_frame, WM_COMMAND, MAKEWPARAM(IDM_APP_BOTTOM_WIN, 0),0);
       				return 0 ;
             }
            break;


    }
    
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

int register_bottom_win()
{
    WNDCLASS    sub_wndclass;
    sub_wndclass.style      = CS_HREDRAW | CS_VREDRAW;
    sub_wndclass.lpfnWndProc= bottom_WndProc;
    sub_wndclass.cbClsExtra = 0;
    sub_wndclass.cbWndExtra = 0;
    sub_wndclass.hInstance  = g_hInstance;
    sub_wndclass.hIcon      = LoadIcon (g_hInstance, TEXT("my_frame_icon"));
    sub_wndclass.hCursor    = LoadCursor (NULL, IDC_ARROW);
    sub_wndclass.hbrBackground  = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_ACTIVECAPTION));
    sub_wndclass.lpszMenuName   = NULL;
    sub_wndclass.lpszClassName  = szBottomWinClassName;


    if (!RegisterClass (&sub_wndclass))
     {
        MessageBox (NULL, TEXT ("Program requires Windows NT!"),
          szAppName, MB_ICONERROR) ;
        return FAIL;
     }

    return SUCCESS;

}


void edit_append_text(HWND hwnd, TCHAR   *szBuffer)
{
    int ndx = GetWindowTextLength (hwnd);
    SendMessage (hwnd, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
    SendMessage (hwnd, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) szBuffer));

}

void WriteInfo(TCHAR * szFormat, ...)
{
	TCHAR   szBuffer [1024] ;
	va_list pArgList ;
    int len1, len2;
    time_t log_time = time(NULL);

    len1 = strftime(szBuffer,  sizeof(szBuffer), "[%Y%m%d %H:%M:%S] ", localtime(&log_time));

	va_start (pArgList, szFormat) ;

	// The last argument to wvsprintf points to the arguments

	len2=_vsntprintf (	szBuffer+len1, sizeof (szBuffer) / sizeof (TCHAR), 
			szFormat, pArgList) ;

	// The va_end macro just zeroes out pArgList for no good reason
	va_end (pArgList) ;
    szBuffer[len1 + len2] = '\r';
    szBuffer[len1 + len2 + 1] = '\n';
    szBuffer[len1 + len2 + 2] = '\0';
    
    edit_append_text(hwnd_b2_tab1, szBuffer);

}

void PrintText(TCHAR * szFormat, ...)
{
	TCHAR   szBuffer [1024] ;
	va_list pArgList ;
    int len;

	va_start (pArgList, szFormat) ;

	// The last argument to wvsprintf points to the arguments

	len=_vsntprintf (	szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
			szFormat, pArgList) ;

	// The va_end macro just zeroes out pArgList for no good reason
	va_end (pArgList) ;
    //szBuffer[len]='\r';
    //szBuffer[len+1]='\n';
    //szBuffer[len+2]=0;
    
    edit_append_text(hwnd_b2_tab1, szBuffer);

}

void print_mem(void *start_addr, uint32_t length)
{
    char str_addr[32];
    char str_data[64];
    char str_readable[32];
    unsigned char *cur_pos = start_addr;
    int i;

    while (length >= 16)
    {
        sprintf(str_addr, "%-16lx", (unsigned long)(void *)cur_pos);
        for (i = 0; i < 16; i++)
        {
            sprintf(str_data + i*3, "%02hhx ", cur_pos[i]);
            if (cur_pos[i] > 31 &&  cur_pos[i] < 127)
            sprintf(str_readable + i, "%c", (char)(cur_pos[i]));
            else
            sprintf(str_readable + i, "%c", '*');
        }
        length -= 16;
        cur_pos += 16;
        PrintText("%s: %s: %s\r\n", str_addr, str_data, str_readable);
    }

    if (length > 0)
    {
        sprintf(str_addr, "%-16lx", (unsigned long)(void *)cur_pos);
        for (i = 0; i < length; i++)
        {
            sprintf(str_data + i*3, "%02hhx ", cur_pos[i]);
            if (cur_pos[i] > 31 &&  cur_pos[i] < 127)
            sprintf(str_readable + i, "%c", (char)(cur_pos[i]));
            else
            sprintf(str_readable + i, "%c", '*');
        }
        for (i = length; i < 16; i++)
        {
            sprintf(str_data + i*3, "%s", "   ");
            sprintf(str_readable + i, "%c", ' ');
        }
        PrintText("%s: %s: %s\r\n", str_addr, str_data, str_readable);
    }


}


#endif
