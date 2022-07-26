#ifndef __Computer3_h_
#define __Computer3_h_
#include "Computer2.h"

class Board;
class Team;

class Computer3 : public Computer2 {
  Computer2 c2;
  void doSetup(Board *b, Team *homeTeam, Team* oppTeam) override;
protected:
  virtual std::pair<std::pair<int, int>, std::pair<int, int>> doGetMove() override;
public:
  Computer3();
  ~Computer3();
};
#endif
