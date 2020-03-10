cmake_minimum_required (VERSION 3.8)

file(GLOB TYPE_SOURCES *.cpp)

list(LENGTH TYPE_SOURCES len)

if (NOT len EQUAL 0)
	add_executable(type ${ALGORITHM_SOURCES})
endif()
