:: 
:: 本软件为免费、开源软件。
:: 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
:: 您可以自由使用、传播本软件。
:: 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
:: =====================
:: 作者: 孙明保
:: 邮箱: sunmingbao@126.com
::

@echo off
dir src /B > obj\src_1.txt

if not exist obj\src_2.txt goto BEGIN_OUTPUT

del obj\src_2.txt

:BEGIN_OUTPUT
setlocal enabledelayedexpansion
for /f "tokens=*" %%i in (obj/src_1.txt) do (
set var=%%i
set "var=!var:.c=!"
echo !var!>>obj/src_2.txt
)

if not exist obj\dest.txt goto BEGIN_OUTPUT2

del obj\dest.txt

:BEGIN_OUTPUT2

for /f "delims=" %%i in (obj\src_2.txt) do >>obj\dest.txt set/p=%%i <nul

type obj\dest.txt

