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
CMAKE_SOURCE_DIR = /home/ubuntu/c++/muduo_practice/net

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/c++/muduo_practice/net/build

# Include any dependencies generated for this target.
include CMakeFiles/my_net.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_net.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_net.dir/flags.make

CMakeFiles/my_net.dir/Channel.cpp.o: CMakeFiles/my_net.dir/flags.make
CMakeFiles/my_net.dir/Channel.cpp.o: ../Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_net.dir/Channel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_net.dir/Channel.cpp.o -c /home/ubuntu/c++/muduo_practice/net/Channel.cpp

CMakeFiles/my_net.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_net.dir/Channel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/Channel.cpp > CMakeFiles/my_net.dir/Channel.cpp.i

CMakeFiles/my_net.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_net.dir/Channel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/Channel.cpp -o CMakeFiles/my_net.dir/Channel.cpp.s

CMakeFiles/my_net.dir/Channel.cpp.o.requires:

.PHONY : CMakeFiles/my_net.dir/Channel.cpp.o.requires

CMakeFiles/my_net.dir/Channel.cpp.o.provides: CMakeFiles/my_net.dir/Channel.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_net.dir/build.make CMakeFiles/my_net.dir/Channel.cpp.o.provides.build
.PHONY : CMakeFiles/my_net.dir/Channel.cpp.o.provides

CMakeFiles/my_net.dir/Channel.cpp.o.provides.build: CMakeFiles/my_net.dir/Channel.cpp.o


CMakeFiles/my_net.dir/EventLoop.cpp.o: CMakeFiles/my_net.dir/flags.make
CMakeFiles/my_net.dir/EventLoop.cpp.o: ../EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_net.dir/EventLoop.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_net.dir/EventLoop.cpp.o -c /home/ubuntu/c++/muduo_practice/net/EventLoop.cpp

CMakeFiles/my_net.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_net.dir/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/EventLoop.cpp > CMakeFiles/my_net.dir/EventLoop.cpp.i

CMakeFiles/my_net.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_net.dir/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/EventLoop.cpp -o CMakeFiles/my_net.dir/EventLoop.cpp.s

CMakeFiles/my_net.dir/EventLoop.cpp.o.requires:

.PHONY : CMakeFiles/my_net.dir/EventLoop.cpp.o.requires

CMakeFiles/my_net.dir/EventLoop.cpp.o.provides: CMakeFiles/my_net.dir/EventLoop.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_net.dir/build.make CMakeFiles/my_net.dir/EventLoop.cpp.o.provides.build
.PHONY : CMakeFiles/my_net.dir/EventLoop.cpp.o.provides

CMakeFiles/my_net.dir/EventLoop.cpp.o.provides.build: CMakeFiles/my_net.dir/EventLoop.cpp.o


CMakeFiles/my_net.dir/Poller.cpp.o: CMakeFiles/my_net.dir/flags.make
CMakeFiles/my_net.dir/Poller.cpp.o: ../Poller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_net.dir/Poller.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_net.dir/Poller.cpp.o -c /home/ubuntu/c++/muduo_practice/net/Poller.cpp

CMakeFiles/my_net.dir/Poller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_net.dir/Poller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/Poller.cpp > CMakeFiles/my_net.dir/Poller.cpp.i

CMakeFiles/my_net.dir/Poller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_net.dir/Poller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/Poller.cpp -o CMakeFiles/my_net.dir/Poller.cpp.s

CMakeFiles/my_net.dir/Poller.cpp.o.requires:

.PHONY : CMakeFiles/my_net.dir/Poller.cpp.o.requires

CMakeFiles/my_net.dir/Poller.cpp.o.provides: CMakeFiles/my_net.dir/Poller.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_net.dir/build.make CMakeFiles/my_net.dir/Poller.cpp.o.provides.build
.PHONY : CMakeFiles/my_net.dir/Poller.cpp.o.provides

CMakeFiles/my_net.dir/Poller.cpp.o.provides.build: CMakeFiles/my_net.dir/Poller.cpp.o


CMakeFiles/my_net.dir/EventLoopThread.cpp.o: CMakeFiles/my_net.dir/flags.make
CMakeFiles/my_net.dir/EventLoopThread.cpp.o: ../EventLoopThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_net.dir/EventLoopThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_net.dir/EventLoopThread.cpp.o -c /home/ubuntu/c++/muduo_practice/net/EventLoopThread.cpp

CMakeFiles/my_net.dir/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_net.dir/EventLoopThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/EventLoopThread.cpp > CMakeFiles/my_net.dir/EventLoopThread.cpp.i

CMakeFiles/my_net.dir/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_net.dir/EventLoopThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/EventLoopThread.cpp -o CMakeFiles/my_net.dir/EventLoopThread.cpp.s

CMakeFiles/my_net.dir/EventLoopThread.cpp.o.requires:

.PHONY : CMakeFiles/my_net.dir/EventLoopThread.cpp.o.requires

CMakeFiles/my_net.dir/EventLoopThread.cpp.o.provides: CMakeFiles/my_net.dir/EventLoopThread.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_net.dir/build.make CMakeFiles/my_net.dir/EventLoopThread.cpp.o.provides.build
.PHONY : CMakeFiles/my_net.dir/EventLoopThread.cpp.o.provides

CMakeFiles/my_net.dir/EventLoopThread.cpp.o.provides.build: CMakeFiles/my_net.dir/EventLoopThread.cpp.o


CMakeFiles/my_net.dir/SocketOperation.cpp.o: CMakeFiles/my_net.dir/flags.make
CMakeFiles/my_net.dir/SocketOperation.cpp.o: ../SocketOperation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_net.dir/SocketOperation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_net.dir/SocketOperation.cpp.o -c /home/ubuntu/c++/muduo_practice/net/SocketOperation.cpp

CMakeFiles/my_net.dir/SocketOperation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_net.dir/SocketOperation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/SocketOperation.cpp > CMakeFiles/my_net.dir/SocketOperation.cpp.i

CMakeFiles/my_net.dir/SocketOperation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_net.dir/SocketOperation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/SocketOperation.cpp -o CMakeFiles/my_net.dir/SocketOperation.cpp.s

CMakeFiles/my_net.dir/SocketOperation.cpp.o.requires:

.PHONY : CMakeFiles/my_net.dir/SocketOperation.cpp.o.requires

CMakeFiles/my_net.dir/SocketOperation.cpp.o.provides: CMakeFiles/my_net.dir/SocketOperation.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_net.dir/build.make CMakeFiles/my_net.dir/SocketOperation.cpp.o.provides.build
.PHONY : CMakeFiles/my_net.dir/SocketOperation.cpp.o.provides

CMakeFiles/my_net.dir/SocketOperation.cpp.o.provides.build: CMakeFiles/my_net.dir/SocketOperation.cpp.o


CMakeFiles/my_net.dir/Socket.cpp.o: CMakeFiles/my_net.dir/flags.make
CMakeFiles/my_net.dir/Socket.cpp.o: ../Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_net.dir/Socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_net.dir/Socket.cpp.o -c /home/ubuntu/c++/muduo_practice/net/Socket.cpp

CMakeFiles/my_net.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_net.dir/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/Socket.cpp > CMakeFiles/my_net.dir/Socket.cpp.i

CMakeFiles/my_net.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_net.dir/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/Socket.cpp -o CMakeFiles/my_net.dir/Socket.cpp.s

CMakeFiles/my_net.dir/Socket.cpp.o.requires:

.PHONY : CMakeFiles/my_net.dir/Socket.cpp.o.requires

CMakeFiles/my_net.dir/Socket.cpp.o.provides: CMakeFiles/my_net.dir/Socket.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_net.dir/build.make CMakeFiles/my_net.dir/Socket.cpp.o.provides.build
.PHONY : CMakeFiles/my_net.dir/Socket.cpp.o.provides

CMakeFiles/my_net.dir/Socket.cpp.o.provides.build: CMakeFiles/my_net.dir/Socket.cpp.o


CMakeFiles/my_net.dir/SocketAddr.cpp.o: CMakeFiles/my_net.dir/flags.make
CMakeFiles/my_net.dir/SocketAddr.cpp.o: ../SocketAddr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/my_net.dir/SocketAddr.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_net.dir/SocketAddr.cpp.o -c /home/ubuntu/c++/muduo_practice/net/SocketAddr.cpp

CMakeFiles/my_net.dir/SocketAddr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_net.dir/SocketAddr.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/SocketAddr.cpp > CMakeFiles/my_net.dir/SocketAddr.cpp.i

CMakeFiles/my_net.dir/SocketAddr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_net.dir/SocketAddr.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/SocketAddr.cpp -o CMakeFiles/my_net.dir/SocketAddr.cpp.s

CMakeFiles/my_net.dir/SocketAddr.cpp.o.requires:

.PHONY : CMakeFiles/my_net.dir/SocketAddr.cpp.o.requires

CMakeFiles/my_net.dir/SocketAddr.cpp.o.provides: CMakeFiles/my_net.dir/SocketAddr.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_net.dir/build.make CMakeFiles/my_net.dir/SocketAddr.cpp.o.provides.build
.PHONY : CMakeFiles/my_net.dir/SocketAddr.cpp.o.provides

CMakeFiles/my_net.dir/SocketAddr.cpp.o.provides.build: CMakeFiles/my_net.dir/SocketAddr.cpp.o


CMakeFiles/my_net.dir/TcpAcceptor.cpp.o: CMakeFiles/my_net.dir/flags.make
CMakeFiles/my_net.dir/TcpAcceptor.cpp.o: ../TcpAcceptor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/my_net.dir/TcpAcceptor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_net.dir/TcpAcceptor.cpp.o -c /home/ubuntu/c++/muduo_practice/net/TcpAcceptor.cpp

CMakeFiles/my_net.dir/TcpAcceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_net.dir/TcpAcceptor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/c++/muduo_practice/net/TcpAcceptor.cpp > CMakeFiles/my_net.dir/TcpAcceptor.cpp.i

CMakeFiles/my_net.dir/TcpAcceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_net.dir/TcpAcceptor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/c++/muduo_practice/net/TcpAcceptor.cpp -o CMakeFiles/my_net.dir/TcpAcceptor.cpp.s

CMakeFiles/my_net.dir/TcpAcceptor.cpp.o.requires:

.PHONY : CMakeFiles/my_net.dir/TcpAcceptor.cpp.o.requires

CMakeFiles/my_net.dir/TcpAcceptor.cpp.o.provides: CMakeFiles/my_net.dir/TcpAcceptor.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_net.dir/build.make CMakeFiles/my_net.dir/TcpAcceptor.cpp.o.provides.build
.PHONY : CMakeFiles/my_net.dir/TcpAcceptor.cpp.o.provides

CMakeFiles/my_net.dir/TcpAcceptor.cpp.o.provides.build: CMakeFiles/my_net.dir/TcpAcceptor.cpp.o


# Object files for target my_net
my_net_OBJECTS = \
"CMakeFiles/my_net.dir/Channel.cpp.o" \
"CMakeFiles/my_net.dir/EventLoop.cpp.o" \
"CMakeFiles/my_net.dir/Poller.cpp.o" \
"CMakeFiles/my_net.dir/EventLoopThread.cpp.o" \
"CMakeFiles/my_net.dir/SocketOperation.cpp.o" \
"CMakeFiles/my_net.dir/Socket.cpp.o" \
"CMakeFiles/my_net.dir/SocketAddr.cpp.o" \
"CMakeFiles/my_net.dir/TcpAcceptor.cpp.o"

# External object files for target my_net
my_net_EXTERNAL_OBJECTS =

libmy_net.a: CMakeFiles/my_net.dir/Channel.cpp.o
libmy_net.a: CMakeFiles/my_net.dir/EventLoop.cpp.o
libmy_net.a: CMakeFiles/my_net.dir/Poller.cpp.o
libmy_net.a: CMakeFiles/my_net.dir/EventLoopThread.cpp.o
libmy_net.a: CMakeFiles/my_net.dir/SocketOperation.cpp.o
libmy_net.a: CMakeFiles/my_net.dir/Socket.cpp.o
libmy_net.a: CMakeFiles/my_net.dir/SocketAddr.cpp.o
libmy_net.a: CMakeFiles/my_net.dir/TcpAcceptor.cpp.o
libmy_net.a: CMakeFiles/my_net.dir/build.make
libmy_net.a: CMakeFiles/my_net.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/c++/muduo_practice/net/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libmy_net.a"
	$(CMAKE_COMMAND) -P CMakeFiles/my_net.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_net.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_net.dir/build: libmy_net.a

.PHONY : CMakeFiles/my_net.dir/build

CMakeFiles/my_net.dir/requires: CMakeFiles/my_net.dir/Channel.cpp.o.requires
CMakeFiles/my_net.dir/requires: CMakeFiles/my_net.dir/EventLoop.cpp.o.requires
CMakeFiles/my_net.dir/requires: CMakeFiles/my_net.dir/Poller.cpp.o.requires
CMakeFiles/my_net.dir/requires: CMakeFiles/my_net.dir/EventLoopThread.cpp.o.requires
CMakeFiles/my_net.dir/requires: CMakeFiles/my_net.dir/SocketOperation.cpp.o.requires
CMakeFiles/my_net.dir/requires: CMakeFiles/my_net.dir/Socket.cpp.o.requires
CMakeFiles/my_net.dir/requires: CMakeFiles/my_net.dir/SocketAddr.cpp.o.requires
CMakeFiles/my_net.dir/requires: CMakeFiles/my_net.dir/TcpAcceptor.cpp.o.requires

.PHONY : CMakeFiles/my_net.dir/requires

CMakeFiles/my_net.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_net.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_net.dir/clean

CMakeFiles/my_net.dir/depend:
	cd /home/ubuntu/c++/muduo_practice/net/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/c++/muduo_practice/net /home/ubuntu/c++/muduo_practice/net /home/ubuntu/c++/muduo_practice/net/build /home/ubuntu/c++/muduo_practice/net/build /home/ubuntu/c++/muduo_practice/net/build/CMakeFiles/my_net.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_net.dir/depend

