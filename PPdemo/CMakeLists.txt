cmake_minimum_required (VERSION 3.8)

add_executable(PPdemo
"main.cpp"
)
target_compile_features(PPdemo PUBLIC cxx_std_20)
target_include_directories(PPdemo PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(PPdemo PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
endif()

target_link_libraries(PPdemo PP)
