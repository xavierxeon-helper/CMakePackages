@echo off
setlocal

echo Setting up environment for Qt usage...
set PATH=C:\dev\Qt\Tools\CMake_64\bin;C:\dev\Qt\Tools\mingw1310_64\bin;%QT_DIR%\mingw_64\bin;%PATH%

set THIS_DIR=%~dp0

mkdir %THIS_DIR%build\cmd_line_release
cd %THIS_DIR%build\cmd_line_release
cmake %THIS_DIR%  -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
cmake --build . --parallel --config Release
if %errorlevel% NEQ 0 goto :FAIL

mkdir %THIS_DIR%build\cmd_line_debug
cd %THIS_DIR%build\cmd_line_debug
cmake %THIS_DIR%  -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles"
cmake --build . --parallel --config Debug
if %errorlevel% EQU 0 goto :END

:FAIL
echo An error occurred when building

:END
cd %THIS_DIR%
pause
