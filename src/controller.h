#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

class Controller {
 public:
  void HandleInput(bool &running, Player &player) const;

 private:
  void MovePlayer(Player &player, Player::Direction input) const;
};

#endif
