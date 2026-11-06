cmake_minimum_required(VERSION 3.20)
project(minesweeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG)

add_executable(minesweeper src/main.cpp)
target_link_libraries(minesweeper PRIVATE SDL3::SDL3)

target_compile_options(minesweeper PRIVATE -Wall -Wextra -Wpedantic)