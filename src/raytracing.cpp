#include <cmath>

#include "constants.hpp"
#include "Hittable.hpp"
#include "ray.hpp"
#include "raytracing.hpp"
#include "utils.hpp"
#include "vec3.hpp"

Colour rayColour(const Ray& ray,
                 const Hittable& world,
                 const int& rayBounceDepth)
{
  // TODO: Figure out why the spheres are not light grey.
  HitRecord hitRecord;

  if (rayBounceDepth <= 0) {
    // We have exceeded the ray bounce limit. No more light is gathered.
    return Colour(0.0, 0.0, 0.0);
  }

  if (world.hit(ray, 0.0, infinity, hitRecord)) {
    Point3 target = hitRecord.p()
                    + hitRecord.normal()
                    + getRandomPointInUnitSphere();
    return 0.5 * rayColour(
      Ray(hitRecord.p(), target - hitRecord.p()), world, rayBounceDepth - 1);
  }

  Vec3 unitDirection = unitVector(ray.direction());
  double t = 0.5 * (unitDirection.y() + 1.0);
  return ((1.0 - t) * Colour(1.0, 1.0, 1.0)) + (t * Colour(0.5, 0.7, 1.0));
}
