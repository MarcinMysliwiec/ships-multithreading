# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /opt/clion-2020.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2020.3.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/psiw/CLionProjects/Sleeping-Barber-Problem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/psiw/CLionProjects/Sleeping-Barber-Problem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Sleeping_Barber_Problem.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Sleeping_Barber_Problem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Sleeping_Barber_Problem.dir/flags.make

CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.o: CMakeFiles/Sleeping_Barber_Problem.dir/flags.make
CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/psiw/CLionProjects/Sleeping-Barber-Problem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.o -c /home/psiw/CLionProjects/Sleeping-Barber-Problem/main.cpp

CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/psiw/CLionProjects/Sleeping-Barber-Problem/main.cpp > CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.i

CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/psiw/CLionProjects/Sleeping-Barber-Problem/main.cpp -o CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.s

CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.o: CMakeFiles/Sleeping_Barber_Problem.dir/flags.make
CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.o: ../Hairdresser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/psiw/CLionProjects/Sleeping-Barber-Problem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.o -c /home/psiw/CLionProjects/Sleeping-Barber-Problem/Hairdresser.cpp

CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/psiw/CLionProjects/Sleeping-Barber-Problem/Hairdresser.cpp > CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.i

CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/psiw/CLionProjects/Sleeping-Barber-Problem/Hairdresser.cpp -o CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.s

# Object files for target Sleeping_Barber_Problem
Sleeping_Barber_Problem_OBJECTS = \
"CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.o" \
"CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.o"

# External object files for target Sleeping_Barber_Problem
Sleeping_Barber_Problem_EXTERNAL_OBJECTS =

Sleeping_Barber_Problem: CMakeFiles/Sleeping_Barber_Problem.dir/main.cpp.o
Sleeping_Barber_Problem: CMakeFiles/Sleeping_Barber_Problem.dir/Hairdresser.cpp.o
Sleeping_Barber_Problem: CMakeFiles/Sleeping_Barber_Problem.dir/build.make
Sleeping_Barber_Problem: CMakeFiles/Sleeping_Barber_Problem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/psiw/CLionProjects/Sleeping-Barber-Problem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Sleeping_Barber_Problem"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Sleeping_Barber_Problem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Sleeping_Barber_Problem.dir/build: Sleeping_Barber_Problem

.PHONY : CMakeFiles/Sleeping_Barber_Problem.dir/build

CMakeFiles/Sleeping_Barber_Problem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Sleeping_Barber_Problem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Sleeping_Barber_Problem.dir/clean

CMakeFiles/Sleeping_Barber_Problem.dir/depend:
	cd /home/psiw/CLionProjects/Sleeping-Barber-Problem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/psiw/CLionProjects/Sleeping-Barber-Problem /home/psiw/CLionProjects/Sleeping-Barber-Problem /home/psiw/CLionProjects/Sleeping-Barber-Problem/cmake-build-debug /home/psiw/CLionProjects/Sleeping-Barber-Problem/cmake-build-debug /home/psiw/CLionProjects/Sleeping-Barber-Problem/cmake-build-debug/CMakeFiles/Sleeping_Barber_Problem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Sleeping_Barber_Problem.dir/depend

