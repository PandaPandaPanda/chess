#ifndef __Rook_h__
#define __Rook_h__
#include <vector>
#include "ChessPiece.h"

class Board;
enum Color;

class Rook : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  char type() const override;
public:
  Rook(Color, int, int);
};
#endif
