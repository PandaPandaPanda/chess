#ifndef __ChessPiece_h__
#define __ChessPiece_h__
#include "Color.h"
#include "Board.h"
#include "vector"

class ChessPiece {
  const Color c;
  int row, col;

protected:
  ChessPiece(int, int);

public:
  Color getColor();
  pair<int, int> getPosition();

  virtual ~ChessPiece();
  virtual std::vector<std::vector<pair<int, int>> getPossibleMoves() = 0;
  virtual bool canMove(int destRow, int destCol, const Board &b) = 0;
  virtual int getValue() = 0;
};
#endif
