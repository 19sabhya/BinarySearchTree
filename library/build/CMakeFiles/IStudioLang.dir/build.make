# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Sabhya/Desktop/IStudio/library

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Sabhya/Desktop/IStudio/library/build

# Include any dependencies generated for this target.
include CMakeFiles/IStudioLang.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IStudioLang.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IStudioLang.dir/flags.make

CMakeFiles/IStudioLang.dir/source/main.cpp.o: CMakeFiles/IStudioLang.dir/flags.make
CMakeFiles/IStudioLang.dir/source/main.cpp.o: ../source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Sabhya/Desktop/IStudio/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IStudioLang.dir/source/main.cpp.o"
	/bin/g++-10  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IStudioLang.dir/source/main.cpp.o -c /mnt/c/Users/Sabhya/Desktop/IStudio/library/source/main.cpp

CMakeFiles/IStudioLang.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IStudioLang.dir/source/main.cpp.i"
	/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Sabhya/Desktop/IStudio/library/source/main.cpp > CMakeFiles/IStudioLang.dir/source/main.cpp.i

CMakeFiles/IStudioLang.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IStudioLang.dir/source/main.cpp.s"
	/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Sabhya/Desktop/IStudio/library/source/main.cpp -o CMakeFiles/IStudioLang.dir/source/main.cpp.s

# Object files for target IStudioLang
IStudioLang_OBJECTS = \
"CMakeFiles/IStudioLang.dir/source/main.cpp.o"

# External object files for target IStudioLang
IStudioLang_EXTERNAL_OBJECTS =

../bin/IStudioLang: CMakeFiles/IStudioLang.dir/source/main.cpp.o
../bin/IStudioLang: CMakeFiles/IStudioLang.dir/build.make
../bin/IStudioLang: CMakeFiles/IStudioLang.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Sabhya/Desktop/IStudio/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/IStudioLang"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IStudioLang.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IStudioLang.dir/build: ../bin/IStudioLang

.PHONY : CMakeFiles/IStudioLang.dir/build

CMakeFiles/IStudioLang.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IStudioLang.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IStudioLang.dir/clean

CMakeFiles/IStudioLang.dir/depend:
	cd /mnt/c/Users/Sabhya/Desktop/IStudio/library/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Sabhya/Desktop/IStudio/library /mnt/c/Users/Sabhya/Desktop/IStudio/library /mnt/c/Users/Sabhya/Desktop/IStudio/library/build /mnt/c/Users/Sabhya/Desktop/IStudio/library/build /mnt/c/Users/Sabhya/Desktop/IStudio/library/build/CMakeFiles/IStudioLang.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IStudioLang.dir/depend

