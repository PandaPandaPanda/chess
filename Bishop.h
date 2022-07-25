#ifndef __Bishop_h__
#define __Bishop_h__
#include "ChessPiece.h"

class Board;
enum Color;

class Bishop : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  ChessType type() const override;
public:
  Bishop(Color, int, int);
};
#endif
