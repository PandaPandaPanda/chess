#ifndef __Rook_h__
#define __Rook_h__
#include "ChessPiece.h"

class Rook : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves() override;
  bool canDoMove(std::pair<int, int> dest, const Board &b) override;
  int value() override;
public:
  Rook(Color, int, int);
};
#endif
