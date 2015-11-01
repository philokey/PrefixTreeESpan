cmake_minimum_required(VERSION 3.3)
project(PrefixTreeESpan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES prefixTreeESpan.cpp prefixTreeESpan.h util.cpp util.h test.cpp test.h)
add_executable(PrefixTreeESpan ${SOURCE_FILES})