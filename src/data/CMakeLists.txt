cmake_minimum_required (VERSION 3.8)

file(GLOB DATA_SOURCES *.cpp)

add_executable(data ${DATA_SOURCES})
