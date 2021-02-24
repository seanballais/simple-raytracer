#include <iostream>

#include "colour.hpp"
#include "vec3.hpp"

int main()
{
  constexpr int imageWidth = 256;
  constexpr int imageHeight = 256;

  std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int j = 0; j < imageHeight; j++) {
    std::cerr << "\rScanlines produced: "
              << j << " / " << imageHeight - 1 << std::flush;
    for (int i = 0; i < imageWidth; i++) {
      // RGB colours will be in the range 0.0 to 1.0, at the moment.
      Colour pixelColour(static_cast<double>(i) / (imageWidth - 1),
                         static_cast<double>(j) / (imageHeight - 1),
                         0.25);
      writeColour(std::cout, pixelColour);
    }
  }
  
  std::cerr << "\nDone.\n";

  return 0;
}
