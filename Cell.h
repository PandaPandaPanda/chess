#ifndef __Cell_h__
#define __Cell_h__
#include "ChessPiece.h"
#include "TextDisplay.h"

class Cell {
  ChessPiece *p;
  TextDisplay *td;

  public:
  void attach(); // attach observer
  void notifyGraphicOvserver();
};
#endif
