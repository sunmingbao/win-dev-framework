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
#include <stdio.h>

#include "defs.h"

int WinPrintf(HWND hwnd, TCHAR * szFormat, ...)
{
	TCHAR   szBuffer [1024] ;
	va_list pArgList ;

	// The va_start macro (defined in STDARG.H) is usually equivalent to:
	// pArgList = (char *) &szFormat + sizeof (szFormat) ;

	va_start (pArgList, szFormat) ;

	// The last argument to wvsprintf points to the arguments

	_vsntprintf (	szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
			szFormat, pArgList) ;

	// The va_end macro just zeroes out pArgList for no good reason
	va_end (pArgList) ;
	return MessageBox (hwnd, szBuffer, TEXT("错误"), 0) ;
}

int get_save_file_name(char *file_name, HWND hwnd, char *filter, char *ext)
{
    TCHAR szFile[MAX_FILE_PATH_LEN]=TEXT("");
    OPENFILENAME  Ofn;
    
    memset(&Ofn, 0, sizeof(OPENFILENAME));
    Ofn.lStructSize = sizeof(OPENFILENAME); 
    Ofn.hwndOwner = hwnd; 
    
    Ofn.lpstrFilter = filter;
    Ofn.nFilterIndex = 2;
    Ofn.lpstrDefExt = ext;

    Ofn.lpstrFile= szFile; 
    Ofn.nMaxFile = MAX_FILE_PATH_LEN; 
    Ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT; 
    Ofn.lpstrTitle = "save to"; 
 

    if (GetSaveFileName(&Ofn)) 
    {
        strcpy(file_name, Ofn.lpstrFile);
        return 0;
    }

    return 1;


}


int get_open_file_name(char *file_name, HWND hwnd, char *filter_str)
{
    OPENFILENAME ofn;       // common dialog box structure
    TCHAR szFile[MAX_FILE_PATH_LEN]=TEXT("");       // buffer for file name

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.nMaxFile = MAX_FILE_PATH_LEN;
    ofn.lpstrFilter = filter_str;
    ofn.nFilterIndex = 2;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box. 

    if (GetOpenFileName(&ofn)) 
    {
        strcpy(file_name, ofn.lpstrFile);
        return 0;
    }
    
    return 1;

}

int GetIndex(HWND hList)
{
  int i, n;
  n = ListView_GetItemCount(hList);
  for (i = 0; i < n; i++)
    if (ListView_GetItemState(hList, i, LVIS_FOCUSED) == LVIS_FOCUSED)
      return i;

    return -1;
} 

int DelSel(HWND hList)
{
  int i, n;
  n = ListView_GetItemCount(hList);
  for (i = 0; i < n; i++)
    {
        if (ListView_GetCheckState(hList, i))
        {
          ListView_DeleteItem(hList, i);
          i--;
          n--;
        }
    }

  return 0;

} 

int SelAll(HWND hList)
{
  int i, n;
  n = ListView_GetItemCount(hList);
  for (i = 0; i < n; i++)
    {
        if (!ListView_GetCheckState(hList, i))
        {
          ListView_SetCheckState(hList, i, 1);
        }
    }

  return 0;

} 

int SelRvs(HWND hList)
{
  int i, n;
  n = ListView_GetItemCount(hList);
  for (i = 0; i < n; i++)
    {
        if (!ListView_GetCheckState(hList, i))
        {
          ListView_SetCheckState(hList, i, 1);
        }
        else
        {
          ListView_SetCheckState(hList, i, 0);
        }
    }

  return 0;

} 

int GetSelCnt(HWND hList)
{
  int i, n, cnt=0;
  n = ListView_GetItemCount(hList);
  for (i = 0; i < n; i++)
    {
        if (ListView_GetCheckState(hList, i))
        {
          cnt++;
        }
    }

  return cnt;

} 

void delete_file_f(char *file_path)
{
    SetFileAttributes(file_path,FILE_ATTRIBUTE_NORMAL);
    DeleteFile(file_path);
}

int file_exists(char *file_path)
{
    FILE *file=fopen(file_path, "r");
    if (NULL!=file)
    {
        fclose(file);
        return 1;
    }

    return 0;

}

int save_file_path_valid(char *file_path)
{
    FILE *file;
    if (file_exists(file_path))
    {
        return 1;
    }

    file=fopen(file_path, "w");
    if (NULL!=file)
    {
        fclose(file);
        delete_file_f(file_path);
        return 1;
    }

    return 0;
}


void set_int_text(HWND hwnd, int value)
{
    char info[32];
    sprintf(info, "%d", value);
    SetWindowText(hwnd, info);
}

int get_int_text(HWND hwnd)
{
    char info[32];
    GetWindowText(hwnd, info, sizeof(info));
    return strtol(info+0,NULL,10);
}

void inc_int_text(HWND hwnd, int value)
{
    set_int_text(hwnd, get_int_text(hwnd) + value);
}

void clear_comb(HWND hwndCtl)
{
    while(ComboBox_GetCount(hwndCtl)>0)
    {
        ComboBox_DeleteString(hwndCtl, 0);
    }
}

int str2int(char *info)
{
    if (strchr(info, 'x') || strchr(info, 'X'))
        return strtol(info+0,NULL,16);
    else        
        return strtol(info+0,NULL,10);
}

void center_child_win(HWND hwndParent, HWND hwndWindow)
{
     RECT rectWindow, rectParent;

         int nWidth ;
         int nHeight;
 
         int nX;
         int nY;
 
         int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
         int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

     // make the window relative to its parent
     if ((hwndParent = GetParent(hwndWindow)) != NULL)
     {
         GetWindowRect(hwndWindow, &rectWindow);
         GetWindowRect(hwndParent, &rectParent);
 
         nWidth = rectWindow.right - rectWindow.left;
         nHeight = rectWindow.bottom - rectWindow.top;
 
         nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
         nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;
 
 
         // make sure that the dialog box never moves outside of the screen
         if (nX < 0) nX = 0;
         if (nY < 0) nY = 0;
         if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
         if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;
 
         MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);
 
     }
 
}


