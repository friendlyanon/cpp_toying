cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CHILD_PROJECT_NAME reverse_only_alpha)

project("${CHILD_PROJECT_NAME}" LANGUAGES CXX)

# ---- Import tools ----

include(../../cmake/tools.cmake)
# Import PROJECT_WARNINGS list variable
include(../../cmake/warnings.cmake)

# ---- Build type ----

include(../../cmake/buildType.cmake)

# ---- Dependencies ----

include(../../cmake/CPM.cmake)

# neo-fun

CPMAddPackage(
  NAME neo_fun
  GITHUB_REPOSITORY "vector-of-bool/neo-fun"
  VERSION 0.4.2
  GIT_TAG 0.4.2
  DOWNLOAD_ONLY YES
)

fail_if_not_added(neo_fun)

add_library(neo_fun INTERFACE)

target_include_directories(neo_fun SYSTEM INTERFACE "$<BUILD_INTERFACE:${neo_fun_SOURCE_DIR}/src>")

target_compile_features(neo_fun INTERFACE cxx_std_20)

# root project

set(ROOT_PROJECT_NAME cpp_toying)

CPMAddPackage(NAME "${ROOT_PROJECT_NAME}" SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

# ---- Create executable ----

set(headers include/reverse_only_alpha.hpp include/reverse_only_alpha_utils.hpp)

set(sources source/main.cpp)

add_executable("${CHILD_PROJECT_NAME}" ${headers} ${sources})

set_target_properties(
  "${CHILD_PROJECT_NAME}"
  PROPERTIES CXX_STANDARD 20
             CXX_EXTENSIONS OFF
             OUTPUT_NAME "${CHILD_PROJECT_NAME}"
)

target_include_directories(
  "${CHILD_PROJECT_NAME}" PRIVATE "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_link_libraries("${CHILD_PROJECT_NAME}" INTERFACE "${ROOT_PROJECT_NAME}")
target_link_libraries("${CHILD_PROJECT_NAME}" PRIVATE neo_fun fmt)

target_compile_options("${CHILD_PROJECT_NAME}" PRIVATE ${PROJECT_WARNINGS})
