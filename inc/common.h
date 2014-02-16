/* 
 * ������Ϊ��ѡ���Դ������
 * �������İ�Ȩ(����Դ�뼰�����Ʒ����汾)��һ�й������С�
 * ����������ʹ�á�������������
 * ��Ҳ�������κ���ʽ���κ�Ŀ��ʹ�ñ�����(����Դ�뼰�����Ʒ����汾)���������κΰ�Ȩ���ơ�
 * =====================
 * ����: ������
 * ����: sunmingbao@126.com
 */

#ifndef __COMMON_H_
#define __COMMON_H_

#include <tchar.h> 
#include <commctrl.h>
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#include "defs.h"
#include "app_property.h"

#define    ARRAY_SIZE(array_name)    (sizeof(array_name)/sizeof(array_name[0]))
static inline int AskConfirmation(HWND hwnd, TCHAR *str, TCHAR *cap_str)
{
    return MessageBox(hwnd
                     ,str
                     ,cap_str
                     ,MB_YESNO | MB_ICONQUESTION) ;
}

static inline int AskConfirmation_3state(HWND hwnd, TCHAR *str, const TCHAR *cap_str)
{
    return MessageBox(hwnd
                     ,str
                     ,cap_str
                     ,MB_YESNOCANCEL | MB_ICONQUESTION) ;
}

int WinPrintf(HWND hwnd, TCHAR * szFormat, ...);
static inline int win_width(HWND hwnd)
{

    RECT		rect;
    GetWindowRect (hwnd, &rect);
    return rect.right - rect.left;
}

static inline int win_height(HWND hwnd)
{

    RECT		rect;
    GetWindowRect (hwnd, &rect);
    return rect.bottom - rect.top;
}

static inline int win_left(HWND hwnd)
{

    RECT		rect;
    GetWindowRect (hwnd, &rect);
    return rect.left;
}

static inline int win_top(HWND hwnd)
{

    RECT		rect;
    GetWindowRect (hwnd, &rect);
    return rect.top;
}

static inline int win_bottom(HWND hwnd)
{

    RECT		rect;
    GetWindowRect (hwnd, &rect);
    return rect.bottom;
}

static inline void get_relative_pos(RECT *rect1, RECT *rect2, RECT *rect3)
{
    RECT rect_tmp;
    RECT* rect=&rect_tmp;
    rect->left=rect2->left - rect1->left;
    rect->right=rect2->right - rect1->left;
    rect->top=rect2->top - rect1->top;
    rect->bottom=rect2->bottom - rect1->top;
    *rect3 = rect_tmp;
}

static inline void get_relative_pos_self(RECT *rect1, RECT *rect)
{

    rect->right=rect1->right - rect1->left;
    rect->left=0;
    rect->bottom=rect1->bottom - rect1->top;
    rect->top=0;

}

void center_child_win(HWND hparent, HWND hchild);

static inline void get_client_rect_screen(HWND hparent, RECT *rect)
{

    RECT		rect_tmp;
    POINT Point = {0, 0};
    ClientToScreen(hparent, &Point);


    GetClientRect (hparent, &rect_tmp);
    rect_tmp.left = Point.x;
    rect_tmp.right += Point.x;
    rect_tmp.top = Point.y;
    rect_tmp.bottom += Point.y;
    *rect = rect_tmp;
    
}

static inline HANDLE launch_thread(LPTHREAD_START_ROUTINE ThreadFunc, LPVOID lpParameter)
{
    HANDLE hThrd;
    DWORD threadId;
    
    hThrd = CreateThread(NULL,
        0,
        ThreadFunc,
        lpParameter,
        0,
        &threadId );
    return hThrd;

}


int get_open_file_name(char *file_name, HWND hwnd, char *filter_str);


int SelRvs(HWND hList);
int SelAll(HWND hList);
int DelSel(HWND hList);
int GetIndex(HWND hList);
int GetSelCnt(HWND hList);

void delete_file_f(char *file_path);
int save_file_path_valid(char *file_path);
int file_exists(char *file_path);

static inline int time_a_smaller_than_b(struct timeval *a, struct timeval *b)
{
    if (a->tv_sec < b->tv_sec) return 1;
    if (a->tv_sec > b->tv_sec) return 0;

    return a->tv_usec < b->tv_usec;
}


static inline unsigned long time_a_between_b(struct timeval *a, struct timeval *b)
{
    if (a->tv_sec == b->tv_sec) return b->tv_usec - a->tv_usec;
    return 1000000 + b->tv_usec - a->tv_usec;
}


void set_int_text(HWND hwnd, int value);
int get_int_text(HWND hwnd);
void inc_int_text(HWND hwnd, int value);

static inline int button_checked(HWND hwnd)
{
    return (Button_GetState(hwnd) & BST_CHECKED)!=0;
}


static inline void button_check(HWND hwnd, int is_check)
{
    WPARAM wParam=(is_check?BST_CHECKED:BST_UNCHECKED);
    SendMessage(hwnd, BM_SETCHECK, wParam, 0);
}

static inline void set_I64u_text(HWND hwnd, uint64_t value)
{
    char info[32];
    sprintf(info, "%I64u", value);
    SetWindowText(hwnd, info);
}

void change_child_height(HWND child, int height);
void change_child_width(HWND child, int width);
void change_child_size(HWND child, int width, int height);
void move_child_pos(HWND child, int x, int y);
void move_child_a2b_bottom_left(HWND a, HWND b, int offset);
void move_child_a2b_bottom_right(HWND a, HWND b, int offset);
void move_child_a2b_right_top(HWND a, HWND b, int offset);
void move_child_a2b_right_bottom(HWND a, HWND b, int offset);
void move_child_a2b_left_top(HWND a, HWND b, int offset);
void right_include_child(HWND child, int offset);
void bottom_include_child(HWND child, int offset);
void h_arrange_win(HWND hleader, int nr_member, HWND hmembers[], int offset);
void h_arrange_win_id(HWND hleader, int nr_member, int hmember_ids[], int offset);
void v_arrange_win_id(HWND hleader, int nr_member, int hmember_ids[], int offset);
int a_include_b_right(HWND a, HWND b);

void clear_comb(HWND hwndCtl);
int str2int(char *info);

static inline void err_info_box(HWND hparent, TCHAR *info)
{
    MessageBox(hparent, info, szAppName, MB_ICONERROR);
}

#endif
