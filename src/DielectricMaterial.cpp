#include <cmath>

#include "DielectricMaterial.hpp"
#include "HitRecord.hpp"
#include "Material.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

DielectricMaterial::DielectricMaterial(double refractionIndex)
  : m_refractionIndex(refractionIndex) {}

bool DielectricMaterial::scatter(const Ray& rayIn,
                                 const HitRecord& hitRecord,
                                 Colour& attenuation,
                                 Ray& scatteredRay) const
{
  attenuation = Colour(1.0, 1.0, 1.0);
  double refractionRatio = hitRecord.isNormalFrontFacing()
    ? (1.0 / m_refractionIndex)
    : m_refractionIndex;

  Vec3 unitDirection = unitVector(rayIn.direction());
  double cosTheta = std::fmin(dot(-unitDirection, hitRecord.normal()), 1.0);
  double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

  bool isCannotRefract = (refractionRatio * sinTheta) > 1.0;
  Vec3 direction;

  if (isCannotRefract
      || reflectance(cosTheta, refractionRatio) > randomDouble()) {
    direction = reflectVec3(unitDirection, hitRecord.normal());
  } else {
    direction = refractVec3(unitDirection, hitRecord.normal(), refractionRatio);
  }

  scatteredRay = Ray(hitRecord.p(), direction);

  return true;
}
