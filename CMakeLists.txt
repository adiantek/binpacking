cmake_minimum_required(VERSION 3.15)

project(binpacking)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

include_directories("include")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(${PROJECT_NAME} ${SOURCES})
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

target_compile_definitions(${PROJECT_NAME}_lib PRIVATE STATIC_LIBRARY=1)