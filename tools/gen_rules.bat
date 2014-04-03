:: 
:: 本软件为免费、开源软件。
:: 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
:: 您可以自由使用、传播本软件。
:: 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
:: =====================
:: 作者: 孙明保
:: 邮箱: sunmingbao@126.com
::


:: 生成makefile规则

@echo off
set rule_file=obj\rules.txt

echo #gen_rules > %rule_file%
for /f  "delims=  " %%i in (obj\src_2.txt) do (
echo %%i
echo #rule begin >>%rule_file%
>>%rule_file% set/p=${OBJ_DIR}\<nul
>>%rule_file% set/p=%%i<nul
>>%rule_file% set/p=.o : %%i<nul
echo .c>>%rule_file%
type tools\compile_cmd.txt >>%rule_file%
)


echo %rule_file%

