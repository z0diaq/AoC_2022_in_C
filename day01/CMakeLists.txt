﻿add_executable (day01 "main.c"   "part1.c" "part2.c")
target_link_libraries(day01 aoc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET day01 PROPERTY C_STANDARD 17)
endif()

target_compile_definitions(day01 PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD>)