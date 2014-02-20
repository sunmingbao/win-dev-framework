@echo off
set rule_file=c:\rules.txt
/* 生成makefile规则 */
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

