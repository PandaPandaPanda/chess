#ifndef __Knight_h__
#define __Knight_h__
#include "ChessPiece.h"

class Knight : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves() override;
  bool canDoMove(std::pair<int, int> dest, const Board &b) override;
  int value() override;
public:
  Knight(Color, int, int);
};
#endif
