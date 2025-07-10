cmake_minimum_required(VERSION 3.22)

add_executable(CalcTests
    MockTests.cpp
    OverFlowTests.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(CalcTests
    CalcLib
    gtest_main
    gmock_main
)

target_include_directories(CalcTests PRIVATE
    ${CMAKE_SOURCE_DIR}
)

add_test(NAME CalcUnitTests COMMAND CalcTests)

include(GoogleTest)
gtest_discover_tests(CalcTests)