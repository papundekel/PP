cmake_minimum_required(VERSION 3.20)

function(download_package _url)
    cmake_path(GET _url FILENAME _filename)

    file(DOWNLOAD "${URL}" "${_filename}")
    file(ARCHIVE_EXTRACT INPUT "${_filename}" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/vendor")
    file(REMOVE "${_filename}")
endfunction()

function(target_pedantic_errors _target)
	if(CMAKE_COMPILER_IS_GNUCXX)
		target_compile_options(${_target}
			PUBLIC -Wall -Wextra -pedantic -Werror
		)
	endif()
endfunction()

project(PP VERSION "0.1.2")

include(GNUInstallDirs)
include(CTest)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/vendor/${CMAKE_INSTALL_DATADIR}/cmake")

download_package("https://github.com/Petkr/PPstyle/releases/download/1.0.12/PPstyle-1.0.12-Linux.tar.gz")
download_package("https://github.com/Petkr/PPtest/releases/download/1.0.2/PPtest-1.0.2-Linux.tar.gz")

include(PPstyle)
include(PPtest)

add_subdirectory(PP)
add_subdirectory(tests)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/devel/")
	add_subdirectory(devel)
endif()

set(CPACK_GENERATOR "TGZ")
include(CPack)
