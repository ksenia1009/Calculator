cmake_minimum_required(VERSION 3.6)

project(cpp-calculator-tests)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(
    Note.h
    Stack.h
    Table.h
    RPN.h
    Expression.h
    ${GTEST_INCLUDE_DIRS}
)

add_executable(
  TestSerialization tests.cpp)

target_link_libraries(
  TestSerialization ${GTEST_LIBRARIES} pthread)

enable_testing()
add_test(TestSerialization "./TestSerialization")
