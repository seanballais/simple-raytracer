#include <cmath>

#include "ray.hpp"
#include "raytracing.hpp"
#include "utils.hpp"
#include "vec3.hpp"

double sphereHitLocation(const Point3& center, double radius, const Ray& ray)
{
  Vec3 rayOriginToSphereCenter = ray.origin() - center;
  double a = dot(ray.direction(), ray.direction());
  double b = 2.0 * dot(ray.direction(), rayOriginToSphereCenter);
  double c = dot(rayOriginToSphereCenter, rayOriginToSphereCenter)
             - (radius * radius);
  double discriminant = (b * b) - (4 * a * c);
  if (discriminant < 0.0) {
    return -1.0;
  } else {
    return (-b - std::sqrt(discriminant)) / (2.0 * a);
  }
}

Colour rayColour(const Ray& ray)
{
  double t = sphereHitLocation(Point3(0.0, 0.0, -1.0), 0.5, ray);
  if (t > 0.0) {
    // Ray has hit a sphere.
    Vec3 normalVec = unitVector(ray.at(t) - Vec3(0.0, 0.0, -1.0));
    return 0.5 * Colour(normalVec.x() + 1,
                        normalVec.y() + 1,
                        normalVec.z() + 1);
  } else {
    // Ray did not hit the sphere.
    Vec3 unitDir = unitVector(ray.direction());
    t = 0.5 * (unitDir.y() + 1.0);

    return (1.0 - t) * Colour(1.0, 1.0, 1.0) + (t * Colour(0.5, 0.7, 1.0));
  }
}
