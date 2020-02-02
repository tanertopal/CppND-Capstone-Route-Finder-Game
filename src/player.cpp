#include "player.h"

#include <iostream>
#include <vector>

#include "world.h"

Player::Player(World::Map &map) : _map(map) {
  _path.emplace_back(map.GetStartCoordinates());
}

void Player::Walk(Direction direction) {
  auto [x, y] = this->GetPosition();

  switch (direction) {
    case Direction::kUp:
      if (_map.IsValidCell(x, y - 1)) {
        _path.emplace_back(x, y - 1);
      }
      break;
    case Direction::kDown:
      if (_map.IsValidCell(x, y + 1)) {
        _path.emplace_back(x, y + 1);
      }
      break;
    case Direction::kLeft:

      if (_map.IsValidCell(x - 1, y)) {
        _path.emplace_back(x - 1, y);
      }
      break;
    case Direction::kRight:
      if (_map.IsValidCell(x + 1, y)) {
        _path.emplace_back(x + 1, y);
      }
      break;
  }

  auto [x2, y2] = this->GetPosition();
}

std::tuple<size_t, size_t> Player::GetPosition() const { return _path.back(); }

std::vector<std::tuple<size_t, size_t>> Player::GetPath() const { return _path; }
