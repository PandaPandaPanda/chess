#ifndef __Computer3_h_
#define __Computer3_h_
#include "Computer.h"

class Board;
class Team;

class Computer3 : public Computer {
  void doPlay(Game *g) override;
  void doSetup(Board *, Team *) override;
public:
  Computer3();
};
#endif
