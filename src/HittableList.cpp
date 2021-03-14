#include <memory>

#include "HitRecord.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"

HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
  add(object);
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
  m_objects.push_back(object);
}

void HittableList::clear()
{
  m_objects.clear();
}

std::vector<std::shared_ptr<Hittable>>& HittableList::getObjects()
{
  return m_objects;
}

bool
HittableList::hit(const Ray& ray,
                  double tMin,
                  double tMax,
                  HitRecord& record) const
{
  HitRecord tempRecord;
  bool hasHitSomething = false;
  double closestTSoFar = tMax;

  for (const auto& object : m_objects) {
    if (object->hit(ray, tMin, closestTSoFar, tempRecord)) {
      hasHitSomething = true;
      closestTSoFar = tempRecord.t();
      record = tempRecord;
    }
  }

  return hasHitSomething;
}
