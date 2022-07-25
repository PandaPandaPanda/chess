#include "Board.h"
#include "ChessPiece.h"

using namespace std;

ChessPiece::ChessPiece(Color c, int row, int col): c{c}, row{row}, col{col} {}

void ChessPiece::possibleMovesDirection(const Board &b, int dr, int dc, vector<pair<int, int>> &moves) const {
  pair<int, int> pos = getPosition();
  const Color myColor = getColor();

  pos.first += dr;
  pos.second += dc;
  while (inBounds(pos)) {
    const ChessPiece *p = b.getChessPiece(pos.first, pos.second);
    if (p == nullptr) { // nothing there
      moves.emplace_back(pos);
    } else {
      if (myColor != p->getColor()) { // take enemy piece
        moves.emplace_back(pos);
      }
      break;
    }
    
    pos.first += dr;
    pos.second += dc;
  }
}

bool ChessPiece::moved() const {
  return hasMoved;
}

Color ChessPiece::getColor() const {
  return c;
}

pair<int, int> ChessPiece::getPosition() const {
  return {row, col};
}

vector<pair<int, int>> ChessPiece::getPossibleMoves(const Board &b) const {
  return possibleMoves(b);
}

bool ChessPiece::canMove(const pair<int, int> dest, const Board &b) const {
  if (!inBounds(dest)) {
    return false;
  }
  if (getPosition() == dest) {
    return false;
  }
  return canDoMove(dest, b);
}

int ChessPiece::getValue() const {
  return value();
}

ChessType ChessPiece::getType() const {
  return type();
}

void ChessPiece::movePiece(const pair<int, int> newPos) {
  row = newPos.first;
  col = newPos.second;
  hasMoved = true;
}

ChessPiece::~ChessPiece() {} // todo? nothing for now

bool ChessPiece::inBounds(int row, int col) {
  return 0 <= row && row < 8 && 0 <= col && col < 8;
}

bool ChessPiece::inBounds(const std::pair<int, int> pos) {
  return inBounds(pos.first, pos.second);
}
