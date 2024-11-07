# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(joltphysics_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(joltphysics_FRAMEWORKS_FOUND_RELEASE "${joltphysics_FRAMEWORKS_RELEASE}" "${joltphysics_FRAMEWORK_DIRS_RELEASE}")

set(joltphysics_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET joltphysics_DEPS_TARGET)
    add_library(joltphysics_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET joltphysics_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${joltphysics_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${joltphysics_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### joltphysics_DEPS_TARGET to all of them
conan_package_library_targets("${joltphysics_LIBS_RELEASE}"    # libraries
                              "${joltphysics_LIB_DIRS_RELEASE}" # package_libdir
                              "${joltphysics_BIN_DIRS_RELEASE}" # package_bindir
                              "${joltphysics_LIBRARY_TYPE_RELEASE}"
                              "${joltphysics_IS_HOST_WINDOWS_RELEASE}"
                              joltphysics_DEPS_TARGET
                              joltphysics_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "joltphysics"    # package_name
                              "${joltphysics_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${joltphysics_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET joltphysics::joltphysics
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${joltphysics_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${joltphysics_LIBRARIES_TARGETS}>
                 )

    if("${joltphysics_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET joltphysics::joltphysics
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     joltphysics_DEPS_TARGET)
    endif()

    set_property(TARGET joltphysics::joltphysics
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${joltphysics_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET joltphysics::joltphysics
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${joltphysics_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET joltphysics::joltphysics
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${joltphysics_LIB_DIRS_RELEASE}>)
    set_property(TARGET joltphysics::joltphysics
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${joltphysics_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET joltphysics::joltphysics
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${joltphysics_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(joltphysics_LIBRARIES_RELEASE joltphysics::joltphysics)
