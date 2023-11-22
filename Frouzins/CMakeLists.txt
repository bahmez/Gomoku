cmake_minimum_required(VERSION 3.22)

target_sources(pbrain-gomoku-ai PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/index.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp"
)

target_include_directories(pbrain-gomoku-ai PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")