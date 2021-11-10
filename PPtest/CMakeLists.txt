cmake_minimum_required(VERSION 3.20)

file(GLOB sources "*.cpp")

add_library("PPtest" SHARED "${sources}")
target_compile_features("PPtest" PUBLIC cxx_std_20)

PPstyle("PPtest")
