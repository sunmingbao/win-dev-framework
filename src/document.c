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


int doc_modified;

char doc_data[64];

void save_doc_file(TCHAR *file_name)
{
    FILE *file=fopen(file_name, "wb");
    fwrite(doc_data, sizeof(doc_data), 1, file);
    fclose(file);
}

void load_doc_file(TCHAR *file_name)
{
    FILE *file=fopen(file_name, "rb");
    fread(doc_data, sizeof(doc_data), 1, file);
    fclose(file);
}

