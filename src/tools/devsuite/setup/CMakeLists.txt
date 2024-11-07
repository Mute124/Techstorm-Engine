# Application: Main executable
add_executable(setup_app "main.cpp")

find_package(argh REQUIRED)

# Include directories
target_include_directories(setup_app PRIVATE ${PROJECT_SOURCE_DIR}/include)
#target_include_directories(setup_app PRIVATE ${PROJECT_SOURCE_DIR}/src/project)
target_link_libraries(setup_app PRIVATE argh argh_DEPS_TARGET)
