cmake_minimum_required (VERSION 3.8)

file(GLOB IO_SOURCES *.cpp)

add_library(io ${IO_SOURCES})
