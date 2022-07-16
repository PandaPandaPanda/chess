#ifndef __ChessPiece_h__
#define __ChessPiece_h__
#include "Color.h"
#include "Board.h"
#include <vector>

class ChessPiece {
  const Color c;
  int row, col;

  virtual std::vector<std::pair<int, int>> possibleMoves() = 0;
  virtual bool canDoMove(std::pair<int, int> dest, const Board &b) = 0;
  virtual int value() = 0;
protected:
  ChessPiece(Color, int, int);

public:
  Color getColor();
  std::pair<int, int> getPosition();
  std::vector<std::pair<int, int>> getPossibleMoves();
  bool canMove(std::pair<int, int> dest, const Board &b);
  int getValue();
  virtual ~ChessPiece();
};
#endif
