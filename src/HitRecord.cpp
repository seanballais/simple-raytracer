#include "HitRecord.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

HitRecord::HitRecord() {}

HitRecord::HitRecord(Point3 p,
                     Vec3 outwardNormal,
                     std::shared_ptr<Material> materialPtr,
                     double t,
                     const Ray& incidentRay)
  : m_p(p)
  , m_materialPtr(materialPtr)
  , m_t(t)
{
  m_isNormalFrontFacing = dot(incidentRay.direction(), outwardNormal) < 0;
  m_normal = m_isNormalFrontFacing ? outwardNormal : -outwardNormal;
}

Point3 HitRecord::p() const
{
  return m_p;
}

Vec3 HitRecord::normal() const
{
  return m_normal;
}

std::shared_ptr<Material> HitRecord::materialPtr() const
{
  return m_materialPtr;
}

double HitRecord::t() const
{
  return m_t;
}

bool HitRecord::isNormalFrontFacing() const
{
  return m_isNormalFrontFacing;
}
