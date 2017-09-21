cmake_minimum_required(VERSION 2.8.0)

set (PROJECT AudioTest)

# CMAKE_SYSTEM_NAME can be:
#   Linux
#   Linux_armhf
# Default: Linux

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_CXX_COMPILER   $ENV{CMAKE_CXX_COMPILER})
  set(CMAKE_C_COMPILER     $ENV{CMAKE_C_COMPILER})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux_armhf")
  set(CMAKE_CXX_COMPILER   "arm-linux-gnueabihf-g++")
  set(CMAKE_C_COMPILER     "arm-linux-gnueabihf-gcc")
else()
  # TODO
endif()

set(CMAKE_CXX_FLAGS_RELEASE " -DNDEBUG -s -O2")
set(CMAKE_CXX_FLAGS_DEBUG   " -DDEBUG -g3 -ggdb3")

add_subdirectory(./src)

#add_subdirectory(./test)
