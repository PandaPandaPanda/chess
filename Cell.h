#ifndef __Cell_h__
#define __Cell_h__
#include <iostream>

class Board;
class ChessPiece;
class TextDisplay;
class Screen;
class Cell
{
  ChessPiece* p;
  TextDisplay* td;
  Screen* scr;
  int r, c;
  int dimension;
  bool isWhiteCell;

public:
  Cell();
  Cell(ChessPiece*);
  void setChessPiece(ChessPiece* p);
  const ChessPiece* getChessPiece() const;
  bool canMove(const std::pair<int, int>, const Board&);
  void movePieceTo(Cell&);
  void attach(TextDisplay*); // attach observer
  void notifyTextObserver();
  int getRow();
  int getCol();
  void setCoords(int r, int c, Screen* scr, int dimension, bool isWhiteCell);
  void resetCell();
  void drawPiece();
};
#endif
