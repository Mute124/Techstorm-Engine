# Application: Main executable
add_executable(main_app "main.cpp")

# Link to the project shared library
target_link_libraries(main_app PRIVATE project_lib)

# Include directories
target_include_directories(main_app PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(main_app PRIVATE ${PROJECT_SOURCE_DIR}/src/project)
