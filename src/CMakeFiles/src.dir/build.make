# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024

# Include any dependencies generated for this target.
include src/CMakeFiles/src.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/src.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src.dir/flags.make

src/CMakeFiles/src.dir/units/Instruction.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/units/Instruction.cpp.o: src/units/Instruction.cpp
src/CMakeFiles/src.dir/units/Instruction.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src.dir/units/Instruction.cpp.o"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/units/Instruction.cpp.o -MF CMakeFiles/src.dir/units/Instruction.cpp.o.d -o CMakeFiles/src.dir/units/Instruction.cpp.o -c /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Instruction.cpp

src/CMakeFiles/src.dir/units/Instruction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/src.dir/units/Instruction.cpp.i"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Instruction.cpp > CMakeFiles/src.dir/units/Instruction.cpp.i

src/CMakeFiles/src.dir/units/Instruction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/src.dir/units/Instruction.cpp.s"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Instruction.cpp -o CMakeFiles/src.dir/units/Instruction.cpp.s

src/CMakeFiles/src.dir/units/Memory.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/units/Memory.cpp.o: src/units/Memory.cpp
src/CMakeFiles/src.dir/units/Memory.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/src.dir/units/Memory.cpp.o"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/units/Memory.cpp.o -MF CMakeFiles/src.dir/units/Memory.cpp.o.d -o CMakeFiles/src.dir/units/Memory.cpp.o -c /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Memory.cpp

src/CMakeFiles/src.dir/units/Memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/src.dir/units/Memory.cpp.i"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Memory.cpp > CMakeFiles/src.dir/units/Memory.cpp.i

src/CMakeFiles/src.dir/units/Memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/src.dir/units/Memory.cpp.s"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Memory.cpp -o CMakeFiles/src.dir/units/Memory.cpp.s

src/CMakeFiles/src.dir/units/Register_file.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/units/Register_file.cpp.o: src/units/Register_file.cpp
src/CMakeFiles/src.dir/units/Register_file.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/src.dir/units/Register_file.cpp.o"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/units/Register_file.cpp.o -MF CMakeFiles/src.dir/units/Register_file.cpp.o.d -o CMakeFiles/src.dir/units/Register_file.cpp.o -c /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Register_file.cpp

src/CMakeFiles/src.dir/units/Register_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/src.dir/units/Register_file.cpp.i"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Register_file.cpp > CMakeFiles/src.dir/units/Register_file.cpp.i

src/CMakeFiles/src.dir/units/Register_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/src.dir/units/Register_file.cpp.s"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/units/Register_file.cpp -o CMakeFiles/src.dir/units/Register_file.cpp.s

src/CMakeFiles/src.dir/utility/util.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/utility/util.cpp.o: src/utility/util.cpp
src/CMakeFiles/src.dir/utility/util.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/src.dir/utility/util.cpp.o"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/utility/util.cpp.o -MF CMakeFiles/src.dir/utility/util.cpp.o.d -o CMakeFiles/src.dir/utility/util.cpp.o -c /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/utility/util.cpp

src/CMakeFiles/src.dir/utility/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/src.dir/utility/util.cpp.i"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/utility/util.cpp > CMakeFiles/src.dir/utility/util.cpp.i

src/CMakeFiles/src.dir/utility/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/src.dir/utility/util.cpp.s"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/utility/util.cpp -o CMakeFiles/src.dir/utility/util.cpp.s

src/CMakeFiles/src.dir/simulator.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/simulator.cpp.o: src/simulator.cpp
src/CMakeFiles/src.dir/simulator.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/src.dir/simulator.cpp.o"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/simulator.cpp.o -MF CMakeFiles/src.dir/simulator.cpp.o.d -o CMakeFiles/src.dir/simulator.cpp.o -c /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/simulator.cpp

src/CMakeFiles/src.dir/simulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/src.dir/simulator.cpp.i"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/simulator.cpp > CMakeFiles/src.dir/simulator.cpp.i

src/CMakeFiles/src.dir/simulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/src.dir/simulator.cpp.s"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/simulator.cpp -o CMakeFiles/src.dir/simulator.cpp.s

# Object files for target src
src_OBJECTS = \
"CMakeFiles/src.dir/units/Instruction.cpp.o" \
"CMakeFiles/src.dir/units/Memory.cpp.o" \
"CMakeFiles/src.dir/units/Register_file.cpp.o" \
"CMakeFiles/src.dir/utility/util.cpp.o" \
"CMakeFiles/src.dir/simulator.cpp.o"

# External object files for target src
src_EXTERNAL_OBJECTS =

src/libsrc.a: src/CMakeFiles/src.dir/units/Instruction.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/units/Memory.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/units/Register_file.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/utility/util.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/simulator.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/build.make
src/libsrc.a: src/CMakeFiles/src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libsrc.a"
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean_target.cmake
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src.dir/build: src/libsrc.a
.PHONY : src/CMakeFiles/src.dir/build

src/CMakeFiles/src.dir/clean:
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src.dir/clean

src/CMakeFiles/src.dir/depend:
	cd /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024 /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024 /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src /mnt/d/周宸源/大学/学习/程序/RISC-V-Simulator-2024/src/CMakeFiles/src.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/src.dir/depend

