cmake_minimum_required (VERSION 3.8)

project ("AoC_2022")

add_definitions(-DDATA_ROOT_DIR="${CMAKE_SOURCE_DIR}")

add_subdirectory("aoc")

include_directories(${CMAKE_SOURCE_DIR}/aoc)

add_subdirectory ("day01")