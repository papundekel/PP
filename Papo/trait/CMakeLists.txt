cmake_minimum_required (VERSION 3.8)

file(GLOB TRAIT_SOURCES *.cpp)

add_library(trait ${TRAIT_SOURCES})
