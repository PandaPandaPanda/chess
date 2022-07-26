#ifndef __Computer1_h_
#define __Computer1_h_
#include "Computer.h"

class Board;
class Team;

class Computer1 : public Computer {
  void doPlay(Game *g) override;
  void doSetup(Board *, Team *) override;
public:
  Computer1();
};
#endif
