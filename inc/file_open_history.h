/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */

#ifndef __FILE_OPEN_HISTORY_H_
#define __FILE_OPEN_HISTORY_H_
#include <windows.h>
#include <tchar.h> 
#include <windowsx.h>

int get_last_doc_file(char *file_path);
void populate_recent_files(HMENU	 hMenu);
void update_file_open_history(char *file_path);
int get_file_path_by_idx(char *file_path, int idx);

#endif

