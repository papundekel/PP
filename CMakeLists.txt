cmake_minimum_required (VERSION 3.20)

if(CMAKE_COMPILER_IS_GNUCXX)
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-Werror
)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/PPstyle")

include(PPstyle)

project(PP)

add_subdirectory(PP)
add_subdirectory(test)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/devel/")
	add_subdirectory(devel)
endif()
