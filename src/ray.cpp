#include "ray.hpp"
#include "vec3.hpp"

Ray::Ray() {}

Ray::Ray(const Point3& origin, const Vec3& direction)
  : m_origin(origin), m_direction(direction) {}

Point3 Ray::origin() const
{
  return m_origin;
}

Vec3 Ray::direction() const
{
  return m_direction;
}

Point3 Ray::at(double t) const
{
  return m_origin + (t * m_direction);
}
