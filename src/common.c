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
#include "common.h"
#include <tchar.h>     
#include <stdio.h>

#include "global_symbols.h"



void rect_client2scrn(HWND h, RECT *rect_s, RECT *rect_d)
{
    RECT rect1;
    POINT point;

    point.x=rect_s->left;
    point.y=rect_s->top;
    ClientToScreen(h, &point);
    rect_d->left=point.x;
    rect_d->top=point.y;

    point.x=rect_s->right;
    point.y=rect_s->bottom;
    ClientToScreen(h, &point);
    rect_d->right=point.x;
    rect_d->bottom=point.y;

}

void get_client_rect_scrn(HWND h, RECT *rect)
{
    RECT rect1;
    GetClientRect(h, &rect1);
    rect_client2scrn(h, &rect1, rect);
}

void change_child_width(HWND child, int width)
{
    HWND p=GetParent(child);
    RECT rect0, rect1, rect2;
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(child, &rect1);
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(child, 	rect1.left, rect1.top,
                width, rect1.bottom-rect1.top, TRUE) ;
}

void change_child_height(HWND child, int height)
{
    HWND p=GetParent(child);
    RECT rect0, rect1, rect2;
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(child, &rect1);
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(child, 	rect1.left, rect1.top,
                rect1.right-rect1.left, height, TRUE) ;
}

void change_child_size(HWND child, int width, int height)
{
    change_child_width(child, width);
    change_child_height(child,height);
}

void move_child_pos(HWND child, int x, int y)
{
    HWND p=GetParent(child);
    RECT rect0, rect1, rect2;
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(child, &rect1);
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(child, 	x, y,
                rect1.right-rect1.left, rect1.bottom-rect1.top, TRUE) ;
}

void move_child_a2b_left(HWND a, HWND b, int offset)
{
    HWND p=GetParent(a);
    RECT rect0, rect1, rect2;
    int width = win_width(a);
    int height = win_height(a);
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(a, &rect1);
    GetWindowRect(b, &rect2);
    rect1.left = rect2.left-offset-width;
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(a, 	rect1.left, rect1.top,
                width, height, TRUE) ;
}

void move_child_a2b_right(HWND a, HWND b, int offset)
{
    HWND p=GetParent(a);
    RECT rect0, rect1, rect2;
    int width = win_width(a);
    int height = win_height(a);
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(a, &rect1);
    GetWindowRect(b, &rect2);
    rect1.left = rect2.right+offset;
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(a, 	rect1.left, rect1.top,
                width, height, TRUE) ;
}

void move_child_a2b_bottom(HWND a, HWND b, int offset)
{
    HWND p=GetParent(a);
    RECT rect0, rect1, rect2;
    int width = win_width(a);
    int height = win_height(a);
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(a, &rect1);
    GetWindowRect(b, &rect2);
    rect1.top = rect2.bottom+offset;
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(a, 	rect1.left, rect1.top,
                width, height, TRUE) ;
}

void child_a2b_xalign(HWND a, HWND b)
{
    HWND p=GetParent(a);
    RECT rect0, rect1, rect2;
    int width = win_width(a);
    int height = win_height(a);
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(a, &rect1);
    GetWindowRect(b, &rect2);
    rect1.left = rect2.left;
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(a, 	rect1.left, rect1.top,
                width, height, TRUE) ;
}

void child_a2b_yalign(HWND a, HWND b)
{
    HWND p=GetParent(a);
    RECT rect0, rect1, rect2;
    int width = win_width(a);
    int height = win_height(a);
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(a, &rect1);
    GetWindowRect(b, &rect2);
    rect1.top = rect2.top;
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(a, 	rect1.left, rect1.top,
                width, height, TRUE) ;
}

void child_a2b_balign(HWND a, HWND b)
{
    HWND p=GetParent(a);
    RECT rect0, rect1, rect2;
    int width = win_width(a);
    int height = win_height(a);
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(a, &rect1);
    GetWindowRect(b, &rect2);
    rect1.top += rect2.bottom-rect1.bottom;
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(a, 	rect1.left, rect1.top,
                width, height, TRUE) ;
}

void child_a2b_ralign(HWND a, HWND b)
{
    HWND p=GetParent(a);
    RECT rect0, rect1, rect2;
    int width = win_width(a);
    int height = win_height(a);
    get_client_rect_scrn(p, &rect0);
    GetWindowRect(a, &rect1);
    GetWindowRect(b, &rect2);
    rect1.left = rect2.right - width;
    get_relative_pos(&rect0, &rect1, &rect1);
    MoveWindow	(a, 	rect1.left, rect1.top,
                width, height, TRUE) ;
}

void move_child_a2b_bottom_left(HWND a, HWND b, int offset)
{
    move_child_a2b_bottom(a, b, offset);
    child_a2b_xalign(a, b);
}

void move_child_a2b_bottom_right(HWND a, HWND b, int offset)
{
    move_child_a2b_bottom(a, b, offset);
    child_a2b_ralign(a, b);
}

void move_child_a2b_right_top(HWND a, HWND b, int offset)
{
    move_child_a2b_right(a, b, offset);
    child_a2b_yalign(a, b);
}

void move_child_a2b_right_bottom(HWND a, HWND b, int offset)
{
    move_child_a2b_right(a, b, offset);
    child_a2b_balign(a, b);
}

void move_child_a2b_left_top(HWND a, HWND b, int offset)
{
    move_child_a2b_left(a, b, offset);
    child_a2b_yalign(a, b);
}

void right_include_child(HWND child, int offset)
{
    HWND p=GetParent(child);
    HWND pp=GetParent(p);
    RECT rect0, rect1, rect2;
    GetWindowRect(child, &rect0);
    GetWindowRect(p, &rect1);
    get_client_rect_scrn(pp, &rect2);
    rect1.right = rect0.right + offset;
    get_relative_pos(&rect2, &rect1, &rect1);
    MoveWindow	(p, 	rect1.left, rect1.top,
                rect1.right-rect1.left, rect1.bottom-rect1.top, TRUE) ;
}

void bottom_include_child(HWND child, int offset)
{
    HWND p=GetParent(child);
    HWND pp=GetParent(p);
    RECT rect0, rect1, rect2;
    GetWindowRect(child, &rect0);
    GetWindowRect(p, &rect1);
    get_client_rect_scrn(pp, &rect2);
    rect1.bottom = rect0.bottom + offset;
    get_relative_pos(&rect2, &rect1, &rect1);
    MoveWindow	(p, 	rect1.left, rect1.top,
                rect1.right-rect1.left, rect1.bottom-rect1.top, TRUE) ;
}

void h_arrange_win(HWND hleader, int nr_member, HWND hmembers[], int offset)
{
    int i;
    HWND a, b=hleader;
    for (i=0; i<nr_member; i++)
    {
        a=hmembers[i];
        move_child_a2b_right_top(a,b,10);
        b=a;
    }
}

void h_arrange_win_id(HWND hleader, int nr_member, int hmember_ids[], int offset)
{
    int i;
    HWND p=GetParent(hleader);
    HWND hmembers[nr_member];
    for (i=0;i<nr_member; i++)
    {
        hmembers[i]=GetDlgItem(p, hmember_ids[i]);
    }
    h_arrange_win(hleader, nr_member, hmembers, offset);
}

void v_arrange_win(HWND hleader, int nr_member, HWND hmembers[], int offset)
{
    int i;
    HWND a, b=hleader;
    for (i=0; i<nr_member; i++)
    {
        a=hmembers[i];
        move_child_a2b_bottom_left(a,b,10);
        b=a;
    }
}

void v_arrange_win_id(HWND hleader, int nr_member, int hmember_ids[], int offset)
{
    int i;
    HWND p=GetParent(hleader);
    HWND hmembers[nr_member];
    for (i=0;i<nr_member; i++)
    {
        hmembers[i]=GetDlgItem(p, hmember_ids[i]);
    }
    v_arrange_win(hleader, nr_member, hmembers, offset);
}

int a_include_b_right(HWND a, HWND b)
{
    RECT rect1, rect2;
    GetWindowRect(a, &rect1);
    GetWindowRect(b, &rect2);
    return rect1.right > rect2.right;
}

void add_tip(HWND htip_control, HWND hwnd, TCHAR *tips)
{
    TOOLINFO        ti;

    ti.cbSize = sizeof(TOOLINFO);
    //Flags TTF_IDISHWND show that the uID is the handle to control
    ti.uFlags =  TTF_IDISHWND | TTF_SUBCLASS;  

    //Handle of the Control for which you want to Tooltip to be displayed
    ti.uId    =(UINT)hwnd;

    //Handle of the parent window (The window in which the Control resides)
    ti.hwnd   = hwnd;
    ti.hinst  = g_hInstance;
    ti.lpszText  = tips;         //Text you want as a Tooltip
    	//Below is the Rectangle for ToolTip. But It will be ignored 
    	//If you use TTF_IDISHWND in Flag
    //ti.rect.left = ti.rect.top = ti.rect.bottom = ti.rect.right = 0; 

    //Will Activate the tooltip window
    SendMessage(htip_control,TTM_ACTIVATE,TRUE,0);  

    //will Add the Tooltip Window
    SendMessage(htip_control,TTM_ADDTOOL,0,(LPARAM)&ti);
}




