cmake_minimum_required(VERSION 3.12)

#获取项目目录名称
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)

message(${ProjectId})

project(${ProjectId} C)

set(CMAKE_C_STANDARD 99)

include_directories(../include)

#把所有c文件添加到files
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

foreach(file ${files})
    get_filename_component(name ${file} NAME)
    string(REPLACE ".c" "" name ${name})
    #添加到可执行文件中
    add_executable(${name} ${file} ../include/error.c)
endforeach()