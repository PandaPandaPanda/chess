#ifndef __Computer1_h_
#define __Computer1_h_
#include "Computer.h"

class Board;
class Team;

class Computer1 : public Computer {
  void doSetup(Board *b, Team *homeTeam, Team* oppTeam) override;
protected:
  std::pair<std::pair<int, int>, std::pair<int, int>> doGetMove() override;
public:
  Computer1();
};
#endif
