cmake_minimum_required(VERSION 3.20)
project(cv LANGUAGES CXX)
set (VERSION_MAJOR 1)
set (VERSION_NINOR 2)

include(CheckFunctionExists)
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

add_executable(cv main.cpp)
target_link_libraries(cv -lpthread)

install (TARGETS cv DESTINATION bin)

message (STATUS "compiler C   = ${CMAKE_C_COMPILER} ${FULL_C_FLAGS}")
message (STATUS "compiler CXX = ${CMAKE_CXX_COMPILER} ${FULL_CXX_FLAGS}")
message (STATUS "LINKER_FLAGS = ${FULL_EXE_LINKER_FLAGS}")
