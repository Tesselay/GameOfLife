cmake_minimum_required(VERSION 3.5)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

find_package(Qt5Core)
find_package(Qt5Test REQUIRED)

add_executable(GameOfLife
  main.cpp mainmenu.cpp playfield.cpp utilities.cpp gamelogic.cpp "test/tst_testfieldconstructor.cpp"
)
add_test(NAME TestFieldConstructor COMMAND TestFieldConstructor)

add_subdirectory(test)

target_link_libraries(GameOfLife Qt5::Core Qt5::Test)
