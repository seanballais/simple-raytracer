#include <cmath>

#include "colour.hpp"
#include "utils.hpp"
#include "vec3.hpp"

void writeColour(std::ostream& out, Colour pixelColour, int numSamplesPerPixel)
{
  double r = pixelColour.x();
  double g = pixelColour.y();
  double b = pixelColour.z();

  // Divide the colour by the number of samples.
  double scale = 1.0 / numSamplesPerPixel;
  r = std::sqrt(scale * r);
  g = std::sqrt(scale * g);
  b = std::sqrt(scale * b);

  out << static_cast<int>(256.0 * clamp(r, 0.0, 0.999)) << " "
      << static_cast<int>(256.0 * clamp(g, 0.0, 0.999)) << " "
      << static_cast<int>(256.0 * clamp(b, 0.0, 0.999)) << "\n";
}
