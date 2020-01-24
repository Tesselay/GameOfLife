cmake_minimum_required(VERSION 3.5)

project(TestFieldConstructor LANGUAGES CXX)

find_package(Qt5Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(TestFieldConstructor tst_testfieldconstructor.cpp
     "../gamelogic.cpp" "../playfield.cpp" "../utilities.cpp")
add_test(NAME TestFieldConstructor COMMAND TestFieldConstructor)

target_link_libraries(TestFieldConstructor PRIVATE Qt5::Test)

