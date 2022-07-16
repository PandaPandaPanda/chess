#ifndef __Queen_h__
#define __Queen_h__
#include "ChessPiece.h"

class Queen : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves() override;
  bool canDoMove(std::pair<int, int> dest, const Board &b) override;
  int value() override;
public:
  Queen(Color, int, int);
};
#endif
