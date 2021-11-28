cmake_minimum_required(VERSION 3.20)

project(PP VERSION "0.1.3")

file(DOWNLOAD "https://raw.githubusercontent.com/Petkr/PPcmake/main/PPcmake.cmake" "${CMAKE_BINARY_DIR}/PPcmake.cmake")
include("${CMAKE_BINARY_DIR}/PPcmake.cmake")
include(CTest)

PPcmake_package("github.com" "Petkr" "PPcmake" "1.0.1")
include(PPcmake)

PPcmake_package("github.com" "Petkr" "PPstyle" "1.0.12")
include(PPstyle)

PPcmake_package("github.com" "Petkr" "PPtest" "1.0.2")
include(PPtest)

PPcmake_add_subdirectory(PP)
PPcmake_add_subdirectory(tests)
PPcmake_add_subdirectory(devel)

PPcmake_cpack()
