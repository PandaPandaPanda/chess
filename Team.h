#ifndef __Side_h__
#define __Side_h__
#include <vector>
#include "Color.h"

class Player;
class ChessPiece;
class Pawn;

class Team {
  double points;
  Color c;
  Player *p;
  std::vector<ChessPiece *> pieces; // Place king at index 0

public:
  Team(Color c);
  const ChessPiece *getKing();
  const std::vector<ChessPiece *> getPieces();
  void setPlayer(Player *p);
  void removePiece(ChessPiece *);
  void promotePawn(Pawn *);
};
#endif
