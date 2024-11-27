# Project shared library. Change the name to whatever you want
add_library(project_lib SHARED project.cpp "project.h")
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


