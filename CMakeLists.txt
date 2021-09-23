cmake_minimum_required(VERSION 3.21)

set(This CPP_Challenges)

project(${This} C CXX)

#set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)


enable_testing()

add_subdirectory(googletest)

#include_directories (pathh/inc/)
#link_directories(pathh/inc/)
#set(Headers
#    strc.h
#)

#add_library(strc STATIC pathh/strc.cpp)

add_subdirectory(Validate_IP_Address)
add_subdirectory(Threading)
