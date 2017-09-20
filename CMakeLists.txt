cmake_minimum_required(VERSION 2.8.0)

set (PROJECT AudioTest)

set(CMAKE_CXX_COMPILER   $ENV{CMAKE_CXX_COMPILER})
set(CMAKE_C_COMPILER     $ENV{CMAKE_C_COMPILER})

set(CMAKE_CXX_FLAGS_RELEASE " -DNDEBUG -s -O2")
set(CMAKE_CXX_FLAGS_DEBUG   " -DDEBUG -g3 -ggdb3")

add_subdirectory(./src)

add_subdirectory(./test)
