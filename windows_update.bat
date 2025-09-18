@echo off
setlocal

REM Finds the newest vcvars script https://github.com/microsoft/vswhere/wiki/Start-Developer-Command-Prompt
REM This is equivalent to running
REM call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
@if not defined _echo echo off
for /f "usebackq delims=" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -prerelease -latest -property installationPath`) do (
  if exist "%%i\Common7\Tools\vsdevcmd.bat" (
    call "%%i\VC\Auxiliary\Build\vcvars64.bat"
    goto :FOUND
  )
)

echo Instance or command prompt not found
goto :FAIL

:FOUND
set THIS_DIR=%~dp0

mkdir %THIS_DIR%build\cmd_line_release
cd %THIS_DIR%build\cmd_line_release
cmake %THIS_DIR%  -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel --config Release
if %errorlevel% NEQ 0 goto :FAIL

mkdir %THIS_DIR%build\cmd_line_debug
cd %THIS_DIR%build\cmd_line_debug
cmake %THIS_DIR%  -DCMAKE_BUILD_TYPE=Debug
cmake --build . --parallel --config Debug
if %errorlevel% EQU 0 goto :END

:FAIL
echo An error occurred when building

:END
cd %THIS_DIR%
pause
