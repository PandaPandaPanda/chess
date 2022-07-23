#ifndef __Game_h__
#define __Game_h__
#include "Board.h"
#include "TextDisplay.h"
#include "Color.h"
#include "Team.h"

class Game {
  Board b;
  TextDisplay t;
  Team black;
  Team white;
  Color turnColor; // starts with black's turn
  Color winner;
  bool endgame;

  bool canMove(std::pair<int, int> start, std::pair<int, int> dest);
  bool isCheckMate();
  void setPlayer(Color c, Player *p);
  
public:
  Game();
  void setup(Player * blackPlayer, Player * whitePlayer);
  void resign();
  bool move(std::pair<int, int> start, std::pair<int, int> dest);
  bool hasGameEnded();
};
#endif
