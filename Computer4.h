#ifndef __Computer4_h_
#define __Computer4_h_
#include "Computer3.h"

class Board;
class Team;

class Computer4 : public Computer3 {
    void doSetup(Board *b, Team *homeTeam, Team *oppTeam) override;

   protected:
    virtual std::pair<std::pair<int, int>, std::pair<int, int>> doGetMove() override;

   public:
    Computer4();
    ~Computer4();
    std::pair<std::pair<int, int>, std::pair<int, int>> getMove();
};
#endif
