@ECHO OFF
:: ��ȡ��ǰ�������������λ��
cd /d %~dp0
set path=%cd%

:: ִ��sqlite����
%path%\sqlite3.exe database.db < sqlite.txt