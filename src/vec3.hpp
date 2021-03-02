#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

class Vec3
{
public:
  Vec3();
  Vec3(double x, double y, double z);

  double x() const;
  double y() const;
  double z() const;

  Vec3 operator+(const Vec3& v) const;
  Vec3 operator-() const;
  Vec3 operator-(const Vec3& v) const;
  Vec3 operator*(const Vec3& v) const;
  Vec3 operator*(const double k) const;
  Vec3 operator/(const double k) const;
  Vec3& operator+=(const Vec3 &v);
  Vec3& operator*=(const double k);
  Vec3& operator/=(const double k);

  double length() const;
  double length_squared() const;

private:
  double m_x;
  double m_y;
  double m_z;
};

inline std::ostream& operator<<(std::ostream& out, const Vec3 &v)
{
  return out << v.x() << " " << v.y() << " " << v.z();
}

inline Vec3 operator*(double k, const Vec3& v)
{
  return v * k;
}

using Point3 = Vec3;
using Colour = Vec3;

#endif
