cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PP)

add_subdirectory(Papo)
add_subdirectory(Papundekel)

target_compile_features(Papo PUBLIC cxx_std_20)
target_compile_features(Papundekel PUBLIC cxx_std_20)
