cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CHILD_PROJECT_NAME max_consecutive_ones)

project("${CHILD_PROJECT_NAME}" LANGUAGES CXX)

# ---- Import tools ----

include(../../cmake/tools.cmake)
# Import PROJECT_WARNINGS list variable
include(../../cmake/warnings.cmake)

# ---- Build type ----

include(../../cmake/buildType.cmake)

# ---- Dependencies ----

include(../../cmake/CPM.cmake)

# root project

set(ROOT_PROJECT_NAME cpp_toying)

CPMAddPackage(NAME "${ROOT_PROJECT_NAME}" SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

# ---- Create executable ----

set(headers)

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
target_link_libraries("${CHILD_PROJECT_NAME}" PRIVATE fmt)

target_compile_options("${CHILD_PROJECT_NAME}" PRIVATE ${PROJECT_WARNINGS})
