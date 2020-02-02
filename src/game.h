#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "player.h"
#include "renderer.h"
#include "world.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;

 private:
  World::Map _map;
  Player _player;

  void Update();
};

#endif
