#include <iostream>
#include <memory>

#include "Camera.hpp"
#include "colour.hpp"
#include "HittableList.hpp"
#include "raytracing.hpp"
#include "Sphere.hpp"
#include "vec3.hpp"

int main()
{
  constexpr double aspectRatio = 16.0 / 9.0;
  constexpr int imageWidth = 400;
  constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
  constexpr int numSamplesPerPixel = 100;

  // World
  HittableList world;
  //world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));

  // Left side pi stand.
  world.add(std::make_shared<Sphere>(Point3(-0.4,  -0.35,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(-0.35, -0.2,   -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(-0.31, -0.05,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(-0.28,  0.1,   -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(-0.26,  0.25,  -1.0), 0.1));

  // Right side pi stand.
  world.add(std::make_shared<Sphere>(Point3(0.4,  -0.35,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(0.35, -0.2,   -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(0.31, -0.05,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(0.28,  0.1,   -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(0.26,  0.25,  -1.0), 0.1));

  // Top arc.
  world.add(std::make_shared<Sphere>(Point3(-0.65, 0.3,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(-0.5,  0.4,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(-0.35, 0.4,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(-0.2,  0.4,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3(-0.05, 0.4,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3( 0.1,  0.4,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3( 0.25, 0.4,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3( 0.4,  0.4,  -1.0), 0.1));
  world.add(std::make_shared<Sphere>(Point3( 0.55, 0.4,  -1.0), 0.1));

  // Ground sphere.
  world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0));

  // Camera
  Camera camera;

  std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int j = imageHeight - 1; j >= 0; j--) {
    std::cerr << "\rScanlines produced: "
              << imageHeight - j << " / " << imageHeight << std::flush;
    for (int i = 0; i < imageWidth; i++) {
      Colour pixelColour(0.0, 0.0, 0.0);
      for (int s = 0; s < numSamplesPerPixel; s++) {
        double u = (i + randomDouble()) / (imageWidth - 1);
        double v = (j + randomDouble()) / (imageHeight - 1);
        Ray ray = camera.getRay(u, v);
        pixelColour += rayColour(ray, world);
      }

      // Sampling is done in a vertically-flipped manner. Saving it to PPM
      // changes it to the correct orientation.
      writeColour(std::cout, pixelColour, numSamplesPerPixel);
    }
  }
  
  std::cerr << "\nDone.\n";

  return 0;
}
