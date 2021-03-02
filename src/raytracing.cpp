#include "ray.hpp"
#include "raytracing.hpp"
#include "utils.hpp"
#include "vec3.hpp"

bool isSphereHit(const Point3& center, double radius, const Ray& ray)
{
  Vec3 rayOriginToSphereCenter = ray.origin() - center;
  double a = dot(ray.direction(), ray.direction());
  double b = 2.0 * dot(ray.direction(), rayOriginToSphereCenter);
  double c = dot(rayOriginToSphereCenter, rayOriginToSphereCenter)
             - (radius * radius);
  double discriminant = (b * b) - (4 * a * c);
  return (discriminant > 0);
}

Colour rayColour(const Ray& ray)
{
  if (isSphereHit(Point3(0.0, 0.0, -1.0), 0.5, ray)) {
    return Colour(1.0, 0.0, 0.0);
  }

  Vec3 unitDir = unitVector(ray.direction());
  double t = 0.5 * (unitDir.y() + 1.0);

  return (1.0 - t) * Colour(1.0, 1.0, 1.0) + (t * Colour(0.5, 0.7, 1.0));
}
