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
  std::vector<ChessPiece *> pieces; // Place king at index 0

public:
  Team(Color c);
  const ChessPiece *getKing();
  const std::vector<ChessPiece *> getPieaces();
  void setPlayer(Player *p);
  void removePiece(ChessPiece *);
  void promotePawn(Pawn *);
};
#endif
