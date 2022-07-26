#ifndef __Computer2_h_
#define __Computer2_h_
#include "Computer1.h"

class Board;
class Team;

class Computer2 : public Computer1 {
    void doSetup(Board *b, Team *homeTeam, Team* oppTeam) override;

   protected:
    virtual std::pair<std::pair<int, int>, std::pair<int, int>> doGetMove() override;

   public:
    Computer2();
};
#endif
