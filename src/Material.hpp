#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "colour.hpp"
#include "ray.hpp"

// If we include the HitRecord class, we'd get a circular dependency.
class HitRecord;

class Material
{
public:
  virtual bool scatter(const Ray& rayIn,
                       const HitRecord& hitRecord,
                       Colour& attenuation,
                       Ray& scatteredRay) const = 0;
};

#endif
