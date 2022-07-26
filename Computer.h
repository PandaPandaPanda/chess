#ifndef __Computer_h__
#define __Computer_h__
#include "Game.h"
#include "Player.h"

class Board;
class Team;
enum PlayerType;

class Computer : public Player {
  void doPlay(Game *g) override;
  virtual std::pair<std::pair<int, int>, std::pair<int, int>> doGetMove() = 0;
  virtual void doSetup(Board *b, Team *homeTeam, Team* oppTeam) = 0;
  PlayerType doGetType() override;
protected:
  Computer();
  Team *homeTeam;
  Team *oppTeam;
  Board *b;
public:
  std::pair<std::pair<int, int>, std::pair<int, int>> getMove();
  void setup(Board *b, Team *homeTeam, Team* oppTeam);
  int getRandomNum(int upperBound);
};
#endif
