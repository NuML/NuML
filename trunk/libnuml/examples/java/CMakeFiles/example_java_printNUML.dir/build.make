# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dada/workspaces/libnuml

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dada/workspaces/libnuml

# Utility rule file for example_java_printNUML.

examples/java/CMakeFiles/example_java_printNUML: examples/java/printNUML.class

examples/java/printNUML.class: examples/java/printNUML.java
examples/java/printNUML.class: examples/java/../../src/bindings/java/local.i
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dada/workspaces/libnuml/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Build java example printNUML"
	cd /home/dada/workspaces/libnuml/examples/java && /home/dada/tools/jdk1.6.0_25/bin/javac -cp .:"/home/dada/workspaces/libnuml/examples/java/../../src/bindings/java/libnumlj.jar":/home/dada/workspaces/libnuml/examples/java /home/dada/workspaces/libnuml/examples/java/printNUML.java -source 1.5 -target 1.5 -d /home/dada/workspaces/libnuml/examples/java

example_java_printNUML: examples/java/CMakeFiles/example_java_printNUML
example_java_printNUML: examples/java/printNUML.class
example_java_printNUML: examples/java/CMakeFiles/example_java_printNUML.dir/build.make
.PHONY : example_java_printNUML

# Rule to build all files generated by this target.
examples/java/CMakeFiles/example_java_printNUML.dir/build: example_java_printNUML
.PHONY : examples/java/CMakeFiles/example_java_printNUML.dir/build

examples/java/CMakeFiles/example_java_printNUML.dir/clean:
	cd /home/dada/workspaces/libnuml/examples/java && $(CMAKE_COMMAND) -P CMakeFiles/example_java_printNUML.dir/cmake_clean.cmake
.PHONY : examples/java/CMakeFiles/example_java_printNUML.dir/clean

examples/java/CMakeFiles/example_java_printNUML.dir/depend:
	cd /home/dada/workspaces/libnuml && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dada/workspaces/libnuml /home/dada/workspaces/libnuml/examples/java /home/dada/workspaces/libnuml /home/dada/workspaces/libnuml/examples/java /home/dada/workspaces/libnuml/examples/java/CMakeFiles/example_java_printNUML.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/java/CMakeFiles/example_java_printNUML.dir/depend

