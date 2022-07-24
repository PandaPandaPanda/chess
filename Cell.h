#ifndef __Cell_h__
#define __Cell_h__
#include <iostream>

class Board;
class ChessPiece;
class TextDisplay;

class Cell {
  ChessPiece *p;
  TextDisplay *td;
  int r, c;

public:
  Cell();
  Cell(ChessPiece *);
  void setChessPiece(ChessPiece *p);
  const ChessPiece *getChessPiece() const;
  bool canMove(const std::pair<int, int>, const Board &);
  void movePieceTo(Cell &);
  void attach(TextDisplay *); // attach observer
  void notifyTextObserver();
  int getRow();
  int getCol();
  void setCoords(int r, int c);
  friend std::ostream& operator<<(std::ostream&, Cell&); //temporary, to remove later
};
#endif
