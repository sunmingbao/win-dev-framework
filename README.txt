
		win-dev-framework简介
		
======================

    win-dev-framework是一个windows程序开发框架，基于C语言和mingw工具链。 
    
    win-dev-framework内含如下内容：
        一份简单的源码目录结构
        win32程序基础代码
        一些常用例程
        makefile编译脚本
        NSIS打包脚本
        
    用户可以以此为基础，快速开始自己的windows程序开发。

    本软件是一款开源、免费软件。
    具体版权说明见COPYING.txt。
    本软件的下载地址：https://sourceforge.net/projects/windevframework/files/v1.x/

    本软件的编译方法见Build.txt。

本软件的目录结构大致如下：

|
|-- makefile
|
|-- package.nsi
|
|-- inc
|   |-- *.h
|
|-- src
|   |-- *.c
|
|-- res
|   |-- 资源文件


各目录项的用途如下：
inc         目录中存放.h文件。
src         目录中存放.c文件。
res         目录中存放资源文件。
makefile    对源码进行编译。
package.nsi 对程序进行打包，即生成安装包。

======================
作者: 孙明保
邮箱: sunmingbao@126.com
