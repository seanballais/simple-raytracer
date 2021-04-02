#include "HitRecord.hpp"
#include "LambertianMaterial.hpp"
#include "Material.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

LambertianMaterial::LambertianMaterial(const Colour& albedo)
  : m_albedo(albedo) {}

Colour LambertianMaterial::albedo() const
{
  return m_albedo;
}

bool LambertianMaterial::scatter(const Ray& rayIn,
                                 const HitRecord& hitRecord,
                                 Colour& attenuation,
                                 Ray& scatteredRay) const
{
  Vec3 scatterDirection = hitRecord.normal() + getRandomUnitVector();

  // Catch degenerate scatter direction.
  if (scatterDirection.isNearZero()) {
    scatterDirection = hitRecord.normal();
  }

  scatteredRay = Ray(hitRecord.p(), scatterDirection);
  attenuation = m_albedo;

  return true;
}