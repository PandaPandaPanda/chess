#ifndef __Queen_h__
#define __Queen_h__
#include <vector>
#include "ChessPiece.h"

class Board;
enum Color;

class Queen : public ChessPiece {
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  ChessType type() const override;
  void doMovePiece(const std::pair<int, int>) override;
public:
  Queen(Color, int, int);
};
#endif
