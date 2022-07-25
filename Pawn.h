#ifndef __Pawn_h__
#define __Pawn_h__
#include <vector>
#include "ChessPiece.h"

class Board;
enum Color;

class Pawn : public ChessPiece {
  bool justDoubleAdvanced = false;
  int moveDirection() const;
  std::vector<std::pair<int, int>> possibleMoves(const Board &b) const override;
  bool canDoMove(const std::pair<int, int> dest, const Board &b) const override;
  int value() const override;
  ChessType type() const override;
  void doMovePiece(const std::pair<int, int>) override;
public:
  Pawn(Color, int, int);
  bool enPassantCapturable();
};
#endif
