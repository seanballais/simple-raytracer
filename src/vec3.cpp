#include <cmath>

#include "vec3.hpp"

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x, double y, double z)
  : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& v) const
{
  return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-() const
{
  return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator-(const Vec3& v) const
{
  return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(const Vec3& v) const
{
  return Vec3(x * v.x, y * v.y, z * v.z);
}

Vec3 Vec3::operator*(const double k) const
{
  return Vec3(x * k, y * k, z * k);
}

Vec3 Vec3::operator/(const double k) const
{
  return *this * (1 / k);
}

Vec3& Vec3::operator+=(const Vec3 &v)
{
  x += v.x;
  y += v.y;
  z += v.z;

  return *this;
}

Vec3& Vec3::operator*=(const double k)
{
  x *= k;
  y *= k;
  z *= k;

  return *this;
}

Vec3& Vec3::operator/=(const double k)
{
  // TODO: Write a blog post on what I have learned regarding this line, where:
  //         return *this * (1.0 / k)
  //       is invalid, but the line below is valid.
  return *this *= (1.0 / k);
}

double Vec3::length() const
{
  return std::sqrt(length_squared());
}

double Vec3::length_squared() const
{
  return (x * x) + (y * y) + (z * z);
}
