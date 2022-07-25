#ifndef __Side_h__
#define __Side_h__
#include <vector>
#include "Color.h"
#include "Board.h"

class Player;
class ChessPiece;
class Pawn;

class Team {
  double points;
  Color c;
  Player *p;
  Board *b;
  std::vector<const ChessPiece *> pieces; // Place king at index 0

public:
  Team(Color c, Board *b);
  const ChessPiece *getKing();
  const std::vector<const ChessPiece *> getPieces();
  void setPlayer(Player *p);
  void removePiece(const ChessPiece *cp);
  void promotePawn(Pawn *cp, ChessType t);
};
#endif
