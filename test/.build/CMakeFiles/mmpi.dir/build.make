# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/guidono/Documents/prog/C++/mpiez/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guidono/Documents/prog/C++/mpiez/test/.build

# Include any dependencies generated for this target.
include CMakeFiles/mmpi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mmpi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mmpi.dir/flags.make

CMakeFiles/mmpi.dir/main.cpp.o: CMakeFiles/mmpi.dir/flags.make
CMakeFiles/mmpi.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/guidono/Documents/prog/C++/mpiez/test/.build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mmpi.dir/main.cpp.o"
	mpic++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mmpi.dir/main.cpp.o -c /home/guidono/Documents/prog/C++/mpiez/test/main.cpp

CMakeFiles/mmpi.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mmpi.dir/main.cpp.i"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/guidono/Documents/prog/C++/mpiez/test/main.cpp > CMakeFiles/mmpi.dir/main.cpp.i

CMakeFiles/mmpi.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mmpi.dir/main.cpp.s"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/guidono/Documents/prog/C++/mpiez/test/main.cpp -o CMakeFiles/mmpi.dir/main.cpp.s

CMakeFiles/mmpi.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/mmpi.dir/main.cpp.o.requires

CMakeFiles/mmpi.dir/main.cpp.o.provides: CMakeFiles/mmpi.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mmpi.dir/build.make CMakeFiles/mmpi.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mmpi.dir/main.cpp.o.provides

CMakeFiles/mmpi.dir/main.cpp.o.provides.build: CMakeFiles/mmpi.dir/main.cpp.o

# Object files for target mmpi
mmpi_OBJECTS = \
"CMakeFiles/mmpi.dir/main.cpp.o"

# External object files for target mmpi
mmpi_EXTERNAL_OBJECTS =

mmpi: CMakeFiles/mmpi.dir/main.cpp.o
mmpi: CMakeFiles/mmpi.dir/build.make
mmpi: CMakeFiles/mmpi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable mmpi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mmpi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mmpi.dir/build: mmpi
.PHONY : CMakeFiles/mmpi.dir/build

CMakeFiles/mmpi.dir/requires: CMakeFiles/mmpi.dir/main.cpp.o.requires
.PHONY : CMakeFiles/mmpi.dir/requires

CMakeFiles/mmpi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mmpi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mmpi.dir/clean

CMakeFiles/mmpi.dir/depend:
	cd /home/guidono/Documents/prog/C++/mpiez/test/.build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guidono/Documents/prog/C++/mpiez/test /home/guidono/Documents/prog/C++/mpiez/test /home/guidono/Documents/prog/C++/mpiez/test/.build /home/guidono/Documents/prog/C++/mpiez/test/.build /home/guidono/Documents/prog/C++/mpiez/test/.build/CMakeFiles/mmpi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mmpi.dir/depend

