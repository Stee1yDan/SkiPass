cmake_minimum_required(VERSION 3.16)
project (storage_unit_repository)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(abstract_storage_unit_repository)
add_subdirectory(in_memory_storage_unit_repository)
