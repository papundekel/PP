cmake_minimum_required (VERSION 3.8)

file(GLOB ODD_SOURCES *.cpp)

list(LENGTH ODD_SOURCES len)

if (NOT len EQUAL 0)
	add_executable(odd ${ALGORITHM_SOURCES})
endif()
