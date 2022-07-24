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
  newPos.setChessPiece(p);
  p = nullptr;
  newPos.notifyTextObserver();
  notifyTextObserver();
}

void Cell::attach(TextDisplay* display) {
  td = display;
}

void Cell::notifyTextObserver() {
  td->notify(*this);
}

int Cell::getRow() {
  return r;
}

int Cell::getCol() {
  return c;
}

void Cell::setCoords(int r, int c) {
  this->r = r;
  this->c = c;
}

ostream& operator<<(ostream& o, Cell& c) {
  if (!c.p) {
    o << ' ';
  } else {
    o << c.p->getType();
  }
  return o;
};
