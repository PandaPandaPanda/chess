#include "Cell.h"
#include "ChessPiece.h"
#include "TextDisplay.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Cell::Cell(): p{nullptr}, td{nullptr} {}

Cell::Cell(ChessPiece* p): p{p}, td{nullptr} {}

void Cell::setChessPiece(ChessPiece *p) {
  this->p = p;
}

const ChessPiece *Cell::getChessPiece() const {
  return p;
}

bool Cell::canMove(const std::pair<int, int> dest, const Board &b) {
  return (p && p->canMove(dest, b));
}

void Cell::movePieceTo(Cell& newPos) {
  delete newPos.p;
  p->movePiece(newPos.p->getPosition());
  newPos.p = p;
  p = nullptr;
}

void Cell::attach(TextDisplay* display) {
  td = display;
}

void Cell::notifyTextObserver() {
  td->notify(*this);
}

ostream& operator<<(ostream& o, Cell& c) {
  if (!c.p) {
    o << ' ';
  } else {
    o << c.p->getType();
  }
  return o;
};
