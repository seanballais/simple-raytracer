#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "Hittable.hpp"

class HittableList : public Hittable
{
public:
  HittableList();
  HittableList(std::shared_ptr<Hittable> object);

  void add(std::shared_ptr<Hittable> object);
  void clear();
  std::vector<std::shared_ptr<Hittable>>& getObjects();

  virtual bool hit(const Ray& ray,
                   double tMin,
                   double tMax,
                   HitRecord& record) const override;

private:
  std::vector<std::shared_ptr<Hittable>> m_objects;
};

#endif
