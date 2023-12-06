cmake_minimum_required(VERSION 3.26)
project(logistics_management_system)

set(CMAKE_C_STANDARD 17)

add_executable(logistics_management_system server.c
        item.c
        item.h
        repository.h
        repository.c
        server.h
        globalDeclarations.h)