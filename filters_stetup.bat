@echo off
if not exist "%UserProfile%\AppData\Local\Atorio\" mkdir %UserProfile%\AppData\Local\Atorio\
if not exist "%UserProfile%\AppData\Local\Atorio\filters\" mkdir %UserProfile%\AppData\Local\Atorio\filters\
del /S /Q %UserProfile%\AppData\Local\Atorio\filters\*
for /f "tokens=*" %%G in ('dir /b /o:gn /a:d "%UserProfile%\AppData\Local\Atorio\filters\"') do if exist "%UserProfile%\AppData\Local\Atorio\filters\%%G" rmdir %UserProfile%\AppData\Local\Atorio\filters\%%G \S \Q
copy /b x64\Release\Atorio-Filters.dll %UserProfile%\AppData\Local\Atorio\filters\
for /f "tokens=*" %%G in ('dir /b /o:gn /a:d "x64\Release\"') do (
mkdir %UserProfile%\AppData\Local\Atorio\filters\%%G\
copy /b x64\Release\%%G\* %UserProfile%\AppData\Local\Atorio\filters\%%G\
)