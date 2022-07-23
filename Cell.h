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
  const ChessPiece *getChessPiece() const;
  bool canMove(const std::pair<int, int>, const Board &);
  void movePieceTo(Cell &);
  void attach(TextDisplay *); // attach observer
  void notifyTextObserver();
  friend ostream& operator<<(ostream&, Cell&); //temporary, to remove later
};
#endif
