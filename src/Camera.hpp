#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"
#include "vec3.hpp"

class Camera
{
public:
  Camera();

  Ray getRay(double u, double v) const;

private:
  Point3 m_origin;
  Point3 m_lowerLeftCorner;
  Vec3 m_horizontalLength;
  Vec3 m_verticalHeight;
};

#endif
