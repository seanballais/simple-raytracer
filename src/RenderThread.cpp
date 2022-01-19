#include <cmath>
#include <cstdlib>
#include <vector>

#include "Camera.hpp"
#include "HittableList.hpp"
#include "ray.hpp"
#include "raytracing.hpp"
#include "RenderedChunk.hpp"
#include "RenderThread.hpp"
#include "utils.hpp"
#include "vec3.hpp"

RenderThread::RenderThread(int id, int chunkWidth, int chunkHeight)
  : m_id(id)
  , m_chunkWidth(chunkWidth)
  , m_chunkHeight(chunkHeight)
  , m_scanlinesCompleted(0) {}

RenderedChunk RenderThread::getRenderedChunk()
{
  std::cout << "Chunk Width: " << m_renderedChunk.chunkWidth << "\n";
  return m_renderedChunk;
}

void RenderThread::render(const HittableList& world,
                          const Camera& camera,
                          const int& numSamplesPerPixel,
                          const int& maxRayBounceDepth)
{
  m_scanlinesCompleted = 0;

  std::vector<uint8_t> pixels;
  for (int j = m_chunkHeight - 1; j >= 0; j--) {
    std::cout << "Render Thread " << m_id << " Progress: "
              << m_scanlinesCompleted << "/" << m_chunkHeight
              << "\n";

    for (int i = 0; i < m_chunkWidth; i++) {
      Colour pixelColour(0.0, 0.0, 0.0);
      for (int s = 0; s < numSamplesPerPixel; s++) {
        double u = (i + randomDouble()) / (m_chunkWidth - 1);
        double v = (j + randomDouble()) / (m_chunkHeight - 1);
        Ray ray = camera.getRay(u, v);
        pixelColour += rayColour(ray, world, maxRayBounceDepth);
      }

      // Save data,
      double r = pixelColour.x();
      double g = pixelColour.y();
      double b = pixelColour.z();

      // Divide the colour by the number of samples.
      double scale = 1.0 / numSamplesPerPixel;
      r = std::sqrt(scale * r);
      g = std::sqrt(scale * g);
      b = std::sqrt(scale * b);

      pixels.push_back(static_cast<uint8_t>(r * 256.0));
      pixels.push_back(static_cast<uint8_t>(g * 256.0));
      pixels.push_back(static_cast<uint8_t>(b * 256.0));
    }

    m_scanlinesCompleted++;
  }

  RenderedChunk renderedChunk;
  renderedChunk.chunkWidth = m_chunkWidth;
  renderedChunk.chunkHeight = m_chunkHeight;
  renderedChunk.render = pixels;

  m_renderedChunk = renderedChunk;
}
