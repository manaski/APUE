# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lifan/VmShare/APUE/APUE/17_advance_ipc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open

# Include any dependencies generated for this target.
include CMakeFiles/pollmsg.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pollmsg.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pollmsg.dir/flags.make

CMakeFiles/pollmsg.dir/pollmsg.c.o: CMakeFiles/pollmsg.dir/flags.make
CMakeFiles/pollmsg.dir/pollmsg.c.o: ../pollmsg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/pollmsg.dir/pollmsg.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pollmsg.dir/pollmsg.c.o -c /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/pollmsg.c

CMakeFiles/pollmsg.dir/pollmsg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pollmsg.dir/pollmsg.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/pollmsg.c > CMakeFiles/pollmsg.dir/pollmsg.c.i

CMakeFiles/pollmsg.dir/pollmsg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pollmsg.dir/pollmsg.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/pollmsg.c -o CMakeFiles/pollmsg.dir/pollmsg.c.s

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o: CMakeFiles/pollmsg.dir/flags.make
CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o: /Users/lifan/VmShare/APUE/APUE/include/error.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o -c /Users/lifan/VmShare/APUE/APUE/include/error.c

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/include/error.c > CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.i

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/include/error.c -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.s

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o: CMakeFiles/pollmsg.dir/flags.make
CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o: /Users/lifan/VmShare/APUE/APUE/lib/spipe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o -c /Users/lifan/VmShare/APUE/APUE/lib/spipe.c

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/lib/spipe.c > CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.i

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/lib/spipe.c -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.s

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o: CMakeFiles/pollmsg.dir/flags.make
CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o: /Users/lifan/VmShare/APUE/APUE/lib/servlisten.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o -c /Users/lifan/VmShare/APUE/APUE/lib/servlisten.c

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/lib/servlisten.c > CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.i

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/lib/servlisten.c -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.s

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o: CMakeFiles/pollmsg.dir/flags.make
CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o: /Users/lifan/VmShare/APUE/APUE/lib/servaccept.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o -c /Users/lifan/VmShare/APUE/APUE/lib/servaccept.c

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/lib/servaccept.c > CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.i

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/lib/servaccept.c -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.s

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o: CMakeFiles/pollmsg.dir/flags.make
CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o: /Users/lifan/VmShare/APUE/APUE/lib/cliconn.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o -c /Users/lifan/VmShare/APUE/APUE/lib/cliconn.c

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/lib/cliconn.c > CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.i

CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/lib/cliconn.c -o CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.s

# Object files for target pollmsg
pollmsg_OBJECTS = \
"CMakeFiles/pollmsg.dir/pollmsg.c.o" \
"CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o" \
"CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o" \
"CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o" \
"CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o" \
"CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o"

# External object files for target pollmsg
pollmsg_EXTERNAL_OBJECTS =

pollmsg: CMakeFiles/pollmsg.dir/pollmsg.c.o
pollmsg: CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o
pollmsg: CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o
pollmsg: CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o
pollmsg: CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o
pollmsg: CMakeFiles/pollmsg.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o
pollmsg: CMakeFiles/pollmsg.dir/build.make
pollmsg: CMakeFiles/pollmsg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable pollmsg"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pollmsg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pollmsg.dir/build: pollmsg

.PHONY : CMakeFiles/pollmsg.dir/build

CMakeFiles/pollmsg.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pollmsg.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pollmsg.dir/clean

CMakeFiles/pollmsg.dir/depend:
	cd /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lifan/VmShare/APUE/APUE/17_advance_ipc /Users/lifan/VmShare/APUE/APUE/17_advance_ipc /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles/pollmsg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pollmsg.dir/depend

