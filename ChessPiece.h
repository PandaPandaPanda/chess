#ifndef __ChessPiece_h__
#define __ChessPiece_h__
#include "Color.h"
#include "Board.h"

class ChessPiece {
  const Color c;
  int row, col;
public:
  ChessPiece(int, int);
  Color color();
  bool canMove(int destRow, int destCol, const Board &b);
};
#endif
