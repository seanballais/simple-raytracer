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
  HitRecord hitRecord;

  if (rayBounceDepth <= 0) {
    // We have exceeded the ray bounce limit. No more light is gathered.
    return Colour(0.0, 0.0, 0.0);
  }

  if (world.hit(ray, 0.001, infinity, hitRecord)) {
    Ray scatteredRay;
    Colour attenuation;
    if (hitRecord.materialPtr()->scatter(ray,
                                         hitRecord,
                                         attenuation,
                                         scatteredRay)) {
      return attenuation * rayColour(scatteredRay, world, rayBounceDepth - 1);
    }

    return Colour(0.0, 0.0, 0.0);
  }

  Vec3 unitDirection = unitVector(ray.direction());
  double t = 0.5 * (unitDirection.y() + 1.0);
  return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}
