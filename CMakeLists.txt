cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_COMPILER   "clang-11")
set(CMAKE_CXX_COMPILER "clang++-11")

project(simple-raytracer)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Mhmm. We're sticking with just Clang. Note that -stdlib is a Clang-only flag.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++")

add_library(rt-libs
    src/colour.cpp
    src/ray.cpp
    src/vec3.cpp
    src/utils.cpp
)

add_executable(ppm-generator
    src/ppm_generator.cpp
)

target_link_libraries(ppm-generator
    rt-libs
)
