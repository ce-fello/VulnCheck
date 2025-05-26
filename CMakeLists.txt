cmake_minimum_required(VERSION 3.14)
project(vulncheck)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/external/doctest
    ${PROJECT_SOURCE_DIR}/external/json
)

add_subdirectory(external/yaml-cpp)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(vulncheck ${SOURCES})

target_link_libraries(vulncheck yaml-cpp)

enable_testing()
add_subdirectory(tests)
