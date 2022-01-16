#include "HitRecord.hpp"
#include "MetalMaterial.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

MetalMaterial::MetalMaterial(const Colour& albedo, const double fuzziness)
  : m_albedo(albedo)
  , m_fuzziness(fuzziness) {}

bool MetalMaterial::scatter(const Ray& rayIn,
                            const HitRecord& hitRecord,
                            Colour& attenuation,
                            Ray& scatteredRay) const
{
  Vec3 reflectedRay = reflectVec3(unitVector(rayIn.direction()),
                                  hitRecord.normal());
  scatteredRay = Ray(hitRecord.p(),
                     reflectedRay
                     + (m_fuzziness * getRandomPointInUnitSphere()));
  attenuation = m_albedo;

  return dot(scatteredRay.direction(), hitRecord.normal()) > 0.0;
}
