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
CMAKE_SOURCE_DIR = /home/ubuntu/c++/muduo_practice/net/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/c++/muduo_practice/net/test/build

# Include any dependencies generated for this target.
include CMakeFiles/eventloopTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/eventloopTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eventloopTest.dir/flags.make

CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o: CMakeFiles/eventloopTest.dir/flags.make
CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o: ../EventLoopTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o -c /home/ubuntu/c++/muduo_practice/net/test/EventLoopTest.cpp

CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/test/EventLoopTest.cpp > CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.i

CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/test/EventLoopTest.cpp -o CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.s

CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o.requires:

.PHONY : CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o.requires

CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o.provides: CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/eventloopTest.dir/build.make CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o.provides.build
.PHONY : CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o.provides

CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o.provides.build: CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o


# Object files for target eventloopTest
eventloopTest_OBJECTS = \
"CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o"

# External object files for target eventloopTest
eventloopTest_EXTERNAL_OBJECTS =

eventloopTest: CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o
eventloopTest: CMakeFiles/eventloopTest.dir/build.make
eventloopTest: CMakeFiles/eventloopTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/c++/muduo_practice/net/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable eventloopTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eventloopTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eventloopTest.dir/build: eventloopTest

.PHONY : CMakeFiles/eventloopTest.dir/build

CMakeFiles/eventloopTest.dir/requires: CMakeFiles/eventloopTest.dir/EventLoopTest.cpp.o.requires

.PHONY : CMakeFiles/eventloopTest.dir/requires

CMakeFiles/eventloopTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eventloopTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eventloopTest.dir/clean

CMakeFiles/eventloopTest.dir/depend:
	cd /home/ubuntu/c++/muduo_practice/net/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/c++/muduo_practice/net/test /home/ubuntu/c++/muduo_practice/net/test /home/ubuntu/c++/muduo_practice/net/test/build /home/ubuntu/c++/muduo_practice/net/test/build /home/ubuntu/c++/muduo_practice/net/test/build/CMakeFiles/eventloopTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eventloopTest.dir/depend

