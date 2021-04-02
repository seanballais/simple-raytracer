#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <memory>

#include "HitRecord.hpp"
#include "Hittable.hpp"
#include "Material.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Sphere : public Hittable
{
public:
  Sphere();
  Sphere(Point3 centerPoint, double radius, std::shared_ptr<Material> material);

  virtual bool hit(const Ray& ray,
                   double tMin,
                   double tMax,
                   HitRecord& record) const override;

  Point3 centerPoint() const;
  double radius() const;
  std::shared_ptr<Material> material() const;

private:
  Point3 m_centerPoint;
  double m_radius;
  std::shared_ptr<Material> m_materialPtr;
};

#endif
