# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /home/lin/下载/clion-2021.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/lin/下载/clion-2021.3.4/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lin/下载/workspace/Sysy2022-bjtu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug

# Include any dependencies generated for this target.
include src/frontend/CMakeFiles/syntax_tree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/frontend/CMakeFiles/syntax_tree.dir/compiler_depend.make

# Include the progress variables for this target.
include src/frontend/CMakeFiles/syntax_tree.dir/progress.make

# Include the compile flags for this target's objects.
include src/frontend/CMakeFiles/syntax_tree.dir/flags.make

src/frontend/CMakeFiles/syntax_tree.dir/syntax_tree.cc.o: src/frontend/CMakeFiles/syntax_tree.dir/flags.make
src/frontend/CMakeFiles/syntax_tree.dir/syntax_tree.cc.o: ../src/frontend/syntax_tree.cc
src/frontend/CMakeFiles/syntax_tree.dir/syntax_tree.cc.o: src/frontend/CMakeFiles/syntax_tree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/frontend/CMakeFiles/syntax_tree.dir/syntax_tree.cc.o"
	cd /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/src/frontend && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/frontend/CMakeFiles/syntax_tree.dir/syntax_tree.cc.o -MF CMakeFiles/syntax_tree.dir/syntax_tree.cc.o.d -o CMakeFiles/syntax_tree.dir/syntax_tree.cc.o -c /home/lin/下载/workspace/Sysy2022-bjtu/src/frontend/syntax_tree.cc

src/frontend/CMakeFiles/syntax_tree.dir/syntax_tree.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/syntax_tree.dir/syntax_tree.cc.i"
	cd /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/src/frontend && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lin/下载/workspace/Sysy2022-bjtu/src/frontend/syntax_tree.cc > CMakeFiles/syntax_tree.dir/syntax_tree.cc.i

src/frontend/CMakeFiles/syntax_tree.dir/syntax_tree.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/syntax_tree.dir/syntax_tree.cc.s"
	cd /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/src/frontend && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lin/下载/workspace/Sysy2022-bjtu/src/frontend/syntax_tree.cc -o CMakeFiles/syntax_tree.dir/syntax_tree.cc.s

# Object files for target syntax_tree
syntax_tree_OBJECTS = \
"CMakeFiles/syntax_tree.dir/syntax_tree.cc.o"

# External object files for target syntax_tree
syntax_tree_EXTERNAL_OBJECTS =

src/frontend/libsyntax_tree.a: src/frontend/CMakeFiles/syntax_tree.dir/syntax_tree.cc.o
src/frontend/libsyntax_tree.a: src/frontend/CMakeFiles/syntax_tree.dir/build.make
src/frontend/libsyntax_tree.a: src/frontend/CMakeFiles/syntax_tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsyntax_tree.a"
	cd /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/src/frontend && $(CMAKE_COMMAND) -P CMakeFiles/syntax_tree.dir/cmake_clean_target.cmake
	cd /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/src/frontend && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/syntax_tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/frontend/CMakeFiles/syntax_tree.dir/build: src/frontend/libsyntax_tree.a
.PHONY : src/frontend/CMakeFiles/syntax_tree.dir/build

src/frontend/CMakeFiles/syntax_tree.dir/clean:
	cd /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/src/frontend && $(CMAKE_COMMAND) -P CMakeFiles/syntax_tree.dir/cmake_clean.cmake
.PHONY : src/frontend/CMakeFiles/syntax_tree.dir/clean

src/frontend/CMakeFiles/syntax_tree.dir/depend:
	cd /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lin/下载/workspace/Sysy2022-bjtu /home/lin/下载/workspace/Sysy2022-bjtu/src/frontend /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/src/frontend /home/lin/下载/workspace/Sysy2022-bjtu/cmake-build-debug/src/frontend/CMakeFiles/syntax_tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/frontend/CMakeFiles/syntax_tree.dir/depend

