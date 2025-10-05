cmake_minimum_required(VERSION 3.20)

project(Chess)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OF)

add_subdirectory(ChessLogic)
add_subdirectory(ChessUI)
