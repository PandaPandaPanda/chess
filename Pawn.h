#ifndef __Pawn_h__
#define __Pawn_h__
#include "ChessPiece.h"

class Pawn : public ChessPiece {
  Pawn();
  ~Pawn() override;
  std::vector<std::vector<pair<int, int>> getPossibleMoves() override; 
  bool canMove(int destRow, int destCol, const Board &b) override;
  int getValue() override;
};
#endif
