#include <iostream>

#include "vec3.hpp"
#include "utils.hpp"

inline std::ostream& operator<<(std::ostream& out, const Vec3 &v)
{
  return out << v.x << " " << v.y << " " << v.z;
}

inline Vec3 operator*(double k, const Vec3& v)
{
  return v * k;
}

inline double dot(const Vec3& u, const Vec3& v)
{
  return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
  return Vec3((u.y * v.z) - (u.z * v.y),
              (u.z * v.x) - (u.x * v.z),
              (u.x * v.y) - (u.y * v.x));
}

inline Vec3 unitVector(const Vec3& v)
{
  return v / v.length();
}
