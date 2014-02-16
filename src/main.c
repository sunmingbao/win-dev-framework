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
#include "env.h"
#include "global_symbols.h"


HINSTANCE g_hInstance;
int       init_over;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
{
    MSG     msg ;
    HACCEL  hAccel ;

    g_hInstance = hInstance;

    env_init();

    register_frame();

    create_windows(iCmdShow);

 	hAccel = LoadAccelerators (hInstance, TEXT("MY_ACCELER")) ;

    /* 初始化完毕。*/
    init_over=1;

    /* 下面进入消息循环 */
    
 	while (GetMessage (&msg, NULL, 0, 0))
 	{
  		if (!TranslateAccelerator (hwnd_frame, hAccel, &msg))
		{
			TranslateMessage (&msg) ;
            
            /* 如果需要的话，这里可以修改个别消息的传递
            if (msg.message==WM_KEYDOWN && VK_RETURN==msg.wParam && msg.hwnd==hwnd_origin)
            {
                msg.hwnd = hwnd_new;
            }
            */
            
			DispatchMessage (&msg) ;
  		}
 	}

    return msg.wParam ;
}


