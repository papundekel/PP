cmake_minimum_required (VERSION 3.8)

file(GLOB ODD_SOURCES *.cpp)

add_library(odd ${ODD_SOURCES})
