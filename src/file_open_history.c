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
#include "utils.h"
#include "global_symbols.h"

#include "res.h"


#define    HISTORY_FILE_NAME    "history"
#define    HISTORY_FILE_NAME_TMP    "history.tmp"
int read_next_filed(FILE *the_file, char *field_name, char *field_value)
{
    char line[MAX_FILE_PATH_LEN + 32];
    char *sep, *tail;

    if (NULL==fgets(line, sizeof(line), the_file)) 
        return 1;

    if (strlen(line)<3) return 1;

    sep = strchr(line,'=');
    if (sep==NULL) return 1;

    *sep = 0;

    tail = sep + strlen(sep+1);
    while ((*tail == '\r') || (*tail == '\n')|| (*tail == ' '))
    {
        *tail=0;
        tail--;
    }
    
    if (field_name!=NULL)
        strcpy(field_name, line);

    if (field_value!=NULL)
        strcpy(field_value, sep+1);

    return 0;
}

int get_field_value_by_idx(char *file_path
                        ,int idx
                        ,char *field_value)
{
    FILE *history_file = fopen(file_path, "r");
    int i;
    int ret;
    
    if (history_file==NULL) return 1;
    
    for(i=0; i<=idx; i++)
    {
        ret=read_next_filed(history_file, NULL, field_value);
    }

    fclose(history_file);
    return ret;
}

int get_file_path_by_idx(char *file_path, int idx)
{
    return get_field_value_by_idx(HISTORY_FILE_NAME
                        ,idx+1
                        ,file_path);
}

int get_last_doc_file(char *file_path)
{
    return get_field_value_by_idx(HISTORY_FILE_NAME
                        ,1
                        ,file_path);
}

void populate_recent_files(HMENU	 hMenu)
{
    int i;
    int file_num;
    char field_value[MAX_FILE_PATH_LEN];
    char    menu_name[MAX_FILE_PATH_LEN + 8];
    FILE *history_file;
    

    for (i=0; i<MAX_RECENT_FILE_NUM; i++)
        DeleteMenu(hMenu, 0, MF_BYPOSITION);


    if (!file_exists(HISTORY_FILE_NAME))
    {
        //fclose(fopen(HISTORY_FILE_NAME, "w"));
        return;
    }

    history_file = fopen(HISTORY_FILE_NAME, "r");
    read_next_filed(history_file, NULL, field_value);
    file_num = atoi(field_value);

    for (i=0; i<file_num; i++)
    {
        read_next_filed(history_file, NULL, field_value);
        sprintf(menu_name, "&%d  %s", i, field_value);
        AppendMenu(hMenu, MF_STRING, ID_FILE_RECENT_FILE_BEGIN+i,  menu_name) ;
    }

    fclose(history_file);
}

void update_file_open_history(char *file_path)
{
    FILE *history_file_tmp = NULL;
    FILE *history_file = NULL;
    char field_value[MAX_FILE_PATH_LEN];
    char line[MAX_FILE_PATH_LEN+64];
    int len, i;
    int old_file_num, new_file_num = 1;

    history_file_tmp = fopen(HISTORY_FILE_NAME_TMP, "w");
    len=sprintf(field_value
        , "file_num=1  \n"
          "file_0=%s\n"
          , file_path);
    fwrite(field_value, 1, len, history_file_tmp);

    if (!file_exists(HISTORY_FILE_NAME))
    {
        goto EXIT;
    }

    history_file = fopen(HISTORY_FILE_NAME, "r");
    read_next_filed(history_file, NULL, field_value);
    old_file_num = atoi(field_value);

    for (i=0; i<old_file_num; i++)
    {

        read_next_filed(history_file, NULL, field_value);
        if (0==strcmp(field_value, file_path)) continue;
        len=sprintf(line, "file_%d=%s\n", new_file_num, field_value);
        fwrite(line, 1, len, history_file_tmp);
        new_file_num++;
        if (new_file_num>=MAX_RECENT_FILE_NUM) break;

    }

    fseek(history_file_tmp, 0, SEEK_SET);
    len=sprintf(line, "file_num=%d", new_file_num);
    fwrite(line, 1, len, history_file_tmp);

EXIT:
    fclose(history_file_tmp);
    if (history_file != NULL)
    {
        fclose(history_file);
        delete_file_f(HISTORY_FILE_NAME);
    }
    MoveFile(HISTORY_FILE_NAME_TMP, HISTORY_FILE_NAME);

    
}

