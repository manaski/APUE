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
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/server.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server.dir/server.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/server.c.o -c /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/server.c

CMakeFiles/server.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/server.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/server.c > CMakeFiles/server.dir/server.c.i

CMakeFiles/server.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/server.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/server.c -o CMakeFiles/server.dir/server.c.s

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o: /Users/lifan/VmShare/APUE/APUE/include/error.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o -c /Users/lifan/VmShare/APUE/APUE/include/error.c

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/include/error.c > CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.i

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/include/error.c -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.s

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o: /Users/lifan/VmShare/APUE/APUE/lib/spipe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o -c /Users/lifan/VmShare/APUE/APUE/lib/spipe.c

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/lib/spipe.c > CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.i

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/lib/spipe.c -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.s

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o: /Users/lifan/VmShare/APUE/APUE/lib/servlisten.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o -c /Users/lifan/VmShare/APUE/APUE/lib/servlisten.c

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/lib/servlisten.c > CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.i

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/lib/servlisten.c -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.s

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o: /Users/lifan/VmShare/APUE/APUE/lib/servaccept.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o -c /Users/lifan/VmShare/APUE/APUE/lib/servaccept.c

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/lib/servaccept.c > CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.i

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/lib/servaccept.c -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.s

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o: /Users/lifan/VmShare/APUE/APUE/lib/cliconn.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o -c /Users/lifan/VmShare/APUE/APUE/lib/cliconn.c

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lifan/VmShare/APUE/APUE/lib/cliconn.c > CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.i

CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lifan/VmShare/APUE/APUE/lib/cliconn.c -o CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server.c.o" \
"CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o" \
"CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o" \
"CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o" \
"CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o" \
"CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/server.c.o
server: CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/include/error.c.o
server: CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/spipe.c.o
server: CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servlisten.c.o
server: CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/servaccept.c.o
server: CMakeFiles/server.dir/Users/lifan/VmShare/APUE/APUE/lib/cliconn.c.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lifan/VmShare/APUE/APUE/17_advance_ipc /Users/lifan/VmShare/APUE/APUE/17_advance_ipc /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open /Users/lifan/VmShare/APUE/APUE/17_advance_ipc/open/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend
