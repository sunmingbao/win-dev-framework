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
#include <windowsx.h>
#include "common.h"
#include "global_symbols.h"
#include "res.h"

TCHAR szLeftWinClassName[] = TEXT ("left_win") ;
HWND    hwnd_left;
HWND  hwnd_button_left_close;

#if 0
HWND    hwnd_tab1;
TCHAR szTab1WinClassName[] = TEXT ("tab1_win") ;

TCHAR *tab_icons[] = {TEXT("my_frame_icon"), TEXT("my_frame_icon")};
TCHAR *tab_labels[] = {TEXT("tab1"), TEXT("tab2")};

LRESULT CALLBACK tab1_WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);



HWND  hwnd_tv;

#endif

LRESULT CALLBACK left_WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc ;
    PAINTSTRUCT ps ;
    HWND    hwnd_sub ;
    RECT		rect ;
    int cxClient, cyClient;

    
    switch (message)
    {
        case WM_CREATE:
            hwnd_left = hwnd;
                        hwnd_button_left_close =	CreateWindow ( TEXT("button"),TEXT("X"),
   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    20, 20,
    30, 30,
                               hwnd, (HMENU)ID_BUTTON_LEFT_CLOSE,
               g_hInstance, NULL) ;

#if 0
            register_tab1_win();
            hwnd_tab1 = CreateWindow (szTab1WinClassName, TEXT (""),
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                10, 10,
                50, 50,
                hwnd_left, NULL, g_hInstance, NULL) ;
#endif
            return 0 ;

        case WM_SIZE:
      		cxClient = LOWORD (lParam) ;
      		cyClient = HIWORD (lParam) ;

            MoveWindow	(hwnd_button_left_close, 	cxClient-25, 0,
                25, 25, TRUE) ;
            //MoveWindow(hwnd_tab1, 	0, 25,  cxClient, cyClient-25, TRUE) ;
            return 0 ;


        case 	WM_COMMAND:
            switch (LOWORD(wParam))
            {
                  
                case    ID_BUTTON_LEFT_CLOSE:
                    SetFocus(hwnd_right);
       				SendMessage(hwnd_frame, WM_COMMAND, MAKEWPARAM(IDM_APP_LEFT_WIN, 0),0);
       				return 0 ;
             }
            break;

    }
    
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

int register_left_win()
{
    WNDCLASS    sub_wndclass;
    sub_wndclass.style      = CS_HREDRAW | CS_VREDRAW;
    sub_wndclass.lpfnWndProc= left_WndProc;
    sub_wndclass.cbClsExtra = 0;
    sub_wndclass.cbWndExtra = 0;
    sub_wndclass.hInstance  = g_hInstance;
    sub_wndclass.hIcon      = LoadIcon (g_hInstance, TEXT("my_frame_icon"));
    sub_wndclass.hCursor    = LoadCursor (NULL, IDC_ARROW);
    //sub_wndclass.hbrBackground  = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_3DFACE));
    //sub_wndclass.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(0,0,200));
    sub_wndclass.hbrBackground  = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_ACTIVECAPTION));
    sub_wndclass.lpszMenuName   = NULL;
    sub_wndclass.lpszClassName  = szLeftWinClassName;


    if (!RegisterClass (&sub_wndclass))
     {
        MessageBox (NULL, TEXT ("Program requires Windows NT!"),
          szAppName, MB_ICONERROR) ;
        return FAIL;
     }

    return SUCCESS;

}

#if 0
int register_tab1_win()
{
    WNDCLASS    sub_wndclass;
    sub_wndclass.style      = CS_HREDRAW | CS_VREDRAW;
    sub_wndclass.lpfnWndProc= tab1_WndProc;
    sub_wndclass.cbClsExtra = 0;
    sub_wndclass.cbWndExtra = 0;
    sub_wndclass.hInstance  = g_hInstance;
    sub_wndclass.hIcon      = LoadIcon (g_hInstance, TEXT("my_frame_icon"));
    sub_wndclass.hCursor    = LoadCursor (NULL, IDC_ARROW);
    sub_wndclass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
    sub_wndclass.lpszMenuName   = NULL;
    sub_wndclass.lpszClassName  = szTab1WinClassName;


    if (!RegisterClass (&sub_wndclass))
     {
        MessageBox (NULL, TEXT ("Program requires Windows NT!"),
          szAppName, MB_ICONERROR) ;
        return FAIL;
     }

    return SUCCESS;

}


HTREEITEM parentItem,childItem1, childItem2, childItem3;

LRESULT CALLBACK tab1_WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc ;
    PAINTSTRUCT ps ;
    HWND    hwnd_sub ;
    RECT		rect ;
    int cxClient, cyClient;
    int ret;

    
    switch (message)
    {
        case WM_CREATE:
        {
            HIMAGELIST imageList;
            HICON icon;

            hwnd_tv =	CreateWindow (WC_TREEVIEW,TEXT("haha"),
   WS_CHILD | WS_VISIBLE|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT|TVS_SHOWSELALWAYS,
    20, 20,
    50, 50,
                               hwnd, (HMENU)ID_TV,
               g_hInstance, NULL) ;

#if 0
            imageList = ImageList_Create(32,
                                          32,
                                          ILC_COLORDDB | ILC_MASK,
                                          4,
                                          0);

// load icons and add them to ImageList
// PARAMS: hInstance, filename, type, width, height, flag
icon = (HICON)LoadImage(g_hInstance,
                          TEXT("config_icon"),
                          IMAGE_ICON, 32, 32,
                          LR_DEFAULTCOLOR);
ImageList_AddIcon(imageList, icon);
icon = (HICON)LoadImage(g_hInstance,
                          TEXT("stream_icon"),
                          IMAGE_ICON, 32, 32,
                          LR_DEFAULTCOLOR);
ImageList_AddIcon(imageList, icon);
icon = (HICON)LoadImage(g_hInstance,
                          TEXT("speed_icon"),
                          IMAGE_ICON, 32, 32,
                          LR_DEFAULTCOLOR);
ImageList_AddIcon(imageList, icon);
icon = (HICON)LoadImage(g_hInstance,
                          TEXT("cap_cfg_icon"),
                          IMAGE_ICON, 32, 32,
                          LR_DEFAULTCOLOR);
ImageList_AddIcon(imageList, icon);
SendMessage(hwnd_tv, TVM_SETIMAGELIST,
                  (WPARAM)TVSIL_NORMAL, (LPARAM)imageList);
#endif
    // add root item
    parentItem = insertItem(hwnd_tv, TEXT("配置"), TVI_ROOT, TVI_LAST, 0, 0, NULL);

    // add some children
    childItem1 = insertItem(hwnd_tv, TEXT("流"), parentItem, TVI_LAST, 1, 1, NULL);
    childItem2 = insertItem(hwnd_tv, TEXT("流控"), parentItem, TVI_LAST, 2, 2, NULL);
    childItem3 = insertItem(hwnd_tv, TEXT("抓包"), parentItem, TVI_LAST, 3, 3, NULL);

    TreeView_Expand(hwnd_tv, parentItem, TVM_EXPAND);


            ShowWindow (hwnd_tv, 1) ;
            UpdateWindow (hwnd_tv) ;
    TreeView_Select(hwnd_tv, childItem1, TVGN_CARET);

            return 0 ;
        }

        case WM_SIZE:
      		cxClient = LOWORD (lParam) ;
      		cyClient = HIWORD (lParam) ;
            MoveWindow(hwnd_tv, 	0, 0,
                cxClient, cyClient, TRUE) ;

            return 0 ;

        case WM_PAINT :
            hdc = BeginPaint (hwnd, &ps) ;
            
            //draw some thing here
            GetClientRect (hwnd, &rect) ;
		    DrawText (hdc, TEXT ("tab1 win!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
  			EndPaint (hwnd, &ps) ;
			return 0 ;

case WM_NOTIFY:
{
   switch(LOWORD(wParam))
   { 
     case ID_TV:
     // if code == NM_CLICK - Single click on an item
     if(((LPNMHDR)lParam)->code == TVN_SELCHANGED) 
     {
        HTREEITEM Selected;
        TV_ITEM tvi;
        char Text[255]="";
        memset(&tvi,0,sizeof(tvi));
        Selected=(HTREEITEM)SendDlgItemMessage(hwnd_tab1,
           ID_TV,TVM_GETNEXTITEM,TVGN_CARET,(LPARAM)Selected);

       if (!init_over) break;
       
       if (childItem1==Selected)
        {
            ShowWindow (hwnd_stream, 1) ;
            ShowWindow (hwnd_fc, 0) ;
        }

       else if (childItem2==Selected)
        {
            //ShowWindow (hwnd_stream, 0) ;
            //ShowWindow (hwnd_fc, 1) ;
            //ret=DialogBox(g_hInstance, TEXT("FC_CFG_DLG"), hwnd, FcCfgDlgProc);

            //TreeView_SelectItem(hwnd_tv, childItem1);
        }
      else if (childItem3==Selected)
        {
            //ShowWindow (hwnd_stream, 0) ;
            //ShowWindow (hwnd_fc, 1) ;
            //ret=DialogBox(g_hInstance, TEXT("PKT_CAP_CFG_DLG"), hwnd, PktCapCfgDlgProc);

            //TreeView_SelectItem(hwnd_tv, childItem1);
        }


     }
   }
break;

}

    }
    
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}
#endif
//int a[10]={[0 ... 2]={1,2,3}};
