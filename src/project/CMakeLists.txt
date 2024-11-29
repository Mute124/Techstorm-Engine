set(PROJECT_SOURCES
	"project.cpp"
	"project.h"
)

# Project shared library. Change the name to whatever you want but be sure to change it in the Application's CMakeLists.txt file
add_library(project_lib SHARED ${PROJECT_SOURCES})

# Organize files in Visual Studio
foreach(source IN LISTS PROJECT_SOURCES)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

# Include directories
target_include_directories(project_lib PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(project_lib PRIVATE ${PROJECT_SOURCE_DIR}/src/engine)

# Link to the engine shared library
target_link_libraries(project_lib PUBLIC Techstorm )

# Set output name for Windows/Linux
if(WIN32)
    set_target_properties(project_lib PROPERTIES OUTPUT_NAME "project_lib.dll")
elseif(UNIX)
    set_target_properties(project_lib PROPERTIES OUTPUT_NAME "project_lib.so")
endif()


