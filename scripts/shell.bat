@echo off

rem Getting access to the compiler
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

rem Adding our things to the path
set path=W:\kongfig\bin\4coder;W:\kongfig\bin;W:\kongfig\scripts;W:\apps\4coder;%path%