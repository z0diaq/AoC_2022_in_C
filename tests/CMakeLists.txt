# create the testing file and list of tests
create_test_sourcelist (Tests
  testsRunner.c
  intArrayTests.c
  intArraySortingTests.c
)

# add the executable
add_executable (ctests ${Tests})
target_link_libraries(ctests aoc)

# remove the test driver source file
set (TestsToRun ${Tests})
remove (TestsToRun testsRunner.c)

# Add all the ADD_TEST for each test
foreach (test ${TestsToRun})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME ${TName} COMMAND ctests ${TName})
endforeach ()