#ifndef WORLD_H
#define WORLD_H

#include <random>
#include <tuple>
#include <vector>

namespace World {
class Map {
 public:
  enum class Tile {
    kEmpty,
    kObstacle,
    kClosed,
    kFinish,
    kStart,
  };

  Map(std::size_t grid_width, std::size_t grid_height);

  const std::tuple<size_t, size_t> GetStartCoordinates() const;
  const std::vector<std::vector<Tile>> GetGrid() const;
  const Tile GetTileAt(size_t x, size_t y) const;
  const bool IsValidCell(size_t x, size_t y) const;
  std::size_t grid_width;
  std::size_t grid_height;
  std::size_t num_obstacles;

 private:
  std::vector<std::vector<Tile>> Fill(std::size_t grid_width,
                                      std::size_t grid_height);

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;

  std::vector<std::vector<Tile>> _grid;
};

std::tuple<size_t, size_t> MostDistantCorner(size_t x, size_t y,
                                             size_t grid_width,
                                             size_t grid_height);

std::size_t Heuristic(size_t x1, size_t y1, size_t x2, size_t y2);
}  // namespace World

#endif
