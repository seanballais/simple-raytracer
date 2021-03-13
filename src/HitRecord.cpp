#include "HitRecord.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

HitRecord::HitRecord(Point3 p,
                     Vec3 outwardNormal,
                     double t,
                     const Ray& incidentRay)
  : m_p(p)
  , m_t(t)
{
  m_isNormalFrontFacing = dot(incidentRay.direction(), outwardNormal) < 0;
  m_normal = m_isNormalFrontFacing ? outwardNormal : -outwardNormal;
}

Point3 HitRecord::p()
{
  return m_p;
}

Vec3 HitRecord::normal()
{
  return m_normal;
}

double HitRecord::t()
{
  return m_t;
}

bool HitRecord::isNormalFrontFacing()
{
  return m_isNormalFrontFacing;
}
