#ifndef METAL_MATERIAL_HPP
#define METAL_MATERIAL_HPP

#include "HitRecord.hpp"
#include "Material.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class MetalMaterial : public Material
{
public:
  MetalMaterial(const Colour& albedo, const double fuzziness);

  virtual bool scatter(const Ray& rayIn,
                       const HitRecord& hitRecord,
                       Colour& attenuation,
                       Ray& scatteredRay) const override;

private:
  Colour m_albedo;
  double m_fuzziness;
};

#endif
