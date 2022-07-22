#ifndef __Game_h__
#define __Game_h__
#include "Board.h"
#include "TextDisplay.h"
#include "Color.h"
#include "Team.h"

class Game {
  Board b;
  TextDisplay t;
<<<<<<< HEAD
  Team black;
  Team white;
  Color turnColor; // starts with black's turn
  Color winner;
  bool endgame;

  bool canMove(std::pair<int, int> start, std::pair<int, int> dest);
  bool isCheckMate();
  
=======
  int turn; // starts with 0 which is black's turn
  Team black;
  Team white;

  bool canMove(std::pair<int, int> start, std::pair<int, int> dest);
>>>>>>> f4affcd18704d4688df403cff1a199aff7d6daa8
public:
  Game();
  void setup(Player *blackPlayer, Player *whitePlayer);
  void setPlayer(Color c, Player *p);
<<<<<<< HEAD
  void resign();
  bool move(std::pair<int, int> start, std::pair<int, int> dest);
  bool hasGameEnded();
=======
  bool move(std::pair<int, int> start, std::pair<int, int> dest);
  void resign();
>>>>>>> f4affcd18704d4688df403cff1a199aff7d6daa8
};
#endif
