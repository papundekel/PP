cmake_minimum_required (VERSION 3.8)

project(Papundekel)

add_executable(Papundekel Papundekel.cpp)

add_custom_target(PapundekelRunner COMMAND Papundekel WORKING_DIRECTORY ${Papo_SOURCE_DIR})
