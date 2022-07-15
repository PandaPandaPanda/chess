#ifndef __King_h__
#define __King_h__
#include "ChessPiece.h"

class King : public ChessPiece {
public:
  King();
  ~King() override;
  std::vector<std::vector<pair<int, int>> getPossibleMoves() override; 
  bool canMove(int destRow, int destCol, const Board &b) override;
  int getValue() override;
};
#endif
