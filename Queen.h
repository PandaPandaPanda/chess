#ifndef __Queen_h__
#define __Queen_h__
#include "ChessPiece.h"

class Queen : public ChessPiece {
  Queen();
  ~Queen() override;
  std::vector<std::vector<pair<int, int>> getPossibleMoves() override; 
  bool canMove(int destRow, int destCol, const Board &b) override;
  int getValue() override;
};
#endif
