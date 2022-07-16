#ifndef __Computer_h__
#define __Computer_h__
#include "Team.h"
#include "Player.h"

class Computer : public Player {
  virtual void doPlay() = 0;
protected:
  Computer(Board, Team);
};
#endif
