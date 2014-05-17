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
#include <stdlib.h>
#include "global_symbols.h"
#include "app_property.h"
#include "res.h"

#include "common.h"
#include "utils.h"
#include "file_open_history.h"
#include "ext_utils_textout.h"
#include "ext_utils_av.h"

TCHAR   szFrameWinClassName[] = TEXT ("frame_win") ;
HWND    hwnd_frame;

HWND hwndTip;

#ifdef _USE_SPLITTER_FRAME
HWND    hwnd_splt_we;
HWND    hwnd_splt_ns;
int display_left=1;
int display_bottom=1;

int we_pos;
int ns_pos;

#endif

int display_toolbar=1;
int display_statusbar=1;

int TOOLBAR_BUTTON3_DOWN;
char doc_file_path[MAX_FILE_PATH_LEN];
char file_to_open[MAX_FILE_PATH_LEN];

void resize_window(HWND hwnd)
{
    RECT rect;
    GetClientRect(hwnd,&rect);
    SendMessage(hwnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(rect.right, rect.bottom));
}

void set_frame_title(TCHAR *file_name)
{
    TCHAR info[128];
    sprintf(info, TEXT("%s - %s"), szAppName, file_name);
    SetWindowText(hwnd_frame, info);

}


int doc_save_proc()
{
    int ret;
    if (doc_modified)
    {
        ret=AskConfirmation_3state(hwnd_frame, TEXT("是否保存当前文件?"), szAppName);
        if (IDCANCEL == ret) return 1;
        if (IDYES == ret)
        {
            SendMessage(hwnd_frame, WM_COMMAND, IDM_FILE_SAVE, 0);
            return doc_modified;
        }
    }

    return 0;
}

void open_file()
{
    if (doc_save_proc()) return;

    load_doc_file(file_to_open);;
    strcpy(doc_file_path, file_to_open);
    set_frame_title(strrchr(doc_file_path, '\\')+1);
    update_statusbar();
    update_file_open_history(doc_file_path);
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc ;
    PAINTSTRUCT ps ;
    static int cxClient, cyClient;
    HMENU hMenu;
    POINT point;
    RECT		rect ;
    int  item_id;
    
    int ret;

#ifdef _USE_SPLITTER_FRAME
    int upper_win_y=toolbar_height, 
        right_win_x=we_pos, 
        right_win_width=cxClient-we_pos, 
        upper_win_height,
        bottom_win_height;

#endif

    switch (message)
    {
        case WM_CREATE:
            hwnd_frame = hwnd;
            
            hwndTip =CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
                        WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP |TTS_BALLOON,
                        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
                        hwnd,
                        NULL,
                        g_hInstance, 
                        NULL);
#ifdef _USE_SPLITTER_FRAME
            hwnd_left = CreateWindow (szLeftWinClassName, TEXT ("sub win"),
                WS_CHILD,
                point.x, point.y,
                we_pos-SPLT_WIDTH, ns_pos-SPLT_WIDTH,
                hwnd, NULL, g_hInstance, NULL) ;

            ShowWindow (hwnd_left, 1) ;
            UpdateWindow (hwnd_left) ;

            hwnd_splt_we= CreateWindow (szSpltWeClassName, TEXT ("sub win"),
                WS_CHILD,
                we_pos-SPLT_WIDTH,
                            point.y,
                  			SPLT_WIDTH, ns_pos-SPLT_WIDTH,
                hwnd, NULL, g_hInstance, NULL) ;
            ShowWindow (hwnd_splt_we, 1) ;
            UpdateWindow (hwnd_splt_we) ;


            hwnd_right = CreateWindow (szRightWinClassName, TEXT ("sub win"),
                WS_CHILD,
                we_pos,
                            point.y,
                  			cxClient-we_pos, ns_pos-SPLT_WIDTH,
                hwnd, NULL, g_hInstance, NULL) ;

            ShowWindow (hwnd_right, 1) ;
            UpdateWindow (hwnd_right) ;
            
            hwnd_splt_ns= CreateWindow (szSpltNsClassName, TEXT ("sub win"),
                WS_CHILD,
                point.x, ns_pos-SPLT_WIDTH,
                cxClient, SPLT_WIDTH,
                hwnd, NULL, g_hInstance, NULL) ;
            
            ShowWindow (hwnd_splt_ns, 1) ;
            UpdateWindow (hwnd_splt_ns) ;

            hwnd_bottom = CreateWindow (szBottomWinClassName, TEXT ("sub win"),
                WS_CHILD,
                point.x,    ns_pos,
                  			cxClient, cyClient-ns_pos,
                hwnd, NULL, g_hInstance, NULL) ;

            ShowWindow (hwnd_bottom, 1) ;
            UpdateWindow (hwnd_bottom) ;

hMenu = GetMenu(hwnd);
hMenu = GetSubMenu(hMenu, 1);
AppendMenu(hMenu, MF_SEPARATOR, 0,  TEXT("")) ;
AppendMenu(hMenu, MF_STRING|MF_CHECKED, IDM_APP_LEFT_WIN,  TEXT("左面板")) ;
AppendMenu(hMenu, MF_STRING|MF_CHECKED, IDM_APP_BOTTOM_WIN,  TEXT("底面板")) ;
#endif
            CreateToolbar();

            CreateStatusBar();

            DragAcceptFiles(hwnd, TRUE);

    set_frame_title(TEXT("无标题"));

            ret=get_last_doc_file(file_to_open);

            if (0==ret) open_file();

            av_test();

            WriteInfo(TEXT("欢迎使用win-dev-framework"));
            return 0 ;

#ifdef _USE_SPLITTER_FRAME
        case WM_SPLITTER_X:
        {
            we_pos=wParam;
            resize_window(hwnd);
            return 0 ;
        }

        case WM_SPLITTER_Y:
        {
            ns_pos=wParam;
            resize_window(hwnd);
            return 0 ;
        }

#endif

        case WM_SIZE:
        {
      		cxClient = LOWORD (lParam) ;
      		cyClient = HIWORD (lParam) ;

             MoveWindow	(	hwnd_toolbar, 	0, 0,
                cxClient, toolbar_height, TRUE) ;
             
      	    MoveWindow	(	hwnd_statusbar, 0, cyClient-statusbar_height,
                cxClient, statusbar_height, TRUE) ;

#ifdef _USE_SPLITTER_FRAME
            if (we_pos==0 || ns_pos==0)
            {
                we_pos = 200;
                ns_pos = cyClient-300;

            }

        upper_win_y=display_toolbar?toolbar_height:0;

        right_win_x=display_left?we_pos:0;
        right_win_width=display_left?cxClient-we_pos:cxClient;
        if (display_bottom)
        {
            upper_win_height=ns_pos-SPLT_WIDTH;
            upper_win_height -= upper_win_y;
        }
        else
        {
            upper_win_height=cyClient;
            upper_win_height -= upper_win_y;
            upper_win_height -= (display_statusbar?statusbar_height:0);

        }

        bottom_win_height = cyClient-ns_pos;
        bottom_win_height -= (display_statusbar?statusbar_height:0);

            //ClientToScreen(hwnd, &point);
           			// Move the buttons to the new center

      	    MoveWindow	(	hwnd_toolbar, 	0, 0,
                cxClient, toolbar_height, TRUE) ;

      	    MoveWindow	(	hwnd_left, 	0, upper_win_y,
                we_pos-SPLT_WIDTH, upper_win_height, TRUE) ;

      	    MoveWindow	(	hwnd_splt_we, 	we_pos-SPLT_WIDTH,
                            upper_win_y,
                  			SPLT_WIDTH, upper_win_height, TRUE) ;

      	    MoveWindow	(	hwnd_right, 	right_win_x,
                            upper_win_y,
                  			right_win_width, upper_win_height, TRUE) ;

      	    MoveWindow	(	hwnd_splt_ns, 	0, ns_pos-SPLT_WIDTH,
                cxClient, SPLT_WIDTH, TRUE) ;

      	    MoveWindow	(	hwnd_bottom, 0,    ns_pos,
                  			cxClient, bottom_win_height, TRUE) ;

      	    MoveWindow	(	hwnd_statusbar, 	0, cyClient-statusbar_height,
                cxClient, statusbar_height, TRUE) ;


#endif
          	return 0 ;
        }


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

        case WM_DROPFILES :
            DragQueryFile((HDROP)wParam,
                          0,
                          file_to_open,
                          sizeof(file_to_open));
            DragFinish((HDROP)wParam);
            open_file();
            return 0;

        case WM_INITMENU:

            if (lParam == 0)
            {
                hMenu = GetMenu(hwnd);
                hMenu = GetSubMenu(hMenu, 0);
                hMenu = GetSubMenu(hMenu, 5);
                populate_recent_files(hMenu);
            }


            return 0;

        case 	WM_COMMAND:
            hMenu = GetMenu (hwnd) ;
            item_id = LOWORD(wParam);
            switch (item_id)
            {
                case    IDM_APP_ABOUT:
                DialogBox (g_hInstance, TEXT("ABOUTBOX"), hwnd, AboutDlgProc) ;
               	return 0 ;

                case    IDM_GET_NEW_VERSION:
                ShellExecute(NULL, "open"
                    , "http://sourceforge.net/projects/xb-ether-tester/files/latest/download?source=directory"
                    , NULL, NULL, SW_SHOWNORMAL);

               	return 0 ;

                case    IDM_GET_SOURCE:
                ShellExecute(NULL, "open"
                    , "https://sourceforge.net/projects/windevframework/files/v1.x/"
                    , NULL, NULL, SW_SHOWNORMAL);

               	return 0 ;

                case    IDM_OPEN_OFFICIAL_SITE:
                ShellExecute(NULL, "open"
                    , "http://sunmingbao.freevar.com/"
                    , NULL, NULL, SW_SHOWNORMAL);

               	return 0 ;

                case    IDM_APP_EXIT:
       				SendMessage (hwnd, WM_CLOSE, 0, 0) ;
       				return 0 ;

                case    IDM_APP_TOOLBAR_WIN:
                    if (display_toolbar)
                    {
                        display_toolbar = 0;
           				ShowWindow(hwnd_toolbar, 0);
                        UpdateWindow (hwnd_frame) ;
                        CheckMenuItem (hMenu, item_id, MF_UNCHECKED) ;

                    }
                    else
                    {
                        display_toolbar= 1;
           				ShowWindow(hwnd_toolbar, 1);
                        UpdateWindow (hwnd_frame) ;
                        CheckMenuItem (hMenu, item_id, MF_CHECKED) ;
                    }
                    resize_window(hwnd_frame);
       				return 0 ;

                case    IDM_APP_STATUSBAR_WIN:
                    if (display_statusbar)
                    {
                        display_statusbar = 0;
           				ShowWindow(hwnd_statusbar, 0);
                        UpdateWindow (hwnd_frame) ;
                        CheckMenuItem (hMenu, item_id, MF_UNCHECKED) ;

                    }
                    else
                    {
                        display_statusbar= 1;
           				ShowWindow(hwnd_statusbar, 1);
                        UpdateWindow (hwnd_frame) ;
                        CheckMenuItem (hMenu, item_id, MF_CHECKED) ;
                    }
                    resize_window(hwnd_frame);
       				return 0 ;
#ifdef _USE_SPLITTER_FRAME
        case    IDM_APP_BOTTOM_WIN:
        if (display_bottom)
        {
            display_bottom = 0;
				ShowWindow(hwnd_bottom, 0);
            ShowWindow(hwnd_splt_ns, 0);
            UpdateWindow (hwnd_frame) ;
            CheckMenuItem (hMenu, item_id, MF_UNCHECKED) ;

        }
        else
        {
            display_bottom= 1;
				ShowWindow(hwnd_bottom, 1);
            ShowWindow(hwnd_splt_ns, 1);
            UpdateWindow (hwnd_frame) ;
            CheckMenuItem (hMenu, item_id, MF_CHECKED) ;
        }
        resize_window(hwnd_frame);
			return 0 ;

    case    IDM_APP_LEFT_WIN:
        if (display_left)
        {
            display_left = 0;
				ShowWindow(hwnd_left, 0);
            ShowWindow(hwnd_splt_we, 0);
            UpdateWindow (hwnd_frame) ;
            CheckMenuItem (hMenu, item_id, MF_UNCHECKED) ;



        }
        else
        {
            display_left= 1;
				ShowWindow(hwnd_left, 1);
            ShowWindow(hwnd_splt_we, 1);
            UpdateWindow (hwnd_frame) ;
            CheckMenuItem (hMenu, item_id, MF_CHECKED) ;
        }
        resize_window(hwnd_frame);
			return 0 ;
#endif

                case    IDT_TOOLBAR_BUTTON1:
                    WinPrintf(hwnd, "IDT_TOOLBAR_BUTTON1");
               	    return 0 ;

                case    IDT_TOOLBAR_BUTTON2:
                    WinPrintf(hwnd, "IDT_TOOLBAR_BUTTON2");
       				return 0 ;

                case    IDT_TOOLBAR_BUTTON3:
                    TOOLBAR_BUTTON3_DOWN = !TOOLBAR_BUTTON3_DOWN;
                    SendMessage(hwnd_toolbar, TB_CHECKBUTTON, IDT_TOOLBAR_BUTTON3, TOOLBAR_BUTTON3_DOWN);
       				return 0 ;

                case    IDM_FILE_SAVE:
                {
                    if (doc_file_path[0]==0)
                    {
                        SendMessage(hwnd, WM_COMMAND, IDM_FILE_SAVE_AS, 0);
                        return 0 ;
                    }
                    save_doc_file(doc_file_path);
                   	return 0 ;
                }

                case    IDM_FILE_SAVE_AS:
                {
                        ret=get_save_file_name(file_to_open, hwnd, DOC_FILE_FILTER, DOC_FILE_SUFFIX);
                        if (ret) return 0 ;
                        save_doc_file(file_to_open);
                        open_file();
                       	return 0 ;
                }
                

                case    IDM_FILE_NEW:
                {
                    if (doc_save_proc()) return 0;
                    doc_file_path[0]=0;
                    set_frame_title(TEXT("无标题"));
                    doc_modified=0;
                    return 0 ;
                }
                
                case    IDM_FILE_OPEN:
                {
                    if (get_open_file_name(file_to_open, hwnd, DOC_FILE_FILTER))
                        return 0;
                    open_file();
                   	return 0 ;
                }

                case    ID_FILE_RECENT_FILE_BEGIN+0:
                case    ID_FILE_RECENT_FILE_BEGIN+1:
                case    ID_FILE_RECENT_FILE_BEGIN+2:
                case    ID_FILE_RECENT_FILE_BEGIN+3:
                case    ID_FILE_RECENT_FILE_BEGIN+4:
                case    ID_FILE_RECENT_FILE_BEGIN+5:
                case    ID_FILE_RECENT_FILE_BEGIN+6:
                case    ID_FILE_RECENT_FILE_BEGIN+7:
                case    ID_FILE_RECENT_FILE_BEGIN+8:
                case    ID_FILE_RECENT_FILE_BEGIN+9:
                {
                    get_file_path_by_idx(file_to_open
                        , item_id - ID_FILE_RECENT_FILE_BEGIN);

                    if (file_exists(file_to_open)) open_file();
                    return 0 ;

                }


            }

            return 0;

     	case	WM_CLOSE:
            if (doc_save_proc()) return 0;
            DestroyWindow (hwnd) ;
            return 0 ;

        case    WM_DESTROY :
            PostQuitMessage (0) ;
            return 0 ;
    }
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

int register_frame()
{
    WNDCLASS    wndclass;
    wndclass.style      = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc= WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance  = g_hInstance;
    wndclass.hIcon      = LoadIcon (g_hInstance, TEXT("app_icon"));
#if 0
    /* 如果想换光标，就用如下代码 */
    wndclass.hCursor    = LoadCursor (g_hInstance, TEXT("main_window_cursor"));
#else
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);
#endif

    wndclass.hbrBackground  = (HBRUSH)GetStockObject(GRAY_BRUSH);
    wndclass.lpszMenuName   = TEXT("MY_MENU");
    wndclass.lpszClassName  = szFrameWinClassName;

    if (!RegisterClass (&wndclass))
     {
        MessageBox (NULL, TEXT("Register frame window class failed.\r\nProgram requires Windows NT!"),
          szAppName, MB_ICONERROR) ;
        return FAIL;
     }

    return SUCCESS;

}


int create_windows(int iCmdShow)
{
    hwnd_frame = CreateWindow (szFrameWinClassName, szAppName,
            WS_OVERLAPPEDWINDOW|WS_MAXIMIZE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL, NULL, g_hInstance, NULL) ;

    
    ShowWindow (hwnd_frame, SW_MAXIMIZE) ;
    UpdateWindow (hwnd_frame) ;

    return 0;

}




