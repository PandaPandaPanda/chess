#ifndef __Knight_h__
#define __Knight_h__
#include "ChessPiece.h"

class Knight : public ChessPiece {
  Knight();
  ~Knight() override;
  std::vector<std::vector<pair<int, int>> getPossibleMoves() override; 
  bool canMove(int destRow, int destCol, const Board &b) override;
  int getValue() override;
};
#endif
