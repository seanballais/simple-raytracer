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
