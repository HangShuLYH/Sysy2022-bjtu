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
CMAKE_COMMAND = /home/hangshu/桌面/clion-2022.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/hangshu/桌面/clion-2022.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hangshu/桌面/Sysy2022-bjtu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug

# Include any dependencies generated for this target.
include src/frontend/CMakeFiles/parser.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/frontend/CMakeFiles/parser.dir/compiler_depend.make

# Include the progress variables for this target.
include src/frontend/CMakeFiles/parser.dir/progress.make

# Include the compile flags for this target's objects.
include src/frontend/CMakeFiles/parser.dir/flags.make

src/frontend/CMakeFiles/parser.dir/parser.cc.o: src/frontend/CMakeFiles/parser.dir/flags.make
src/frontend/CMakeFiles/parser.dir/parser.cc.o: ../src/frontend/parser.cc
src/frontend/CMakeFiles/parser.dir/parser.cc.o: src/frontend/CMakeFiles/parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/frontend/CMakeFiles/parser.dir/parser.cc.o"
	cd /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/src/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/frontend/CMakeFiles/parser.dir/parser.cc.o -MF CMakeFiles/parser.dir/parser.cc.o.d -o CMakeFiles/parser.dir/parser.cc.o -c /home/hangshu/桌面/Sysy2022-bjtu/src/frontend/parser.cc

src/frontend/CMakeFiles/parser.dir/parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/parser.dir/parser.cc.i"
	cd /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/src/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hangshu/桌面/Sysy2022-bjtu/src/frontend/parser.cc > CMakeFiles/parser.dir/parser.cc.i

src/frontend/CMakeFiles/parser.dir/parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/parser.dir/parser.cc.s"
	cd /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/src/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hangshu/桌面/Sysy2022-bjtu/src/frontend/parser.cc -o CMakeFiles/parser.dir/parser.cc.s

# Object files for target parser
parser_OBJECTS = \
"CMakeFiles/parser.dir/parser.cc.o"

# External object files for target parser
parser_EXTERNAL_OBJECTS =

src/frontend/libparser.a: src/frontend/CMakeFiles/parser.dir/parser.cc.o
src/frontend/libparser.a: src/frontend/CMakeFiles/parser.dir/build.make
src/frontend/libparser.a: src/frontend/CMakeFiles/parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libparser.a"
	cd /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/src/frontend && $(CMAKE_COMMAND) -P CMakeFiles/parser.dir/cmake_clean_target.cmake
	cd /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/src/frontend && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/frontend/CMakeFiles/parser.dir/build: src/frontend/libparser.a
.PHONY : src/frontend/CMakeFiles/parser.dir/build

src/frontend/CMakeFiles/parser.dir/clean:
	cd /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/src/frontend && $(CMAKE_COMMAND) -P CMakeFiles/parser.dir/cmake_clean.cmake
.PHONY : src/frontend/CMakeFiles/parser.dir/clean

src/frontend/CMakeFiles/parser.dir/depend:
	cd /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hangshu/桌面/Sysy2022-bjtu /home/hangshu/桌面/Sysy2022-bjtu/src/frontend /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/src/frontend /home/hangshu/桌面/Sysy2022-bjtu/cmake-build-debug/src/frontend/CMakeFiles/parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/frontend/CMakeFiles/parser.dir/depend

