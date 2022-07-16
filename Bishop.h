#ifndef __Bishop_h__
#define __Bishop_h__
#include "ChessPiece.h"

class Bishop : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves() override;
  bool canDoMove(std::pair<int, int> dest, const Board &b) override;
  int value() override;
public:
  Bishop(Color, int, int);
};
#endif
