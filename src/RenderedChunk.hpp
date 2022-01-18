#ifndef RENDERED_CHUNK_HPP
#define RENDERED_CHUNK_HPP

#include <cstdint>
#include <vector>

struct RenderedChunk {
  int chunkWidth;
  int chunkHeight;
  std::vector<uint8_t> render;
};

#endif
