#ifndef __Computer2_h_
#define __Computer2_h_
#include "Computer.h"

class Board;
class Team;

class Computer2 : public Computer {
  void doPlay() override;
  void doSetup(Board *, Team *) override;
public:
  Computer2();
};
#endif
