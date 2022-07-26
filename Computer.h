#ifndef __Computer_h__
#define __Computer_h__
#include "Game.h"
#include "Player.h"

class Board;
class Team;
enum PlayerType;

class Computer : public Player {
  virtual void doPlay(Game *g) = 0;
  virtual void doSetup(Board *, Team *) = 0;
  PlayerType doGetType() override;
protected:
  Computer();
  Team *t;
  Board *b;
public:
  void setup(Board *b, Team *t);
  int getRandomNum(int upperBound);
};
#endif
