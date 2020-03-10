cmake_minimum_required (VERSION 3.8)

file(GLOB TRAIT_SOURCES *.cpp)

list(LENGTH TRAIT_SOURCES len)

if (NOT len EQUAL 0)
	add_executable(trait ${ALGORITHM_SOURCES})
endif()
