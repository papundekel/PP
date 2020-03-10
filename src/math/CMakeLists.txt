cmake_minimum_required (VERSION 3.8)

file(GLOB MATH_SOURCES *.cpp)

add_executable(math ${MATH_SOURCES})
