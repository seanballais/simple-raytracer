#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Camera.hpp"
#include "RenderedChunk.hpp"
#include "colour.hpp"
#include "DielectricMaterial.hpp"
#include "HittableList.hpp"
#include "LambertianMaterial.hpp"
#include "MetalMaterial.hpp"
#include "raytracing.hpp"
#include "RenderThread.hpp"
#include "Sphere.hpp"
#include "utils.hpp"
#include "vec3.hpp"

int main()
{
  constexpr double aspectRatio = 16.0 / 9.0;
  constexpr int imageWidth = 1920;
  constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
  constexpr int numSamplesPerPixel = 100;
  constexpr int maxRayBounceDepth = 5;

  // World
  HittableList world;

  auto groundMaterial = std::make_shared<LambertianMaterial>(
    Colour(0.5, 0.5, 0.5));
  world.add(std::make_shared<Sphere>(Point3(0.0, -1000.0, 0.0),
                                     1000.0,
                                     groundMaterial));

  for (int i = -11; i < 11; i++) {
    for (int j = -11; j < 11; j++) {
      auto chooseMat = randomDouble();
      Point3 center(i + 0.9 * randomDouble(), 0.2, j + 0.9 * randomDouble());

      if ((center - Point3(4.0, 0.2, 0.0)).length() > 0.9) {
        std::shared_ptr<Material> sphereMaterial;

        if (chooseMat < 0.8) {
          // Use diffuse material.
          Vec3 albedo = getRandomVec3() * getRandomVec3();
          sphereMaterial = std::make_shared<LambertianMaterial>(albedo);
          world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
        } else if (chooseMat < 0.95) {
          // Use metal material.
          Vec3 albedo = getRandomVec3(0.5, 1.0);
          double fuzz = randomDouble(0.0, 0.5);
          sphereMaterial = std::make_shared<MetalMaterial>(albedo, fuzz);
          world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
        } else {
          // Use glass material.
          sphereMaterial = std::make_shared<DielectricMaterial>(1.5);
          world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
        }
      }
    }
  }

  auto material1 = std::make_shared<DielectricMaterial>(1.5);
  world.add(std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, material1));

  auto material2 = std::make_shared<LambertianMaterial>(Colour(0.4, 0.2, 0.1));
  world.add(std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, material2));

  auto material3 = std::make_shared<MetalMaterial>(Colour(0.7, 0.6, 0.5), 0.0);
  world.add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, material3));

  // Camera
  Point3 lookFrom(13.0, 2.0, 3.0);
  Point3 lookAt(0.0, 0.0, 0.0);
  Vec3 viewUp(0.0, 1.0, 0.0);
  double distanceToFocus = 10.0;
  double aperture = 0.1;

  Camera camera(lookFrom,
                lookAt,
                viewUp,
                20.0,
                aspectRatio,
                aperture,
                distanceToFocus);

  std::cout << "Rendering image.\n";
  std::cout << "Width: " << imageWidth << "\n";
  std::cout << "Height: " << imageHeight << "\n";

  // Let's use multithreading.
  const int numCores = std::thread::hardware_concurrency();
  std::cout << "Rendering with " << numCores << " cores...\n";

  // Slice up the task vertically. Each thread will render a vertical slice of
  // the final image.
  int chunkWidthPerThread = imageWidth / numCores;
  std::cout << "Width of each chunk: " << chunkWidthPerThread << "px\n";

  // If the image width is not divisible by the number of cores we have, we
  // put the remaining width to the last thread. We could spread out the
  // remaining width to the other threads, but we'll just give it to the last
  // thread for simplicity.
  int chunkWidthForNthThread = chunkWidthPerThread + (imageWidth % numCores);
  std::cout << "Width of last chunk: " << chunkWidthForNthThread << "px\n";

  std::vector<RenderThread> renderThreads;
  renderThreads.reserve(numCores);

  int startingX = 0;
  for (int i = 0; i < numCores; i++) {
    std::cout << "Setting up render thread #" << i << "\n";

    if (i < numCores - 1) {
      renderThreads.emplace_back(i,
                                 imageWidth,
                                 imageHeight,
                                 startingX,
                                 chunkWidthPerThread,
                                 imageHeight);
    } else {
      renderThreads.emplace_back(numCores - 1,
                                 imageWidth,
                                 imageHeight,
                                 startingX,
                                 chunkWidthForNthThread,
                                 imageHeight);
    }

    // We don't need to worry about the last chunk's width, since we're just
    // getting the starting X position of a chunk. Only the last chunk may have
    // a different width which cannot affect any future render thread
    // initializations, because it's the last chunk.
    startingX += chunkWidthPerThread;
  }

  auto timeStart = std::chrono::steady_clock::now();

  // Place the render threads into their own std::threads.
  std::vector<std::thread> threads;
  threads.reserve(renderThreads.size());
  for (int i = 0; i < renderThreads.size(); i++) {
    threads.push_back(
      std::thread(&RenderThread::render,
                  &renderThreads[i],
                  world,
                  camera,
                  numSamplesPerPixel,
                  maxRayBounceDepth)
    );
  }

  // Wait until the threads are done.
  for (int i = 0; i < threads.size(); i++) {
    threads[i].join();
  }

  auto timeEnd = std::chrono::steady_clock::now();

  std::cout << "Rendering done.\n";

  // Stitch everything up.
  std::cout << "Saving to PNG file...\n";
  const int numChannels = 3; // RGB
  int pixelIndex = 0;
  uint8_t pixels[imageWidth * imageHeight * numChannels];
  RenderedChunk chunks[renderThreads.size()];

  for (int i = 0; i < renderThreads.size(); i++) {
    std::cout << "Getting chunk from render thread " << i << "...\n";
    chunks[i] = renderThreads[i].getRenderedChunk();
  }

  // TODO: Fix image saving code.
  for (int i = 0; i < imageHeight; i++) {
    // Note that each element in the chunk is a colour channel value.
    for (int j = 0; j < renderThreads.size(); j++) {
      
      // Get a line from each chunk.
      int startingIndex = chunks[j].chunkWidth * i * numChannels;
      for (int k = 0; k < chunks[j].chunkWidth; k++) {
        // Get each pixel value.
        pixels[pixelIndex++] = chunks[j].render[startingIndex++];
        pixels[pixelIndex++] = chunks[j].render[startingIndex++];
        pixels[pixelIndex++] = chunks[j].render[startingIndex++];
      }
    }
  }

  stbi_write_png(
    "render.png",
    imageWidth,
    imageHeight,
    numChannels,
    pixels,
    imageWidth * numChannels
  );

  // Get time duration.
  auto timeElapsed = timeEnd - timeStart;
  int timeElapsedMS = std::chrono::duration_cast<std::chrono::milliseconds>(
    timeElapsed
  ).count();

  int totalElapsedTimeMS = timeElapsedMS;

  int hours = timeElapsedMS / 3600000; // 1 hr = 3,600,000 ms
  timeElapsedMS = timeElapsedMS % 3600000;

  int minutes = timeElapsedMS / 60000; // 1 m  = 60,000 ms
  timeElapsedMS = timeElapsedMS % 60000;

  int seconds = timeElapsedMS / 1000;  // 1s   = 1,000 ms
  timeElapsedMS = timeElapsedMS % 1000;

  int milliseconds = timeElapsedMS;

  std::cout << "============================================\n";
  std::cout << "Time Elapsed: "
            << hours        << "hr "
            << minutes      << "m "
            << seconds      << "s "
            << milliseconds << "ms\n";
  std::cout << "Time Elapsed: " << totalElapsedTimeMS << "ms\n";

  return 0;
}
