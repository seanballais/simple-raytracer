#ifndef RAYTRACING_HPP
#define RAYTRACING_HPP

#include "Hittable.hpp"
#include "vec3.hpp"
#include "ray.hpp"

Colour rayColour(const Ray& ray,
                 const Hittable& world,
                 const int& rayBounceDepth);

#endif
