@echo off
rem  ===== Date Created: 14 July, 2020 ===== 

set depLibs=sfml-graphics-s.lib sfml-window-s.lib sfml-system-s.lib opengl32.lib winmm.lib user32.lib freetype.lib advapi32.lib gdi32.lib

set compilerFlags=/nologo /std:c++17 /DSFML_STATIC /Fe:CLogButBetter.exe /MTd /GR- /Gm- /EHsc /Od /Oi /FC /Zi /WX /W4 /wd4100 /I..\src\ /I..\deps\include\
set linkerFlags=/opt:ref /SUBSYSTEM:console /IGNORE:4204 /LIBPATH:..\deps\lib\Debug %depLibs%

set files=..\src\*.cpp

WHERE cl.exe >nul 2>nul
IF %ERRORLEVEL% NEQ 0 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

IF NOT EXIST bin\ mkdir bin
pushd bin

cl %compilerFlags% %files% /link %linkerFlags%

popd
IF %ERRORLEVEL% NEQ 0 (
	EXIT /B %ERRORLEVEL%
) ELSE (
	run.bat
)
