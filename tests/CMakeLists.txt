file(GLOB TEST_SOURCES *.cpp)

add_executable(unit-tests ${TEST_SOURCES})
target_link_libraries(unit-tests PRIVATE yaml-cpp)

target_include_directories(unit-tests PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_sources(unit-tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src/PatternLoader.cpp
    ${PROJECT_SOURCE_DIR}/src/Analyzer.cpp
)

add_test(NAME AllTests COMMAND unit-tests)
