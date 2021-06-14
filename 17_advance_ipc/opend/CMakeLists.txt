cmake_minimum_required(VERSION 3.12)

#获取项目目录名称
get_filename_component(ProjectId . NAME)

message(${ProjectId})

project(${ProjectId} C)

set(CMAKE_C_STANDARD 99)

include_directories(../../include)
include_directories(.)

#添加到可执行文件中
add_executable(server server.c ../../include/error.c
        ../../lib/spipe.c ../../lib/servlisten.c
        ../../lib/servaccept.c ../../lib/cliconn.c
        ../../lib/recvfd.c ../../lib/sendfd.c
        ../../lib/senderr.c
        # ./loop.poll.c
        ./loop.select.c ./request.c
        ./cliargs.c ./client.c
        ../../lib/errorlog.c ../../lib/writen.c
        ../../lib/daemonize.c ../../lib/bufargs.c
        )