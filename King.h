#ifndef __King_h__
#define __King_h__
#include "ChessPiece.h"

class King : public ChessPiece {
  bool enemyCanAttack(const std::pair<int, int> pos, const Board &b) const;
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  char type() const override;
public:
  King(Color, int, int);
  static const std::vector<std::pair<int, int>> moveVectors;
};
const std::vector<std::pair<int, int>> King::moveVectors 
  = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
     {0, 1}, {1, -1}, {1, 0}, {1, -1}};
#endif
