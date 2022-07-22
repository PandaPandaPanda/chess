#ifndef __Game_h__
#define __Game_h__
#include "Board.h"
#include "TextDisplay.h"
#include "Color.h"
#include "Team.h"

class Game {
  Board b;
  TextDisplay t;
  int turn; // starts with 0 which is black's turn
  Team black;
  Team white;

  bool canMove(std::pair<int, int> start, std::pair<int, int> dest);
public:
  Game();
  void setup(Player *blackPlayer, Player *whitePlayer);
  void setPlayer(Color c, Player *p);
  bool move(std::pair<int, int> start, std::pair<int, int> dest);
  void resign();
};
#endif
