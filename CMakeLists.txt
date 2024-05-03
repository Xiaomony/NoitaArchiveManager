cmake_minimum_required(VERSION 3.15)
project(Noita_Archive_Manager)

set (CMAKE_CXX_STANDARD 17)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_LIST)


add_executable(NoitaArchiveManager ${SRC_LIST})
