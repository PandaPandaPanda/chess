#ifndef __King_h__
#define __King_h__
#include "ChessPiece.h"

class King : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves() override;
  bool canDoMove(std::pair<int, int> dest, const Board &b) override;
  int value() override;
public:
  King(Color, int, int);
};
#endif
