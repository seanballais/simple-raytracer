#include <cmath>

#include "constants.hpp"
#include "Hittable.hpp"
#include "ray.hpp"
#include "raytracing.hpp"
#include "utils.hpp"
#include "vec3.hpp"

Colour rayColour(const Ray& ray, const Hittable& world)
{
  HitRecord hitRecord;
  if (world.hit(ray, 0.0, infinity, hitRecord)) {
    return 0.5 * (hitRecord.normal() + Colour(1.0, 1.0, 1.0));
  }

  Vec3 unitDirection = unitVector(ray.direction());
  double t = 0.5 * (unitDirection.y() + 1.0);

  return ((1.0 - t) * Colour(1.0, 1.0, 1.0)) + (t * Colour(0.5, 0.7, 1.0));
}
