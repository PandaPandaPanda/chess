#ifndef __Knight_h__
#define __Knight_h__
#include "ChessPiece.h"

class Knight : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  char type() const override;
public:
  Knight(Color, int, int);
  static const std::vector<std::pair<int, int>> moveVectors;
};
const std::vector<std::pair<int, int>> Knight::moveVectors 
  = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, 
     {2, 1}, {2, -1}, {1, -2}, {-1, -2}};
#endif
