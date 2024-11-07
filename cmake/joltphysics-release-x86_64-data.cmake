########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(joltphysics_COMPONENT_NAMES "")
if(DEFINED joltphysics_FIND_DEPENDENCY_NAMES)
  list(APPEND joltphysics_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES joltphysics_FIND_DEPENDENCY_NAMES)
else()
  set(joltphysics_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(joltphysics_PACKAGE_FOLDER_RELEASE "C:/Users/HP/.conan2/p/joltp891272d36cf13/p")
set(joltphysics_BUILD_MODULES_PATHS_RELEASE )


set(joltphysics_INCLUDE_DIRS_RELEASE "${joltphysics_PACKAGE_FOLDER_RELEASE}/include")
set(joltphysics_RES_DIRS_RELEASE )
set(joltphysics_DEFINITIONS_RELEASE "-DJPH_USE_SSE4_1"
			"-DJPH_USE_SSE4_2")
set(joltphysics_SHARED_LINK_FLAGS_RELEASE )
set(joltphysics_EXE_LINK_FLAGS_RELEASE )
set(joltphysics_OBJECTS_RELEASE )
set(joltphysics_COMPILE_DEFINITIONS_RELEASE "JPH_USE_SSE4_1"
			"JPH_USE_SSE4_2")
set(joltphysics_COMPILE_OPTIONS_C_RELEASE )
set(joltphysics_COMPILE_OPTIONS_CXX_RELEASE )
set(joltphysics_LIB_DIRS_RELEASE "${joltphysics_PACKAGE_FOLDER_RELEASE}/lib")
set(joltphysics_BIN_DIRS_RELEASE )
set(joltphysics_LIBRARY_TYPE_RELEASE STATIC)
set(joltphysics_IS_HOST_WINDOWS_RELEASE 1)
set(joltphysics_LIBS_RELEASE Jolt)
set(joltphysics_SYSTEM_LIBS_RELEASE )
set(joltphysics_FRAMEWORK_DIRS_RELEASE )
set(joltphysics_FRAMEWORKS_RELEASE )
set(joltphysics_BUILD_DIRS_RELEASE )
set(joltphysics_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(joltphysics_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${joltphysics_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${joltphysics_COMPILE_OPTIONS_C_RELEASE}>")
set(joltphysics_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${joltphysics_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${joltphysics_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${joltphysics_EXE_LINK_FLAGS_RELEASE}>")


set(joltphysics_COMPONENTS_RELEASE )