#ifndef __Queen_h__
#define __Queen_h__
#include "ChessPiece.h"

class Queen : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  char type() const override;
public:
  Queen(Color, int, int);
};
#endif
