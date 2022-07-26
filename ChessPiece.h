#ifndef __ChessPiece_h__
#define __ChessPiece_h__
#include <vector>
#include "Color.h"

enum ChessType {
  PAWN,
  BISHOP,
  KNIGHT,
  ROOK,
  QUEEN,
  KING
};

class Board;

class ChessPiece {
  const Color c;
  int row, col;
  bool hasMoved = false;

  virtual std::vector<std::pair<int, int>> possibleMoves(const Board &b) const = 0;
  virtual bool canDoMove(const std::pair<int, int> dest, const Board &b) const = 0;
  virtual int value() const = 0;
  virtual ChessType type() const = 0;
  virtual void doMovePiece(const std::pair<int, int>) = 0;
protected:
  ChessPiece(Color, int, int);
  void possibleMovesDirection(const Board &b, int dr, int dc, std::vector<std::pair<int, int>> &moves) const;

public:
  bool moved() const;
  Color getColor() const;
  std::pair<int, int> getPosition() const;
  std::vector<std::pair<int, int>> getPossibleMoves(const Board &b) const;
  bool canMove(const std::pair<int, int> dest, const Board &b) const;
  int getValue() const;
  ChessType getType() const;
  void movePiece(const std::pair<int,int>); // update row and col upon chess piece moved
  virtual ~ChessPiece();
  static bool inBounds(int, int);
  static bool inBounds(const std::pair<int, int>);
};
#endif
