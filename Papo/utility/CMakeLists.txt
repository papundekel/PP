cmake_minimum_required (VERSION 3.8)

file(GLOB UTILITY_SOURCES *.cpp)

add_library(utility ${UTILITY_SOURCES})
