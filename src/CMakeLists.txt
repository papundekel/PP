cmake_minimum_required (VERSION 3.8)

add_subdirectory("algorithm")
add_subdirectory("data")
add_subdirectory("io")
add_subdirectory("math")
add_subdirectory("odd")
add_subdirectory("trait")
add_subdirectory("type")
add_subdirectory("utility")

file(GLOB MAIN_SOURCES *.cpp)

add_executable(src ${MAIN_SOURCES})
