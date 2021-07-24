cmake_minimum_required (VERSION 3.8)

if(CMAKE_COMPILER_IS_GNUCXX)
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-Werror
)
endif()

project(PP)

add_subdirectory(PP)
add_subdirectory(PPdemo)
