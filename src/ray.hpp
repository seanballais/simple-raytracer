#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class Ray
{
public:
  Ray();
  Ray(const Point3& origin, const Vec3& direction);

  Point3 origin() const;
  Vec3 direction() const;
  Point3 at(double t) const;

private:
  Point3 m_origin;
  Vec3 m_direction;
};

#endif
