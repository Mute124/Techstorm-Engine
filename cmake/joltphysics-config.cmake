########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(joltphysics_FIND_QUIETLY)
    set(joltphysics_MESSAGE_MODE VERBOSE)
else()
    set(joltphysics_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/joltphysicsTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${joltphysics_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(joltphysics_VERSION_STRING "3.0.1")
set(joltphysics_INCLUDE_DIRS ${joltphysics_INCLUDE_DIRS_RELEASE} )
set(joltphysics_INCLUDE_DIR ${joltphysics_INCLUDE_DIRS_RELEASE} )
set(joltphysics_LIBRARIES ${joltphysics_LIBRARIES_RELEASE} )
set(joltphysics_DEFINITIONS ${joltphysics_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${joltphysics_BUILD_MODULES_PATHS_RELEASE} )
    message(${joltphysics_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


