#include "world.h"

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using std::abs;
using std::size_t;
using std::vector;

namespace World {
Map::Map(size_t grid_width, size_t grid_height)
    : _engine(_dev()),
      _random_w(0, static_cast<int>(grid_width - 1)),
      _random_h(0, static_cast<int>(grid_height - 1)),
      _grid(Fill(grid_width, grid_height)),
      grid_width(grid_width),
      grid_height(grid_height),
      num_obstacles(static_cast<size_t>(grid_height * grid_width * 0.2)) {}

vector<vector<Map::Tile>> Map::Fill(size_t grid_width, size_t grid_height) {
  vector<vector<Map::Tile>> m;

  // Initialize map where all tiles are kEmpty
  for (size_t i = 0; i < grid_width; i++) {
    vector<Tile> row;
    for (size_t j = 0; j < grid_height; j++) {
      row.emplace_back(Tile::kEmpty);
    }
    m.emplace_back(row);
  }

  // Place destination
  size_t x_d = _random_w(_engine);
  size_t y_d = _random_h(_engine);
  m[x_d][y_d] = Tile::kFinish;

  // Find most distant corner of world map based on
  // heuristic and place start there
  auto [x_s, y_s] = MostDistantCorner(x_d, y_d, grid_width, grid_height);
  m[x_s][y_s] = Tile::kStart;

  // Turn 20% of the kEmpty tiles into kObstacle
  size_t num_created_obstacles = 0;
  while (num_created_obstacles < num_obstacles) {
    // This loop could be more efficent
    size_t x = _random_w(_engine);
    size_t y = _random_h(_engine);

    if (m[x][y] == Tile::kEmpty) {
      m[x][y] = Tile::kObstacle;
      num_obstacles--;
    }
  }

  return m;
}

const std::tuple<size_t, size_t> Map::GetStartCoordinates() const {
  for (size_t x = 0; x < _grid.size(); x++) {
    for (size_t y = 0; y < _grid[x].size(); y++) {
      switch (_grid[x][y]) {
        case Tile::kStart:
          return std::make_tuple(x, y);
      }
    }
  }
}

const vector<vector<Map::Tile>> Map::GetGrid() const { return _grid; }

const Map::Tile Map::GetTileAt(size_t x, size_t y) const { return _grid[x][y]; }

const bool Map::IsValidCell(size_t x, size_t y) const {
  const bool x_in_map = x >= 0 && x < grid_height;
  const bool y_in_map = y >= 0 && y < grid_width;
  if (!x_in_map || !y_in_map) return false;

  const Tile tile = this->GetTileAt(x, y);
  if (tile == Tile::kObstacle) return false;

  return true;
}

std::tuple<size_t, size_t> MostDistantCorner(size_t x, size_t y,
                                             size_t grid_width,
                                             size_t grid_height) {
  // Initialize with distance to self
  size_t x_c = x;
  size_t y_c = y;
  size_t prev_distance = 0;

  vector<std::tuple<size_t, size_t>> corners{
      std::make_tuple(0, 0), std::make_tuple(0, grid_height - 1),
      std::make_tuple(grid_width - 1, 0),
      std::make_tuple(grid_width - 1, grid_height - 1)};

  for (const auto [x_i, y_i] : corners) {
    auto d_t = Heuristic(x_i, y_i, x, y);
    if (d_t > prev_distance) {
      x_c = x_i;
      y_c = y_i;
      prev_distance = d_t;
    }
  }

  return std::make_tuple(x_c, y_c);
}

size_t Heuristic(size_t x1, size_t y1, size_t x2, size_t y2) {
  return static_cast<size_t>(abs(static_cast<int>(x2) - static_cast<int>(x1)) +
                             abs(static_cast<int>(y2) - static_cast<int>(y1)));
}
}  // namespace World
