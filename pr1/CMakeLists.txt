cmake_minimum_required(VERSION 3.10)

project(Lab1_3)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")

#Finding all libs
#System process1
find_library(LIB_PROCESS1 process1 PATHS /usr/lib)
#Home process
find_library(LIB_PROCESS process PATHS $ENV{HOME}/mylibs)

add_executable(my_program main.c input.c output.c)
#Connecting libs to prog
target_link_libraries(my_program ${LIB_PROCESS1} ${LIB_PROCESS})
