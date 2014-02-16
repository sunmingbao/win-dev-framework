/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */

#ifndef __ENV_H_
#define __ENV_H_

extern int scrn_width;  /* 屏幕宽度 */
extern int scrn_height; /* 屏幕高度 */

extern int cxChar; /* SYSTEM_FIXED_FONT width */
extern int cyChar; /* SYSTEM_FIXED_FONT height */

void env_init();

#endif

