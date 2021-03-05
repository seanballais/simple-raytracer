#include <cmath>

#include "ray.hpp"
#include "raytracing.hpp"
#include "utils.hpp"
#include "vec3.hpp"

double sphereHitLocation(const Point3& center, double radius, const Ray& ray)
{
  Vec3 rayOriginToSphereCenter = ray.origin() - center;
  double a = ray.direction().length_squared();
  double halfB = dot(ray.direction(), rayOriginToSphereCenter);
  double c = rayOriginToSphereCenter.length_squared() - (radius * radius);
  double discriminant = (halfB * halfB) - (a * c);
  if (discriminant < 0.0) {
    return -1.0;
  } else {
    return (-halfB - std::sqrt(discriminant)) / a;
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
