#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "HitRecord.hpp"
#include "ray.hpp"

class Hittable
{
public:
  virtual bool
  hit(const Ray& ray, double tMin, double tMax, HitRecord record) const = 0;
};

#endif
