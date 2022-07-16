#ifndef __Game_h__
#define __Game_h__
#include "Board.h"
#include "TextDisplay.h"
#include "Color.h"
#include "Team.h"

class Game {
  Board b;
  TextDisplay t;
  Color turn;
  Team black;
  Team white;
public:
  Game(Player *, Player *);
  void move(std::pair<int, int> start, std::pair<int, int> dest);
  void resign();
  void setup();
};
#endif
