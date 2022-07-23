#ifndef __ChessPiece_h__
#define __ChessPiece_h__
#include "Color.h"
#include "Board.h"
#include <vector>

enum ChessType {
  Pawn,
  Bishop,
  Knight,
  Rook,
  Queen,
  King
};

class ChessPiece {
  const Color c;
  int row, col;

  virtual std::vector<std::pair<int, int>> possibleMoves(const Board &b) const = 0;
  virtual bool canDoMove(const std::pair<int, int> dest, const Board &b) const = 0;
  virtual int value() const = 0;
  virtual char type() const = 0;
protected:
  ChessPiece(Color, int, int);

public:
  Color getColor() const;
  std::pair<int, int> getPosition() const;
  std::vector<std::pair<int, int>> getPossibleMoves(const Board &b) const;
  bool canMove(const std::pair<int, int> dest, const Board &b) const;
  int getValue() const;
  char getType() const;
  void movePiece(const std::pair<int,int>); // update row and col upon chess piece moved
  virtual ~ChessPiece();
  static bool inBounds(int, int);
  static bool inBounds(const std::pair<int, int>);
};
#endif
