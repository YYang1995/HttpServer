# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/c++/muduo_practice/base/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/c++/muduo_practice/base/test/build

# Include any dependencies generated for this target.
include CMakeFiles/threadTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/threadTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threadTest.dir/flags.make

CMakeFiles/threadTest.dir/ThreadTest.cpp.o: CMakeFiles/threadTest.dir/flags.make
CMakeFiles/threadTest.dir/ThreadTest.cpp.o: ../ThreadTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/base/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threadTest.dir/ThreadTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/ThreadTest.cpp.o -c /home/ubuntu/c++/muduo_practice/base/test/ThreadTest.cpp

CMakeFiles/threadTest.dir/ThreadTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/ThreadTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/base/test/ThreadTest.cpp > CMakeFiles/threadTest.dir/ThreadTest.cpp.i

CMakeFiles/threadTest.dir/ThreadTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/ThreadTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/base/test/ThreadTest.cpp -o CMakeFiles/threadTest.dir/ThreadTest.cpp.s

CMakeFiles/threadTest.dir/ThreadTest.cpp.o.requires:

.PHONY : CMakeFiles/threadTest.dir/ThreadTest.cpp.o.requires

CMakeFiles/threadTest.dir/ThreadTest.cpp.o.provides: CMakeFiles/threadTest.dir/ThreadTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/threadTest.dir/build.make CMakeFiles/threadTest.dir/ThreadTest.cpp.o.provides.build
.PHONY : CMakeFiles/threadTest.dir/ThreadTest.cpp.o.provides

CMakeFiles/threadTest.dir/ThreadTest.cpp.o.provides.build: CMakeFiles/threadTest.dir/ThreadTest.cpp.o


# Object files for target threadTest
threadTest_OBJECTS = \
"CMakeFiles/threadTest.dir/ThreadTest.cpp.o"

# External object files for target threadTest
threadTest_EXTERNAL_OBJECTS =

threadTest: CMakeFiles/threadTest.dir/ThreadTest.cpp.o
threadTest: CMakeFiles/threadTest.dir/build.make
threadTest: CMakeFiles/threadTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/c++/muduo_practice/base/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable threadTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threadTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threadTest.dir/build: threadTest

.PHONY : CMakeFiles/threadTest.dir/build

CMakeFiles/threadTest.dir/requires: CMakeFiles/threadTest.dir/ThreadTest.cpp.o.requires

.PHONY : CMakeFiles/threadTest.dir/requires

CMakeFiles/threadTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threadTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threadTest.dir/clean

CMakeFiles/threadTest.dir/depend:
	cd /home/ubuntu/c++/muduo_practice/base/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/c++/muduo_practice/base/test /home/ubuntu/c++/muduo_practice/base/test /home/ubuntu/c++/muduo_practice/base/test/build /home/ubuntu/c++/muduo_practice/base/test/build /home/ubuntu/c++/muduo_practice/base/test/build/CMakeFiles/threadTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threadTest.dir/depend

