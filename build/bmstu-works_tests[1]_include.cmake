if(EXISTS "/home/somewhat/bmstu-cpp-works/build/bmstu-works_tests[1]_tests.cmake")
  include("/home/somewhat/bmstu-cpp-works/build/bmstu-works_tests[1]_tests.cmake")
else()
  add_test(bmstu-works_tests_NOT_BUILT bmstu-works_tests_NOT_BUILT)
endif()
