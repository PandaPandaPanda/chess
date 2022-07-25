#include "Cell.h"
#include "ChessPiece.h"
#include "TextDisplay.h"
#include "sdl_wrap.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Cell::Cell()
  : p{ nullptr }
  , td{ nullptr }
{
}

Cell::Cell(ChessPiece* p)
  : p{ p }
  , td{ nullptr }
{
}

void
Cell::notifyTextObserver()
{
  td->notify(*this);
}

void
Cell::setChessPiece(ChessPiece* p)
{
  delete this->p;
  this->p = p;
  notifyTextObserver();
}

const ChessPiece*
Cell::getChessPiece() const
{
  return p;
}

bool
Cell::canMove(const std::pair<int, int> dest, const Board& b)
{
  return (p && p->canMove(dest, b));
}

void
Cell::movePieceTo(Cell& newPos)
{
  p->movePiece({ newPos.getRow(), newPos.getCol() });

  newPos.setChessPiece(p);

  p = nullptr;
  newPos.notifyTextObserver();
  notifyTextObserver();
}

void
Cell::attach(TextDisplay* display)
{
  td = display;
}

int
Cell::getRow()
{
  return r;
}

int
Cell::getCol()
{
  return c;
}

void
Cell::setCoords(int r, int c, Screen* scr, int dimension, bool isWhiteCell)
{
  this->r = r;
  this->c = c;
  this->scr = scr;
  this->dimension = dimension;
  this->isWhiteCell = isWhiteCell;
}

void
Cell::resetCell()
{
  Colour colorToDraw =
    isWhiteCell ? Colour{ '\xff', '\xff', '\xff' } : Colour{ 0x0, 0x0, 0x0 };

  scr->draw_rect(
    c * dimension, r * dimension, dimension, dimension, colorToDraw);
}

void
Cell::drawPiece()
{
  string toDraw;

  if (p) {
    if (p->getColor() == Color::Black) {
      toDraw += 'B';
    } else {
      toDraw += 'W';
    }
    switch (p->getType()) {
      case ChessType::PAWN:
        toDraw += 'P';
        break;
      case ChessType::ROOK:
        toDraw += 'R';
        break;
      case ChessType::KNIGHT:
        toDraw += 'N';
        break;
      case ChessType::BISHOP:
        toDraw += 'B';
        break;
      case ChessType::QUEEN:
        toDraw += 'Q';
        break;
      case ChessType::KING:
        toDraw += 'K';
        break;
    }

    scr->draw_img(toDraw, c * dimension + 10, r * dimension + 10);
  }
}
