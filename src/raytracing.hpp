#ifndef RAYTRACING_HPP
#define RAYTRACING_HPP

#include "vec3.hpp"
#include "ray.hpp"

double sphereHitLocation(const Point3& center, double radius, const Ray& ray);
Colour rayColour(const Ray& ray);

#endif
