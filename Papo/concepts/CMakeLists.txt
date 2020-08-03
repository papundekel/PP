cmake_minimum_required (VERSION 3.8)

file(GLOB CONCEPTS_SOURCES *.cpp)

add_library(concepts ${CONCEPTS_SOURCES})
