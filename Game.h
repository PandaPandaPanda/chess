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
  char winner;
  int steps;
  bool endgame;

  bool canMove(std::pair<int, int> start, std::pair<int, int> dest);
  bool isCheckMate();
  bool isStaleMate();
  void invalidateEnPassant();
  std::pair<const ChessPiece *, int> oneAttackingPiece(const ChessPiece *king); // king being attacked by exactly one piece
  bool knightAttackingKing(const ChessPiece *king); // king being attacked by knight
  bool canBlockCheck(const ChessPiece *attackingPiece, const ChessPiece *king);
  bool canCaptureAttacking(const ChessPiece *attackingPiece);
  std::pair<bool, Color> strToColor(std::string color);

public:
  Game();
  ~Game();
  void setup(); // enter board setup mode
  void resign();
  void setPlayer(Color c, Player* p);
  bool move(std::pair<int, int> start, std::pair<int, int> dest);
  bool hasGameEnded();
  int getSteps();
  char getWinner();
  Color getTurnColor();
  friend std::ostream& operator<<(std::ostream&, Game&);
};
#endif
