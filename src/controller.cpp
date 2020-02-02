#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "player.h"

void Controller::HandleInput(bool &running, Player &player) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          MovePlayer(player, Player::Direction::kUp);
          break;

        case SDLK_DOWN:
          MovePlayer(player, Player::Direction::kDown);
          break;

        case SDLK_LEFT:
          MovePlayer(player, Player::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          MovePlayer(player, Player::Direction::kRight);
          break;
      }
    }
  }
}

void Controller::MovePlayer(Player &player, Player::Direction input) const {
  player.Walk(input);
}
