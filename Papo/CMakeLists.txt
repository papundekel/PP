cmake_minimum_required (VERSION 3.8)

project(Papo)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${Papo_SOURCE_DIR})

add_executable(Papo Papo.cpp)

add_dependencies(Papo PapundekelRunner)

foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
    target_link_libraries(Papo ${subdir})
endforeach()
