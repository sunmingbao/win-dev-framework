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
#include "app_property.h"
#include "common.h"
#include "global_symbols.h"

#include "res.h"


BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam)
{
    TCHAR info[1024];

    sprintf(info
        , "%s    V%c.%c.%c\r\n"
        "(编译时间: %s) \r\n\r\n"
        "作者：%s (来自 %s)\r\n\r\n"
        "======================\r\n\r\n"
        "本软件为免费、开源软件。\r\n"
        "本软件的版权(包括源码及二进制发布版本)归一切公众所有。\r\n"
        "您可以自由使用、传播本软件。\r\n"
        "您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。\r\n\r\n"
        "======================\r\n\r\n"
        
        "本软件是是一个windows程序开发框架，基于C语言和mingw工具链。\r\n"
        "用户可以以此为基础，快速开始自己的windows程序开发。\r\n\r\n"
        "======================\r\n\r\n"
        "关于本软件，您有任何问题或建议，欢迎联系作者。\r\n"
        "邮箱:%s\r\n"
        "%s"
        , szAppName
        , version[0] , version[1] , version[2]
        , BUILD_TIME
        , szAuthor, szCompany
        , szEmail
        , szContact);
     	switch (message)
     	{
     	case 	WM_INITDIALOG :
                center_child_win(hwnd_frame, hDlg);
                SetDlgItemText(hDlg, ID_ABOUT_INFO, info);
                SetFocus(GetDlgItem(hDlg, IDOK));
          		return FALSE ;

        case 	WM_CLOSE:
   				SendMessage(hDlg, WM_COMMAND, IDCANCEL, 0);
   				return TRUE ;

     	case 	WM_COMMAND :
          		switch (LOWORD (wParam))
          		{

                case 	ID_AB_SOURCE:
               		SendMessage(hwnd_frame, WM_COMMAND, IDM_GET_SOURCE, 0);
               		return TRUE ;
               		
               	case 	ID_AB_SITE:
               		SendMessage(hwnd_frame, WM_COMMAND, IDM_OPEN_OFFICIAL_SITE, 0);
               		return TRUE ;
               		
               	case 	ID_AB_UPDATE:
               		SendMessage(hwnd_frame, WM_COMMAND, IDM_GET_NEW_VERSION, 0);
               		return TRUE ;
        
          		case 	IDOK :
          		case 	IDCANCEL :
               				EndDialog (hDlg, 0) ;
               				return TRUE ;
          }
          		break ;
     }
  	return FALSE ;
}



