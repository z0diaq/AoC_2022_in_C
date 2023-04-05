add_library(aoc STATIC "data.c" "data.h" "utils.h" "array.h" "array.c" "testHelpers.h" "runner.h" "runner.c" "utils.c")
target_compile_definitions(aoc PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD>)

