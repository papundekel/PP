cmake_minimum_required (VERSION 3.8)

file(GLOB TYPE_SOURCES *.cpp)

add_library(type ${TYPE_SOURCES})
