cmake_minimum_required(VERSION 3.15)

set(output_Name NoitaArchiveManager)

project(Noita_Archive_Manager)

#设置静态编译
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")


set (CMAKE_CXX_STANDARD 17)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_LIST)


add_executable(${output_Name} ${SRC_LIST})

#链接静态库
#链接boost静态库(project_Name为你的项目名，*分别代表库名、mingw版本号、boost库版本号，如：libboost_system-mgw72-mt-s-1_65_1.a)
# target_link_libraries(${output_Name} libboost_*-mgw*-mt-s-*.a)
#链接gcc-g++静态库
target_link_libraries(${output_Name} libgcc.a)
target_link_libraries(${output_Name} libstdc++.a)
#链接网络库（如需要）
# target_link_libraries(project_Name ws2_32)
#链接线程库（必须放到最后）
target_link_libraries(${output_Name} libpthread.a)