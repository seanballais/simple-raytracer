#include "Camera.hpp"
#include "ray.hpp"
#include "vec3.hpp"

Camera::Camera()
{
  double aspectRatio = 16.0 / 9.0;
  double viewportHeight = 2.0;
  double viewportWidth = aspectRatio * viewportHeight;
  double focalLength = 1.0;

  m_origin = Point3(0.0, 0.0, 0.0);
  m_horizontalLength = Vec3(viewportWidth, 0.0, 0.0);
  m_verticalHeight = Vec3(0.0, viewportHeight, 0.0);
  m_lowerLeftCorner = ((m_origin - m_horizontalLength) / 2)
                      - (m_verticalHeight / 2)
                      - Vec3(0.0, 0.0, focalLength);
}

Ray Camera::getRay(double u, double v) const
{
  return Ray(m_origin,
             m_lowerLeftCorner
             + (u * m_horizontalLength)
             + (v * m_verticalHeight)
             - m_origin);
}
