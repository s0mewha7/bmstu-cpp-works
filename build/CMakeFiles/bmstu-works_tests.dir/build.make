# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/somewhat/bmstu-works

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/somewhat/bmstu-works/build

# Include any dependencies generated for this target.
include CMakeFiles/bmstu-works_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bmstu-works_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bmstu-works_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bmstu-works_tests.dir/flags.make

CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o: CMakeFiles/bmstu-works_tests.dir/flags.make
CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o: ../dummy_string/string_test.cpp
CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o: CMakeFiles/bmstu-works_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/somewhat/bmstu-works/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o -MF CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o.d -o CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o -c /home/somewhat/bmstu-works/dummy_string/string_test.cpp

CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/somewhat/bmstu-works/dummy_string/string_test.cpp > CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.i

CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/somewhat/bmstu-works/dummy_string/string_test.cpp -o CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.s

CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o: CMakeFiles/bmstu-works_tests.dir/flags.make
CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o: ../second_work/dec2oct_test.cpp
CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o: CMakeFiles/bmstu-works_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/somewhat/bmstu-works/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o -MF CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o.d -o CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o -c /home/somewhat/bmstu-works/second_work/dec2oct_test.cpp

CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/somewhat/bmstu-works/second_work/dec2oct_test.cpp > CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.i

CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/somewhat/bmstu-works/second_work/dec2oct_test.cpp -o CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.s

CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o: CMakeFiles/bmstu-works_tests.dir/flags.make
CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o: ../third_work/xml_format_test.cpp
CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o: CMakeFiles/bmstu-works_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/somewhat/bmstu-works/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o -MF CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o.d -o CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o -c /home/somewhat/bmstu-works/third_work/xml_format_test.cpp

CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/somewhat/bmstu-works/third_work/xml_format_test.cpp > CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.i

CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/somewhat/bmstu-works/third_work/xml_format_test.cpp -o CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.s

# Object files for target bmstu-works_tests
bmstu__works_tests_OBJECTS = \
"CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o" \
"CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o" \
"CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o"

# External object files for target bmstu-works_tests
bmstu__works_tests_EXTERNAL_OBJECTS =

bmstu-works_tests: CMakeFiles/bmstu-works_tests.dir/dummy_string/string_test.cpp.o
bmstu-works_tests: CMakeFiles/bmstu-works_tests.dir/second_work/dec2oct_test.cpp.o
bmstu-works_tests: CMakeFiles/bmstu-works_tests.dir/third_work/xml_format_test.cpp.o
bmstu-works_tests: CMakeFiles/bmstu-works_tests.dir/build.make
bmstu-works_tests: lib/libgtest_main.a
bmstu-works_tests: lib/libgtest.a
bmstu-works_tests: CMakeFiles/bmstu-works_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/somewhat/bmstu-works/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bmstu-works_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bmstu-works_tests.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=bmstu-works_tests -D TEST_EXECUTABLE=/home/somewhat/bmstu-works/build/bmstu-works_tests -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/somewhat/bmstu-works/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=bmstu-works_tests_TESTS -D CTEST_FILE=/home/somewhat/bmstu-works/build/bmstu-works_tests[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/bmstu-works_tests.dir/build: bmstu-works_tests
.PHONY : CMakeFiles/bmstu-works_tests.dir/build

CMakeFiles/bmstu-works_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bmstu-works_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bmstu-works_tests.dir/clean

CMakeFiles/bmstu-works_tests.dir/depend:
	cd /home/somewhat/bmstu-works/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/somewhat/bmstu-works /home/somewhat/bmstu-works /home/somewhat/bmstu-works/build /home/somewhat/bmstu-works/build /home/somewhat/bmstu-works/build/CMakeFiles/bmstu-works_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bmstu-works_tests.dir/depend

