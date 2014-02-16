/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */


#ifndef __GLOBAL_SYMBOLS_H_
#define __GLOBAL_SYMBOLS_H_

#include <windows.h>
#include "defs.h"



extern HINSTANCE g_hInstance;
extern int init_over;

int register_frame();
void set_frame_title(TCHAR *file_name);

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam);


#define TIMER_STATUS_BAR 1
#define TIMER_STATUS_GAP 100

#define TIMER_TIP_WIN_SHOW    2
#define TIMER_TIP_WIN_SHOW_GAP 3

#define TIMER_TIP_WIN_HIDE    3
#define TIMER_TIP_WIN_HIDE_GAP 30

#define TIMER_TIP_WIN_LAST    4
#define TIMER_TIP_WIN_LAST_GAP 500

extern HWND    hwnd_frame;
extern HWND hwndTip;
extern int  doc_modified;

extern TCHAR szSubWinClassName[];
extern HWND  hwnd_left;
extern HWND  hwnd_tv;


extern TCHAR szRightWinClassName[];
extern HWND    hwnd_right;
extern HWND    hwnd_stream;
extern HWND    hwnd_fc;
extern HWND    hwnd_lv;

extern TCHAR szBottomWinClassName[];
extern HWND    hwnd_bottom;

#define    SPLT_WIDTH    (6)
extern TCHAR szSpltWeClassName[];
extern TCHAR szSpltNsClassName[];

extern HWND    hwnd_splt_we;
extern HWND    hwnd_splt_ns;

extern int we_pos;
extern int ns_pos;

extern HWND    hwnd_toolbar;
extern int toolbar_height;

extern HWND    hwnd_statusbar;
extern int statusbar_height;

extern TCHAR szHexEditWinClassName[];
extern char  *test_buf;
extern int cur_data_len;
extern int is_read_only;





int CreateToolbar();
int CreateStatusBar();
int create_windows(int iCmdShow);
void add_tip(HWND htip_control, HWND hwnd, TCHAR *tips);

void resize_window(HWND hwnd);

#endif

