#include <iostream>

#include "colour.hpp"
#include "raytracing.hpp"
#include "vec3.hpp"

int main()
{
  constexpr double aspectRatio = 16.0 / 9.0;
  constexpr int imageWidth = 400;
  constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);

  constexpr double viewportHeight = 2.0;
  constexpr double viewportWidth = aspectRatio * viewportHeight;
  constexpr double focalLength = 1.0;

  Point3 origin = Point3(0.0, 0.0, 0.0);
  Vec3 horizontalLength = Vec3(viewportWidth, 0.0, 0.0);
  Vec3 verticalLength = Vec3(0, viewportHeight, 0.0);
  Vec3 lowerLeftCorner = origin - (horizontalLength / 2)
                                - (verticalLength / 2)
                                - Vec3(0.0, 0.0, focalLength);

  std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int j = imageHeight - 1; j >= 0; j--) {
    std::cerr << "\rScanlines produced: "
              << j + 1 << " / " << imageHeight << std::flush;
    for (int i = 0; i < imageWidth; i++) {
      double u = static_cast<double>(i) / (imageWidth - 1);
      double v = static_cast<double>(j) / (imageHeight - 1);
      Ray ray(origin, lowerLeftCorner + (u * horizontalLength)
                                      + (v * verticalLength)
                                      - origin);
      Colour pixelColour = rayColour(ray);

      // Sampling is done in a vertically-flipped manner. Saving it to PPM
      // changes it to the correct orientation.
      writeColour(std::cout, pixelColour);
    }
  }
  
  std::cerr << "\nDone.\n";

  return 0;
}
