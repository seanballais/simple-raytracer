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
