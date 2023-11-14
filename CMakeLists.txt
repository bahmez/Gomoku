cmake_minimum_required(VERSION 3.22)
project(Gomoku)

set(CMAKE_CXX_STANDARD 20)

add_executable(Gomoku)

add_subdirectory(CommandsHandler)
add_subdirectory(Gomoku)
