# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Qt\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Qt\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CLearning\VSC\ChatRoom-Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CLearning\VSC\ChatRoom-Client\build\debug

# Utility rule file for ChatRoom-Client2_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/ChatRoom-Client2_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ChatRoom-Client2_autogen.dir/progress.make

CMakeFiles/ChatRoom-Client2_autogen: ChatRoom-Client2_autogen/timestamp

ChatRoom-Client2_autogen/timestamp: C:/Qt/6.7.2/mingw_64/./bin/moc.exe
ChatRoom-Client2_autogen/timestamp: C:/Qt/6.7.2/mingw_64/./bin/uic.exe
ChatRoom-Client2_autogen/timestamp: CMakeFiles/ChatRoom-Client2_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\CLearning\VSC\ChatRoom-Client\build\debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target ChatRoom-Client2"
	C:\Qt\Tools\CMake_64\bin\cmake.exe -E cmake_autogen D:/CLearning/VSC/ChatRoom-Client/build/debug/CMakeFiles/ChatRoom-Client2_autogen.dir/AutogenInfo.json Debug
	C:\Qt\Tools\CMake_64\bin\cmake.exe -E touch D:/CLearning/VSC/ChatRoom-Client/build/debug/ChatRoom-Client2_autogen/timestamp

ChatRoom-Client2_autogen: CMakeFiles/ChatRoom-Client2_autogen
ChatRoom-Client2_autogen: ChatRoom-Client2_autogen/timestamp
ChatRoom-Client2_autogen: CMakeFiles/ChatRoom-Client2_autogen.dir/build.make
.PHONY : ChatRoom-Client2_autogen

# Rule to build all files generated by this target.
CMakeFiles/ChatRoom-Client2_autogen.dir/build: ChatRoom-Client2_autogen
.PHONY : CMakeFiles/ChatRoom-Client2_autogen.dir/build

CMakeFiles/ChatRoom-Client2_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ChatRoom-Client2_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ChatRoom-Client2_autogen.dir/clean

CMakeFiles/ChatRoom-Client2_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLearning\VSC\ChatRoom-Client D:\CLearning\VSC\ChatRoom-Client D:\CLearning\VSC\ChatRoom-Client\build\debug D:\CLearning\VSC\ChatRoom-Client\build\debug D:\CLearning\VSC\ChatRoom-Client\build\debug\CMakeFiles\ChatRoom-Client2_autogen.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ChatRoom-Client2_autogen.dir/depend

