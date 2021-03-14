#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

class HitRecord
{
public:
  HitRecord();
  HitRecord(Point3 p, Vec3 outwardNormal, double t, const Ray& incidentRay);

  Point3 p();
  Vec3 normal();
  double t();
  bool isNormalFrontFacing();

private:
  Point3 m_p;
  Vec3 m_normal;
  double m_t;
  bool m_isNormalFrontFacing;
};

#endif
