;
;     The contents of this file are subject to the Initial
;     Developer's Public License Version 1.0 (the "License");
;     you may not use this file except in compliance with the
;     License. You may obtain a copy of the License at
;        http://www.ibphoenix.com?a=ibphoenix&page=ibp_idpl
;
;     Software distributed under the License is distributed on
;     an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either
;     express or implied.  See the License for the specific
;     language governing rights and limitations under the License.
;
;
;  The Original Code was created by Vladimir Tsvigun for IBPhoenix.
;  Updated and extended by Paul Reeves for v1.2 release.
;
;
;  Copyright (c) 2003 Vladimir Tsvigun
;  Portions Copyright (c) 2004 Paul Reeves
;  All Rights Reserved.
;
;
;
;  OdbcJdbcSetup.iss
;
;  Currently compiled against InnoSetup v5.3 from http://www.innosetup.com/
;
;

#define FIREBIRD_URL "http://www.firebirdsql.org"
#define BUILD_ROOT "..\..\"
#define SOURCE_DOCS "Install"
#define SOURCE_LIBS "Builds\output"
#include BUILD_ROOT + "Version.h"
#define ProductVersion Str(MAJOR_VERSION) + "." + Str(MINOR_VERSION) + "." + Str(REVNO_VERSION)
#define FileVersion GetFileVersion(BUILD_ROOT + "Builds\output\Win64\Release\OdbcFb.dll")
#if FileVersion != GetFileVersion(BUILD_ROOT + "Builds\output\Win32\Release\OdbcFb.dll")
#error "Versions of libraries don't match"
#endif

[Setup]
AppName=Firebird ODBC Driver
AppVerName=Firebird ODBC driver {#ProductVersion} (SD edition)
AppVersion={#ProductVersion}
AppMutex=InnoSetupExtensionsCompilerAppMutex
AppPublisher=SD
DefaultDirName={commonappdata}\OdbcFb
DisableDirPage=true

UninstallDisplayIcon={sys}\OdbcFb.dll

PrivilegesRequired=admin

SourceDir={#BUILD_ROOT}
OutputDir=Builds\output
OutputBaseFilename=OdbcFb-{#ProductVersion}-{#BUILDTYPE_VERSION}
VersionInfoVersion={#FileVersion}

LicenseFile={#SOURCE_DOCS}\IDPLicense.txt
DisableReadyPage=yes
Compression=lzma
SolidCompression=true

WizardImageFile={#SOURCE_DOCS}\Win32\firebird-logo1.bmp
WizardSmallImageFile={#SOURCE_DOCS}\Win32\firebird-logo2.bmp

[Languages]
Name: en; MessagesFile: compiler:Default.isl
Name: ru; MessagesFile: compiler:Default.isl,compiler:Languages\Russian.isl


[Files]
Source: {#SOURCE_LIBS}\Win32\Release\OdbcFb.dll; DestDir: {sys}; Flags: 32bit regserver restartreplace
Source: {#SOURCE_LIBS}\Win64\Release\OdbcFb.dll; DestDir: {sys}; Flags: 64bit regserver restartreplace; Check: IsWin64
Source: {#SOURCE_LIBS}\OdbcFb.chm; DestDir: {app}
Source: {#SOURCE_DOCS}\Win32\Readme.txt; DestDir: {app}; Flags: isreadme
Source: {#SOURCE_DOCS}\IDPLicense.txt; DestDir: {app};

[CustomMessages]
en.DeveloperInstall=Developer install - register driver in System Dir. Install documentation to program group.
en.DeploymentInstall=Deployment install - no docs, no menus, no icons.
en.DocumentationInstall=Install documentation only.
en.DeveloperComponent=Install driver to
en.DeploymentComponent=Install driver only. No docs, uninstall.
en.DocumentationComponent=Documentation in CHM and HTML format

ru.DeveloperInstall=Полная установка - драйвер в системную папку, документацию в группу программ.
ru.DeploymentInstall=Только драйвер - никаких документов, меню, иконок.
ru.DocumentationInstall=Только документацию.
ru.DeveloperComponent=Установка драйвера в
ru.DeploymentComponent=Установка только драйвера, без документации и деинсталяции.
ru.DocumentationComponent=Документация в формате CHM и HTML
