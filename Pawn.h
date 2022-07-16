#ifndef __Pawn_h__
#define __Pawn_h__
#include "ChessPiece.h"

class Pawn : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves() override;
  bool canDoMove(std::pair<int, int> dest, const Board &b) override;
  int value() override;
public:
  Pawn(Color, int, int);
};
#endif
