#ifndef __Player_h__
#define __Player_h__

#include "Game.h"

enum PlayerType {
  H,
  C
};

class Player {
  virtual void doPlay(Game *g) = 0;
  virtual PlayerType doGetType() = 0;
protected:
  Player();
public:
  virtual ~Player() = 0;
  void play(Game *g);
  PlayerType getType();
};
#endif
