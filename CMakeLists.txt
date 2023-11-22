cmake_minimum_required(VERSION 3.22)
project(Gomoku)

set(CMAKE_CXX_STANDARD 20)

add_executable(pbrain-gomoku-ai)

add_subdirectory(CommandsHandler)
add_subdirectory(Gomoku)
add_subdirectory(Frouzins)

add_custom_command(
        TARGET pbrain-gomoku-ai
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:pbrain-gomoku-ai>
        ${CMAKE_CURRENT_SOURCE_DIR}/$<TARGET_FILE_NAME:pbrain-gomoku-ai>
)