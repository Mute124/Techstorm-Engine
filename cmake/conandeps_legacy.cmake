message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(ZLIB)
find_package(joltphysics)

set(CONANDEPS_LEGACY  ZLIB::ZLIB  joltphysics::joltphysics )