#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include <memory>

#include "Material.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class HitRecord
{
public:
  HitRecord();
  HitRecord(Point3 p,
            Vec3 outwardNormal,
            std::shared_ptr<Material> materialPtr,
            double t,
            const Ray& incidentRay);

  Point3 p() const;
  Vec3 normal() const;
  std::shared_ptr<Material> materialPtr() const;
  double t() const;
  bool isNormalFrontFacing() const;

private:
  Point3 m_p;
  Vec3 m_normal;
  std::shared_ptr<Material> m_materialPtr;
  double m_t;
  bool m_isNormalFrontFacing;
};

#endif
