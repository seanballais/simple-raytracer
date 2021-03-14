#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

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

inline double randomDouble()
{
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
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

#endif
