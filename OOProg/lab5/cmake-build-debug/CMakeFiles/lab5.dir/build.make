# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\programs\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\programs\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\79227\Desktop\susu_labs\OOProg\lab5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\79227\Desktop\susu_labs\OOProg\lab5\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\lab5.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\lab5.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\lab5.dir\flags.make

CMakeFiles\lab5.dir\main.cpp.obj: CMakeFiles\lab5.dir\flags.make
CMakeFiles\lab5.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\79227\Desktop\susu_labs\OOProg\lab5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab5.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\lab5.dir\main.cpp.obj /FdCMakeFiles\lab5.dir\ /FS -c C:\Users\79227\Desktop\susu_labs\OOProg\lab5\main.cpp
<<

CMakeFiles\lab5.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab5.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\lab5.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\79227\Desktop\susu_labs\OOProg\lab5\main.cpp
<<

CMakeFiles\lab5.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab5.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\lab5.dir\main.cpp.s /c C:\Users\79227\Desktop\susu_labs\OOProg\lab5\main.cpp
<<

# Object files for target lab5
lab5_OBJECTS = \
"CMakeFiles\lab5.dir\main.cpp.obj"

# External object files for target lab5
lab5_EXTERNAL_OBJECTS =

lab5.exe: CMakeFiles\lab5.dir\main.cpp.obj
lab5.exe: CMakeFiles\lab5.dir\build.make
lab5.exe: CMakeFiles\lab5.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\79227\Desktop\susu_labs\OOProg\lab5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab5.exe"
	"D:\programs\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\lab5.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\lab5.dir\objects1.rsp @<<
 /out:lab5.exe /implib:lab5.lib /pdb:C:\Users\79227\Desktop\susu_labs\OOProg\lab5\cmake-build-debug\lab5.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\lab5.dir\build: lab5.exe

.PHONY : CMakeFiles\lab5.dir\build

CMakeFiles\lab5.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lab5.dir\cmake_clean.cmake
.PHONY : CMakeFiles\lab5.dir\clean

CMakeFiles\lab5.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\79227\Desktop\susu_labs\OOProg\lab5 C:\Users\79227\Desktop\susu_labs\OOProg\lab5 C:\Users\79227\Desktop\susu_labs\OOProg\lab5\cmake-build-debug C:\Users\79227\Desktop\susu_labs\OOProg\lab5\cmake-build-debug C:\Users\79227\Desktop\susu_labs\OOProg\lab5\cmake-build-debug\CMakeFiles\lab5.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\lab5.dir\depend

