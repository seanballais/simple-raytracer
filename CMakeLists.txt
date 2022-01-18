cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_COMPILER   "clang-11")
set(CMAKE_CXX_COMPILER "clang++-11")

project(simple-raytracer)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Mhmm. We're sticking with just Clang. Note that -stdlib is a Clang-only flag.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++")

add_library(rt-libs
    src/Camera.cpp
    src/colour.cpp
    src/constants.hpp
    src/DielectricMaterial.cpp
    src/HitRecord.cpp
    src/Hittable.hpp
    src/HittableList.cpp
    src/LambertianMaterial.cpp
    src/Material.hpp
    src/MetalMaterial.cpp
    src/Sphere.cpp
    src/stb_image_write.h
    src/ray.cpp
    src/raytracing.cpp
    src/RenderedChunk.hpp
    src/RenderThread.cpp
    src/utils.cpp
    src/vec3.cpp
)

add_executable(main
    src/main.cpp
)

target_link_libraries(main
    rt-libs
    Threads::Threads
)
