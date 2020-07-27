::  Initial Developer's Public License.
::  The contents of this file are subject to the  Initial Developer's Public
::  License Version 1.0 (the "License"). You may not use this file except
::  in compliance with the License. You may obtain a copy of the License at
::    http://www.ibphoenix.com?a=ibphoenix&page=ibp_idpl
::  Software distributed under the License is distributed on an "AS IS" basis,
::  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
::  for the specific language governing rights and limitations under the
::  License.
::
::  The Original Code is copyright 2004 Paul Reeves.
::
::  The Initial Developer of the Original Code is Paul Reeves
::
::  All Rights Reserved.
::
::=============================================================================
::
:: Take a build and package it.
::
@echo off


:SET_ENVIRONMENT
::==============
setlocal
set ROOT_PATH=..\..
for /F "tokens=2*" %%a in ('findstr /C:\^#define %ROOT_PATH%\Version.h') do SET ODBC_%%a=%%~b
set PRODUCT_VER_STRING=%ODBC_MAJOR_VERSION%.%ODBC_MINOR_VERSION%.%ODBC_REVNO_VERSION%-%ODBC_BUILDTYPE_VERSION%

:BUILD_HELP
::=========
if exist "%ProgramFiles%\HTML Help Workshop\hhc.exe" (
set HTMLHELP="%ProgramFiles%\HTML Help Workshop\hhc.exe"
) else (
  if exist "%ProgramFiles(x86)%\HTML Help Workshop\hhc.exe" (
	set HTMLHELP="%ProgramFiles(x86)%\HTML Help Workshop\hhc.exe"
  ) else (
  echo HTML Help Workshop is not available
  goto :EOF
  )
)
%HTMLHELP% %ROOT_PATH%\Install\HtmlHelp\OdbcJdbc.hhp
if not ERRORLEVEL 1 echo Help build error & goto :EOF

:ZIP
::========
del /q %ROOT_PATH%\Builds\output\OdbcFb-%PRODUCT_VER_STRING%* >nul
%SEVENZIP%7z -bso0 a %ROOT_PATH%\Builds\output\OdbcFb-%PRODUCT_VER_STRING%-Win32.7z %ROOT_PATH%\Builds\output\OdbcFb.chm %ROOT_PATH%\Builds\output\Win32\Release\OdbcFb.dll || goto :ERR
%SEVENZIP%7z -bso0 a %ROOT_PATH%\Builds\output\OdbcFb-%PRODUCT_VER_STRING%-Win64.7z %ROOT_PATH%\Builds\output\OdbcFb.chm %ROOT_PATH%\Builds\output\Win64\Release\OdbcFb.dll || goto :ERR

:ISX
::========
if defined INNO6_SETUP_PATH (
  set ISCC_COMMAND=%INNO6_SETUP_PATH%\iscc.exe
)
if not defined ISCC_COMMAND (
if defined INNO5_SETUP_PATH (
  set ISCC_COMMAND=%INNO5_SETUP_PATH%\iscc.exe
)
)
:: If the environment variable is not set let's search in PATH
if not defined ISCC_COMMAND (
  @for /f "usebackq tokens=*" %%c in (`where /f iscc 2^>nul`) do set ISCC_COMMAND=%%c
)
if not defined ISCC_COMMAND (
  @echo  Required Inno Setup compiler not found
  @exit /b 1
)
@Echo Now let's compile the InnoSetup scripts
@Echo.
call %ISCC_COMMAND% "%ROOT_PATH%\Install\Win32\OdbcJdbcSetup.iss" || goto :ERR
goto :EOF

:ERR
::=======
@echo Some error happen during build, inspect messages above
