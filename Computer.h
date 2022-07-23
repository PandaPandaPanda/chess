#ifndef __Computer_h__
#define __Computer_h__
#include "Player.h"

class Board;
class Team;
enum PlayerType;

class Computer : public Player {
  virtual void doPlay() = 0;
  virtual void doSetup(Board *, Team *) = 0;
  PlayerType doGetType() override;
protected:
  Computer();
public:
  void setup(Board *b, Team *t);
};
#endif
