#ifndef __Computer4_h_
#define __Computer4_h_
#include "Computer.h"

class Board;
class Team;

class Computer4 : public Computer {
  void doPlay(Game *g) override;
  void doSetup(Board *, Team *) override;
public:
  Computer4();
};
#endif
