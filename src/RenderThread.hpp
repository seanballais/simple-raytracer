#ifndef RENDER_THREAD_HPP
#define RENDER_THREAD_HPP

#include <cstdlib>
#include <thread>
#include <vector>

#include "Camera.hpp"
#include "HittableList.hpp"

class RenderThread
{
public:
  RenderThread(int id, int chunkWidth, int chunkHeight);
  std::vector<uint8_t> render(const HittableList& world,
                              const Camera& camera,
                              const int& numSamplesPerPixel,
                              const int& maxRayBounceDepth);
  void printStatus();

private:
  int m_id;
  int m_chunkWidth;
  int m_chunkHeight;
  int m_scanlinesCompleted;
  bool m_isDone;
};

#endif
