#include <cmath>
#include <memory>

#include "HitRecord.hpp"
#include "Hittable.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "utils.hpp"

Sphere::Sphere() {}

Sphere::Sphere(Point3 centerPoint,
               double radius,
               std::shared_ptr<Material> material)
  : m_centerPoint(centerPoint)
  , m_radius(radius)
  , m_materialPtr(material) {}

bool
Sphere::hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
{
  Vec3 rayOriginToSphereCenter = ray.origin() - m_centerPoint;
  double a = ray.direction().length_squared();
  double halfB = dot(rayOriginToSphereCenter, ray.direction());
  double c = rayOriginToSphereCenter.length_squared() - (m_radius * m_radius);

  double discriminant = (halfB * halfB) - (a * c);
  if (discriminant < 0) {
    return false;
  }

  double squaredDiscrim = std::sqrt(discriminant);

  // Find the nearest t that lies in the acceptable range.
  double t = (-halfB - squaredDiscrim) / a;
  if (t < tMin || tMax < t) {
    t = (-halfB + squaredDiscrim) / a;
    if (t < tMin || tMax < t) {
      return false;
    }
  }

  Point3 intersectionPoint = ray.at(t);
  Vec3 outwardNormal = (intersectionPoint - m_centerPoint) / m_radius;
  record = HitRecord(intersectionPoint, outwardNormal, m_materialPtr, t, ray);

  return true;
}

Point3 Sphere::centerPoint() const
{
  return m_centerPoint;
}

double Sphere::radius() const
{
  return m_radius;
}

std::shared_ptr<Material> Sphere::material() const
{
  return m_materialPtr;
}
