cmake_minimum_required(VERSION 3.22)
project(CalcGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CalcLib
        ICalculator.h
        SimpleCalculator.h SimpleCalculator.cpp
        IHistory.h
        InMemoryHistory.h InMemoryHistory.cpp
)

add_custom_target(coverage
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  COMMAND ${LCOV}
    --directory . 
    --capture
    --output-file coverage.info
    --rc geninfo_unexecuted_blocks=1
    --ignore-errors inconsistent
  COMMAND ${LCOV}
    --remove coverage.info '*/googletest/*' '*/googlemock/*' '*/usr/*' '*/test/*'
    --output-file coverage_filtered.info
  COMMAND ${GENHTML}
    --demangle-cpp
    -o coverage
    coverage_filtered.info
  DEPENDS CalcTests
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

enable_testing()

add_subdirectory(test)