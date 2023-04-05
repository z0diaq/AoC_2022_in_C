cmake_minimum_required (VERSION 3.2)

project ("AoC_2022")

add_definitions(-DDATA_ROOT_DIR="${CMAKE_SOURCE_DIR}" -D_CRT_SECURE_NO_WARNINGS)

add_subdirectory("aoc")

include_directories(${CMAKE_SOURCE_DIR}/aoc)
add_subdirectory("tests")

add_subdirectory ("day01")