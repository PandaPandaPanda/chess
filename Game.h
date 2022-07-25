#ifndef __Game_h__
#define __Game_h__
#include "Board.h"
#include "Color.h"
#include "Team.h"
#include "TextDisplay.h"

class Screen;
class Game
{
  TextDisplay* t;
  Screen* scr;
  Board b;
  Team black;
  Team white;
  Color turnColor; // starts with black's turn
  Color winner;
  bool endgame;

  bool canMove(std::pair<int, int> start, std::pair<int, int> dest);
  bool isCheckMate();
  std::pair<bool, Color> strToColor(std::string color);

public:
  Game();
  ~Game();
  void setup(); // enter board setup mode
  void resign();
  void setPlayer(Color c, Player* p);
  bool move(std::pair<int, int> start, std::pair<int, int> dest);
  bool hasGameEnded();
  friend std::ostream& operator<<(std::ostream&, Game&);
};
#endif
