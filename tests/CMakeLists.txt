include_directories(
    ${PROJECT_SOURCE_DIR}/external/doctest
    ${PROJECT_SOURCE_DIR}/src/include
)

file(GLOB TEST_SOURCES *.cpp)

file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

list(REMOVE_ITEM PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(vulncheck_tests ${TEST_SOURCES} ${PROJECT_SOURCES})

target_link_libraries(vulncheck_tests yaml-cpp)

add_test(NAME vulncheck_tests COMMAND vulncheck_tests)
