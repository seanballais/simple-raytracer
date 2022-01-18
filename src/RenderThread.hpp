#ifndef RENDER_THREAD_HPP
#define RENDER_THREAD_HPP

#include <cstdlib>
#include <thread>
#include <vector>

#include "Camera.hpp"
#include "HittableList.hpp"
#include "RenderedChunk.hpp"

class RenderThread
{
public:
  RenderThread(int id, int chunkWidth, int chunkHeight);
  RenderedChunk getRenderedChunk();
  void render(const HittableList& world,
              const Camera& camera,
              const int& numSamplesPerPixel,
              const int& maxRayBounceDepth);

private:
  int m_id;
  int m_chunkWidth;
  int m_chunkHeight;
  int m_scanlinesCompleted;
  bool m_isDone;
  RenderedChunk m_renderedChunk;
};

#endif
