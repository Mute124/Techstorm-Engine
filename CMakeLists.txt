cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The configurations we support
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Distribution")

# Set project name
project(TechStorm LANGUAGES CXX)

include(cmake/cpm.cmake)
#set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Distribution")
# Force the use of the same runtime library

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
CPMAddPackage(
    NAME raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
) 

CPMAddPackage(
    NAME ImGui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG v1.91.2
)

CPMADDPACKAGE(
    NAME eventpp
    GIT_REPOSITORY https://github.com/wqking/eventpp.git
    GIT_TAG v0.1.3
)

CPMADDPACKAGE(
    NAME JoltPhysics
    GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
    GIT_TAG v5.1.0
    OPTIONS "BUILD_SHARED_LIBS=ON" "GENERATE_DEBUG_SYMBOLS=ON" "OVERRIDE_CXX_FLAGS=ON"
)


# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Static libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Shared libraries (.so/.dll)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Executables (.out/.exe)

# Platform-specific settings
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)  # To export symbols from DLLs
    set(CMAKE_RUNTIME_OUTPUT_NAME_SUFFIX ".exe")
elseif(UNIX)
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif()

# Set linker flags
#set(CMAKE_EXE_LINKER_FLAGS_DISTRIBUTION "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
#set(JPH_SOURCE ${JoltPhysics_SOURCE_DIR})
# Include subdirectories


add_subdirectory(src/application)
add_subdirectory(src/project)
add_subdirectory(src/engine)
add_subdirectory(src/tools)
