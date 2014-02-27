/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */

#ifndef __UTILS_H_
#define __UTILS_H_

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


static inline void err_info_box(HWND hparent, TCHAR *info)
{
    MessageBox(hparent, info, szAppName, MB_ICONERROR);
}

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

int get_save_file_name(char *file_name, HWND hwnd, char *filter, char *ext);
int get_open_file_name(char *file_name, HWND hwnd, char *filter_str);

#endif

