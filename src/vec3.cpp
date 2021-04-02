#include <cmath>
#include <iostream>

#include "vec3.hpp"

Vec3::Vec3() : m_x(0.0), m_y(0.0), m_z(0.0) {}

Vec3::Vec3(double x, double y, double z)
  : m_x(x), m_y(y), m_z(z) {}

double Vec3::x() const
{
  return m_x;
}

double Vec3::y() const
{
  return m_y;
}

double Vec3::z() const
{
  return m_z;
}

Vec3 Vec3::operator+(const Vec3& v) const
{
  return Vec3(m_x + v.x(), m_y + v.y(), m_z + v.z());
}

Vec3 Vec3::operator-() const
{
  return Vec3(-m_x, -m_y, -m_z);
}

Vec3 Vec3::operator-(const Vec3& v) const
{
  return Vec3(m_x - v.x(), m_y - v.y(), m_z - v.z());
}

Vec3 Vec3::operator*(const Vec3& v) const
{
  return Vec3(m_x * v.x(), m_y * v.y(), m_z * v.z());
}

Vec3 Vec3::operator*(const double k) const
{
  return Vec3(m_x * k, m_y * k, m_z * k);
}

Vec3 Vec3::operator/(const double k) const
{
  return *this * (1 / k);
}

Vec3& Vec3::operator+=(const Vec3 &v)
{
  m_x += v.x();
  m_y += v.y();
  m_z += v.z();

  return *this;
}

Vec3& Vec3::operator*=(const double k)
{
  m_x *= k;
  m_y *= k;
  m_z *= k;

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
  return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}

bool Vec3::isNearZero() const
{
  constexpr double zeroThreshold = 1e-8;
  return (std::fabs(m_x) < zeroThreshold)
         && (std::fabs(m_y) < zeroThreshold)
         && (std::fabs(m_z) < zeroThreshold);
}
