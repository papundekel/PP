cmake_minimum_required(VERSION 3.20)

add_library("PP" SHARED
"dummy.cpp"
#string_view.cpp"
#"ostream.cpp"
)

target_include_directories("PP" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../")

PPcmake_target_pedantic_errors("PP")

file(GLOB PP_headers "*.hpp")

target_sources("PP" PUBLIC ${PP_headers})

target_compile_features("PP" INTERFACE cxx_std_20)

if (CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties("PP" PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
endif()

include(GNUInstallDirs)

install(TARGETS "PP" LIBRARY)
install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" FILES_MATCHING PATTERN "*.hpp")

PPstyle("PP")
