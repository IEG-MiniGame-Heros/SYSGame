@ECHO OFF
:: 获取当前批处理程序所在位置
cd /d %~dp0
set path=%cd%

:: 执行sqlite命令
%path%\sqlite3.exe database.db < sqlite.txt