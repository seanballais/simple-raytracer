#include <cmath>

#include "vec3.hpp"
#include "utils.hpp"

Vec3 getRandomPointInUnitSphere()
{
  while (true) {
    Vec3 p = getRandomVec3(-1.0, 1.0);
    if (p.length_squared() >= 1.0) {
      continue;
    }

    return p;
  }
}

Vec3 getRandomUnitVector()
{
  return unitVector(getRandomPointInUnitSphere());
}

Vec3 getRandomVectorInHemisphere(const Vec3& normal)
{
  Vec3 vecInUnitSphere = getRandomPointInUnitSphere();
  if (dot(vecInUnitSphere, normal) > 0.0) {
    return vecInUnitSphere;
  } else {
    return -vecInUnitSphere;
  }
}

Vec3 reflectVec3(const Vec3& v, const Vec3& normal)
{
  return v - (2 * dot(v, normal) * normal);
}

Vec3 refractVec3(const Vec3& uv, const Vec3& normal, double etaiOverEtat)
{
  double cosTheta = std::fmin(dot(-uv, normal), 1.0);
  Vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * normal);
  Vec3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.length_squared()))
                      * normal;
  return rOutPerp + rOutParallel;
}

double reflectance(double cosine, double refIdx)
{
  // Use Schlick's Approximation for reflectance.
  double r0 = (1 - refIdx) / (1 + refIdx);
  r0 = r0 * r0;
  return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5);
}
