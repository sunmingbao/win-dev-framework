@echo off
dir src /B > obj\src_1.txt

::tools\str_replace.bat  obj\src_1.txt obj\src_4.txt .c

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

