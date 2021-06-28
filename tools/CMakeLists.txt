cmake_minimum_required(VERSION 3.12)
project(tools)
set(CMAKE_CXX_STANDARD 14)

include_directories(../SimpleSaxParser)

if(CMAKE_COMPILER_IS_GNUCXX)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-Werror=return-type")
    add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
else()
    add_definitions(-DUSE64bit=true)
endif()

add_executable(divider DividerTest.cpp WikiDivider.cpp
        ../SimpleSaxParser/SaxParser.cpp)

add_executable(picker PickerTest.cpp WikiPicker.cpp
        ../SimpleSaxParser/SaxParser.cpp)