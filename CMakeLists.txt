cmake_minimum_required(VERSION 2.8.11)
project(tests)

set(MAIN_TARGET ${PROJECT_NAME})

set(LIB_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(
  ${LIB_DIR}
)

FILE(GLOB SOURCE_TEST "src/test/test_*.cpp")
message("Added test files: ${SOURCE_TEST}")
# //TODO think about profiler.cpp
add_executable(${MAIN_TARGET} ${SOURCE_TEST} src/test/main.cpp include/gun/utils/profiler.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")
add_definitions(-DTESTS)
# add_definitions(-DTRACING)

target_link_libraries(
  ${MAIN_TARGET}
)
