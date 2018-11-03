cmake_minimum_required(VERSION 2.8.12)
project(HackerRank)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(DOCTEST_WITH_TESTS OFF CACHE BOOL "Build tests/examples" FORCE)
add_subdirectory(doctest EXCLUDE_FROM_ALL)

enable_testing()
add_subdirectory(cmake)
add_subdirectory(DNAHealth)
