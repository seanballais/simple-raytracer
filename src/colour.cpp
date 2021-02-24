#include "colour.hpp"

void writeColour(std::ostream& out, Colour pixelColour)
{
  out << static_cast<int>(255.0 * pixelColour.x) << " "
      << static_cast<int>(255.0 * pixelColour.y) << " "
      << static_cast<int>(255.0 * pixelColour.z) << "\n";
}
