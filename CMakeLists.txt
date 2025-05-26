cmake_minimum_required(VERSION 3.16)
project(SASTAnalyzer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build tests" ON)

find_package(yaml-cpp REQUIRED)
find_package(fmt QUIET)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    src/*.hpp
)

add_executable(vulncheck ${SRC_FILES})
target_link_libraries(vulncheck PRIVATE yaml-cpp)

if(fmt_FOUND)
    target_link_libraries(vulncheck PRIVATE fmt::fmt)
    target_compile_definitions(vulncheck PRIVATE USE_FMT)
endif()

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
