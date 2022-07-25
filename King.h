#ifndef __King_h__
#define __King_h__
#include <vector>
#include "ChessPiece.h"

class Board;
enum Color;

class King : public ChessPiece {
  bool enemyCanAttack(const std::pair<int, int> pos, const Board &b) const;
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  ChessType type() const override;
public:
  King(Color, int, int);
  bool inCheck(const Board &b) const;
  static const std::vector<std::pair<int, int>> moveVectors;
};
#endif
