cmake_minimum_required (VERSION 3.8)

add_executable(PPdemo
"main.cpp"
)
target_compile_features(PPdemo PUBLIC cxx_std_20)
set_target_properties(PPdemo PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=4")
target_include_directories(PPdemo PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

target_link_libraries(PPdemo PP)
