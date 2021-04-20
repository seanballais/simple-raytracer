#include <cmath>

#include "Camera.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

Camera::Camera(Point3 lookFrom,
               Point3 lookAt,
               Vec3 viewUp,
               double verticalFOV,
               double aspectRatio)
{
  double theta = degToRad(verticalFOV);
  double h = std::tan(theta / 2);
  double viewportHeight = 2.0 * h;
  double viewportWidth = aspectRatio * viewportHeight;
  double focalLength = 1.0;

  Vec3 w = unitVector(lookFrom - lookAt);
  Vec3 u = unitVector(cross(viewUp, w));
  Vec3 v = cross(w, u);

  m_origin = lookFrom;
  m_horizontalLength = viewportWidth * u;
  m_verticalHeight = viewportHeight * v;
  m_lowerLeftCorner = m_origin
                      - (m_horizontalLength / 2)
                      - (m_verticalHeight / 2)
                      - w;
}

Ray Camera::getRay(double s, double t) const
{
  return Ray(m_origin,
             m_lowerLeftCorner
             + (s * m_horizontalLength)
             + (t * m_verticalHeight)
             - m_origin);
}
