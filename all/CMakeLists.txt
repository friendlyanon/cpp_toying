cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(BuildAll LANGUAGES CXX)

include(../cmake/tools.cmake)

set(CHILD_PROJECTS reverse_only_alpha max_consecutive_ones)

foreach(child ${CHILD_PROJECTS})
  add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/../packages/${child}" "${CMAKE_BINARY_DIR}/packages/${child}"
  )
endforeach()
