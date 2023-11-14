cmake_minimum_required(VERSION 3.22)

target_sources(Gomoku PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/GameBoard.cpp"
)

target_include_directories(Gomoku PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")