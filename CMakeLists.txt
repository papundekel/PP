cmake_minimum_required(VERSION 3.20)

if(CMAKE_COMPILER_IS_GNUCXX)
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-Werror
)
endif()

project(PP VERSION "0.1.1")

include(GNUInstallDirs)
include(CTest)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/vendor/${CMAKE_INSTALL_DATADIR}/cmake")

file(DOWNLOAD "https://github.com/Petkr/PPstyle/releases/download/1.0.11/PPstyle-1.0.11-Linux.tar.gz" "PPstyle.tar.gz")
file(DOWNLOAD "https://github.com/Petkr/PPtest/releases/download/1.0.2/PPtest-1.0.2-Linux.tar.gz"     "PPtest.tar.gz")
file(ARCHIVE_EXTRACT INPUT "PPstyle.tar.gz" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/vendor")
file(ARCHIVE_EXTRACT INPUT "PPtest.tar.gz"  DESTINATION "${CMAKE_CURRENT_LIST_DIR}/vendor")
file(REMOVE "PPstyle.tar.gz" "PPtest.tar.gz")

include(PPstyle)
include(PPtest)

add_subdirectory(PP)
add_subdirectory(tests)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/devel/")
	add_subdirectory(devel)
endif()

set(CPACK_GENERATOR "TGZ")
include(CPack)
