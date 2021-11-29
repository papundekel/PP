cmake_minimum_required(VERSION 3.20)

add_library("PP" SHARED
"dummy.cpp"
#string_view.cpp"
#"ostream.cpp"
)

file(GLOB PP_headers "*.hpp")
target_sources("PP" PUBLIC ${PP_headers})
PPcmake_target_pedantic_errors("PP")
target_include_directories("PP" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../")
target_compile_features("PP" INTERFACE cxx_std_20)
target_compile_options("PP" PUBLIC "-ftemplate-backtrace-limit=0" "-fconcepts-diagnostics-depth=5")

install(TARGETS "PP" LIBRARY)
install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" FILES_MATCHING PATTERN "*.hpp")

PPstyle("PP")
