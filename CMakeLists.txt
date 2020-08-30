cmake_minimum_required (VERSION 3.8)

<<<<<<< HEAD
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PP)

add_subdirectory(Papo)
add_subdirectory(Papundekel)

target_compile_features(Papo PUBLIC cxx_std_20)
target_compile_features(Papundekel PUBLIC cxx_std_20)
=======
project(Papo)

add_subdirectory(Papo)

target_compile_features(Papo PUBLIC cxx_std_20)
>>>>>>> 727fe40adda2d37f2f785e15f6261b25383ac507
