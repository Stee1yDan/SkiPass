cmake_minimum_required(VERSION 3.16)
project (cli_view)

set(CMAKE_CXX_STANDARD 23)

add_library(cli_view STATIC source/cli_view.cpp)

target_include_directories(cli_view PUBLIC include)
target_link_libraries(cli_view PUBLIC view)