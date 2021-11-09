cmake_minimum_required(VERSION 3.8)

add_library(PP SHARED
"dummy.cpp"
#string_view.cpp"
#"ostream.cpp"
)

target_compile_features(PP INTERFACE cxx_std_20)

if (CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(PP PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
endif()

add_custom_target(PP-style COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/../PPstyle/format.sh")
add_dependencies(PP PP-style)

include(GNUInstallDirs)

install(TARGETS PP LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" FILES_MATCHING PATTERN "*.hpp")
