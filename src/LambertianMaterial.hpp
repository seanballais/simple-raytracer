#ifndef LAMBERTIAN_MATERIAL_HPP
#define LAMBERTIAN_MATERIAL_HPP

#include "HitRecord.hpp"
#include "Material.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class LambertianMaterial : public Material
{
public:
  LambertianMaterial(const Colour& albedo);

  Colour albedo() const;

  virtual bool scatter(const Ray& rayIn,
                       const HitRecord& hitRecord,
                       Colour& attenuation,
                       Ray& scatteredRay) const override;
private:
  Colour m_albedo;
};

#endif
