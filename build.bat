@echo off

mkdir build
cd build

set CMAKE_GENERATOR_OPTION="MinGW Makefiles"

rem ///////////////////////////
set MAKER=cmake
set GENERATOR=mingw32-make
rem //////////////////////////

echo =============start cmake=============
%MAKER% -G %CMAKE_GENERATOR_OPTION% ..
echo =============start %GENERATOR%=============
%GENERATOR%
echo =============complete==============

cd ..