#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdlib>

#include "constants.hpp"
#include "vec3.hpp"

inline double dot(const Vec3& u, const Vec3& v)
{
  return (u.x() * v.x()) + (u.y() * v.y()) + (u.z() * v.z());
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
  return Vec3((u.y() * v.z()) - (u.z() * v.y()),
              (u.z() * v.x()) - (u.x() * v.z()),
              (u.x() * v.y()) - (u.y() * v.x()));
}

inline Vec3 unitVector(const Vec3& v)
{
  return v / v.length();
}

inline double degToRad(double degrees)
{
  return (degrees * pi) / 180.0;
}

inline double randomDouble(double min, double max)
{
  return min + (max - min) * (std::rand() / (RAND_MAX + 1.0));
}

inline double randomDouble()
{
  return randomDouble(0.0, 1.0);
}

inline double clamp(double x, double min, double max)
{
  if (x < min) {
    return min;
  } else if (x > max) {
    return max;
  }

  return x;
}

inline Vec3 getRandomVec3()
{
  return Vec3(randomDouble(), randomDouble(), randomDouble());
}

inline Vec3 getRandomVec3(double min, double max)
{
  return Vec3(randomDouble(min, max),
              randomDouble(min, max),
              randomDouble(min, max));
}

Vec3 getRandomPointInUnitSphere();
Vec3 getRandomUnitVector();
Vec3 getRandomVectorInHemisphere(const Vec3& normal);

#endif
