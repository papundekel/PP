cmake_minimum_required (VERSION 3.8)

file(GLOB ALGORITHM_SOURCES *.cpp)

list(LENGTH ALGORITHM_SOURCES len)

if (NOT len EQUAL 0)
	add_executable(algorithm ${ALGORITHM_SOURCES})
endif()