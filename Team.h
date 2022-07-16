#ifndef __Side_h__
#define __Side_h__
#include "Color.h"
#include "Player.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include <vector>
class Team {
  double points;
  Color c;
  Player *p;
  std::vector<ChessPiece *> pieces;
public:
  void removePiece(ChessPiece *);
  void promotePawn(Pawn *);
};
#endif
