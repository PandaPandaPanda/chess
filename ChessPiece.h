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
  string type; //may be temporary

  virtual std::vector<std::pair<int, int>> possibleMoves() = 0;
  virtual bool canDoMove(std::pair<int, int> dest, const Board &b) = 0;
  virtual int value() = 0;
protected:
  ChessPiece(Color, int, int, string type);

public:
  Color getColor() const;
  std::pair<int, int> getPosition() const;
  std::vector<std::pair<int, int>> getPossibleMoves() const;
  bool canMove(std::pair<int, int> dest, const Board &b) const;
  int getValue() const;
  string getType() const; //may be temporary
  void movePiece(pair<int,int>); //update row and col upon chess piece moved
  virtual ~ChessPiece();
};
#endif
