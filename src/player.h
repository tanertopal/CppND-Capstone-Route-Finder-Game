#ifndef PLAYER_H
#define PLAYER_H

#include <tuple>
#include <vector>

#include "SDL.h"
#include "world.h"

class Player {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Player(World::Map &map);

  void Walk(Direction direction);

  std::tuple<size_t, size_t> GetPosition() const;
  std::vector<std::tuple<size_t, size_t>> GetPath() const;

 private:
  std::vector<std::tuple<size_t, size_t>> _path;
  World::Map &_map;
};

#endif
