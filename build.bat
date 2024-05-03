@echo off

mkdir build
cd build

set CMAKE_GENERATOR_OPTION="MinGW Makefiles"

rem 若未将cmake或mingw添加到环境变量
rem 则分别需要将MAKER改为cmake的路径,GENERATOR改为mingw下bin目录的路径
set MAKER=cmake
set GENERATOR=mingw32-make

echo =============start cmake=============
%MAKER% -G %CMAKE_GENERATOR_OPTION% ..
echo =============start %GENERATOR%=============
%GENERATOR%
echo =============complete==============

cd ..