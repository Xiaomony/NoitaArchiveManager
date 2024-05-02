@echo off

mkdir build
cd build

set CMAKE_GENERATOR_OPTION="MinGW Makefiles"
set GENERATOR=mingw32-make

echo =============start cmake=============
cmake -G %CMAKE_GENERATOR_OPTION% ..
echo =============start %GENERATOR%=============
%GENERATOR%
echo =============complete==============

cd ..