#ifndef __Computer1_h_
#define __Computer1_h_
#include "Computer.h"

class Board;
class Team;

class Computer1 : public Computer {
protected:
  void doSetup(Board *b, Team *homeTeam, Team* oppTeam) override;
  std::pair<std::pair<int, int>, std::pair<int, int>> doGetMove() override;
public:
  std::pair<std::pair<int, int>, std::pair<int, int>> getMove();
  Computer1();
};
#endif
