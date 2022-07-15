#ifndef __Rook_h__
#define __Rook_h__
#include "ChessPiece.h"

class Rook : public ChessPiece {
  Rook();
  ~Rook() override;
  std::vector<std::vector<pair<int, int>> getPossibleMoves() override; 
  bool canMove(int destRow, int destCol, const Board &b) override;
  int getValue() override;
};
#endif
