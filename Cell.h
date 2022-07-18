#ifndef __Cell_h__
#define __Cell_h__
#include "ChessPiece.h"
#include "TextDisplay.h"

class Cell {
  ChessPiece *p;
  TextDisplay *td;

public:
  Cell();
  Cell(ChessPiece *);
  void movePieceTo(Cell &);
  void attach(TextDisplay *); // attach observer
  void notifyTextObserver();
  bool canMove(std::pair<int, int> dest, const Board &b);
  friend ostream& operator<<(ostream&, Cell&); //temporary, to remove later
};
#endif
