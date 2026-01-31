::@echo off
:: > Setup required Environment
:: -------------------------------------
set COMPILER_DIR=C:\raylib\w64devkit\bin
set PATH=%PATH%;%COMPILER_DIR%
cd %~dp0
:: .
:: > Compile simple .rc file
:: ----------------------------
cmd /c windres ..\..\src\cool_project.rc -o ..\..\src\cool_project.rc.data
:: .
:: > Generating project
:: --------------------------
cmd /c mingw32-make -C ..\..\src ^
PROJECT_NAME=cool_project ^
PROJECT_VERSION=1.0 ^
PROJECT_DESCRIPTION="my cool new project" ^
PROJECT_INTERNAL_NAME=cool_project ^
PROJECT_PLATFORM=PLATFORM_DESKTOP ^
PROJECT_SOURCE_FILES="cool_project.c" ^
BUILD_MODE="RELEASE" ^
BUILD_WEB_ASYNCIFY=FALSE ^
BUILD_WEB_MIN_SHELL=TRUE ^
BUILD_WEB_HEAP_SIZE=268435456 ^
RAYLIB_MODULE_AUDIO=TRUE ^
RAYLIB_MODULE_MODELS=TRUE
