#ifndef DIELECTRIC_MATERIAL_HPP
#define DIELECTRIC_MATERIAL_HPP

#include "HitRecord.hpp"
#include "Material.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class DielectricMaterial : public Material
{
public:
  DielectricMaterial(double refractionIndex);

  virtual bool scatter(const Ray& rayIn,
                       const HitRecord& hitRecord,
                       Colour& attenuation,
                       Ray& scatteredRay) const override;
private:
  double m_refractionIndex;
};

#endif