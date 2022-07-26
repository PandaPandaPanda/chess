#ifndef __Computer1_h_
#define __Computer1_h_
#include "Computer.h"

class Board;
class Team;

class Computer1 : public Computer {
  void doSetup(Board *, Team *) override;
protected:
  void doPlay(Game *g) override;
public:
  Computer1();
};
#endif
