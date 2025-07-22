cmake_minimum_required(VERSION 3.16)
project(abstract_storage_unit_repository)

set(CMAKE_CXX_STANDARD 23)

add_library(abstract_storage_unit_repository INTERFACE)

target_include_directories(abstract_storage_unit_repository INTERFACE include)
target_link_libraries(abstract_storage_unit_repository INTERFACE storage_unit)