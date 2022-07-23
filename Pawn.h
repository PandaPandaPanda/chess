#ifndef __Pawn_h__
#define __Pawn_h__
#include "ChessPiece.h"

class Pawn : public ChessPiece {
  int moveDirection() const;
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  char type() const override;
public:
  Pawn(Color, int, int);
};
#endif
