#ifndef VEC3_HPP
#define VEC3_HPP

class Vec3
{
  public:
    double x;
    double y;
    double z;

    Vec3();
    Vec3(double x, double y, double z);

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
};

using Point3 = Vec3;
using Colour = Vec3;

#endif
