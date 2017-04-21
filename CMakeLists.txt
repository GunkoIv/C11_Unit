cmake_minimum_required(VERSION 2.8.11)
project(tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")

set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(MAIN_TARGET ${PROJECT_NAME})

FILE(GLOB SOURCE_MAIN "src/test/*.cpp")

find_library(RT NAMES rt PATHS /usr/local/lib)

include_directories(
    /src/test
)

add_executable(${MAIN_TARGET} ${SOURCE_MAIN})

add_definitions(-DTESTS)

target_link_libraries(
    ${MAIN_TARGET}
    ${RT}
)
