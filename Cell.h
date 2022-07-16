#ifndef __Cell_h__
#define __Cell_h__
#include "ChessPiece.h"
#include "TextDisplay.h"

class Cell {
  ChessPiece *p;
  TextDisplay *td;

public:
  Cell(ChessPiece *);
  void movePieceTo(Cell &);
  void attach(TextDisplay *); // attach observer
  void notifyTextObserver();
};
#endif
