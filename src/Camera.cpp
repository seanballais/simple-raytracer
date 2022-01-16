#include <cmath>

#include "Camera.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

Camera::Camera(Point3 lookFrom,
               Point3 lookAt,
               Vec3 viewUp,
               double verticalFOV,
               double aspectRatio,
               double aperture,
               double focusDistance)
{
  double theta = degToRad(verticalFOV);
  double h = std::tan(theta / 2);
  double viewportHeight = 2.0 * h;
  double viewportWidth = aspectRatio * viewportHeight;

  m_w = unitVector(lookFrom - lookAt);
  m_u = unitVector(cross(viewUp, m_w));
  m_v = cross(m_w, m_u);

  m_origin = lookFrom;
  m_horizontalLength = focusDistance * viewportWidth * m_u;
  m_verticalHeight = focusDistance * viewportHeight * m_v;
  m_lowerLeftCorner = m_origin
                      - (m_horizontalLength / 2)
                      - (m_verticalHeight / 2)
                      - (focusDistance * m_w);

  m_lensRadius = aperture / 2;
}

Ray Camera::getRay(double s, double t) const
{
  Vec3 rd = m_lensRadius * getRandomVectorInUnitDisk();
  Vec3 offset = m_u * rd.x() + m_v * rd.y();

  return Ray(m_origin + offset,
             m_lowerLeftCorner
             + (s * m_horizontalLength)
             + (t * m_verticalHeight)
             - m_origin - offset);
}
