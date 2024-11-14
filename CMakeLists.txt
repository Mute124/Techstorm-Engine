cmake_minimum_required(VERSION 3.29)
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
# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
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

# Download and include CPM.cmake
#if(NOT CPM_LOADED)
#    set(CPM_DOWNLOAD_VERSION 0.38.0)
#    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/CPM.cmake")
#    if(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
#        file(DOWNLOAD https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
#             ${CPM_DOWNLOAD_LOCATION})
#    endif()
#    include(${CPM_DOWNLOAD_LOCATION})
#endif()


if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
# Set project name
project(TechStorm LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(cmake/cpm.cmake)
include(cmake/techstorm.cmake)
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
option(WIN32_LEAN_AND_MEAN ON)

if (NOT result EQUAL 0)
    find_package(ZLIB)
    find_package(joltphysics)
    find_package(libconfig)
    find_package(Angelscript)
    find_package(sol2)

set(DOUBLE_PRECISION OFF)
set(GENERATE_DEBUG_SYMBOLS OFF)
set(CROSS_PLATFORM_DETERMINISTIC ON)
set(FLOATING_POINT_EXCEPTIONS_ENABLED OFF)
set(OBJECT_LAYER_BITS 32)
set(USE_SSE4_1 ON)
set(USE_SSE4_2 ON)
set(USE_AVX ON)
set(USE_AVX2 ON)
set(USE_AVX512 OFF)
set(USE_LZCNT ON)
set(USE_TZCNT ON)
set(USE_F16C ON)
set(USE_FMADD ON)
set(BUILD_SHARED_LIBS ON)


# Include subdirectories
add_subdirectory(src/engine)
add_subdirectory(src/project)
add_subdirectory(src/application)
add_subdirectory(src/tools)


