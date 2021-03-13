#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "HitRecord.hpp"
#include "Hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Sphere : public Hittable
{
public:
  Sphere();
  Sphere(Point3 centerPoint, double radius);

  virtual bool hit(const Ray& ray,
                   double tMin,
                   double tMax,
                   HitRecord& record) const override;

  Point3 centerPoint() const;
  double radius() const;

private:
  Point3 m_centerPoint;
  double m_radius;
};

#endif
