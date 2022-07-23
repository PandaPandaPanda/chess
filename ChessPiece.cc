#include "ChessPiece.h"

using namespace std;

ChessPiece::ChessPiece(Color c, int row, int col): c{c}, row{row}, col{col} {}

Color ChessPiece::getColor() const {
  return c;
}

pair<int, int> ChessPiece::getPosition() const {
  return {row, col};
}

vector<pair<int, int>> ChessPiece::getPossibleMoves() const {
  return possibleMoves();
}

bool ChessPiece::canMove(const pair<int, int> dest, const Board &b) const {
  return canDoMove(dest, b);
}

int ChessPiece::getValue() const {
  return value();
}

char ChessPiece::getType() const {
  return type();
}

void ChessPiece::movePiece(const pair<int, int> newPos) {
  row = newPos.first;
  col = newPos.second;
}

ChessPiece::~ChessPiece() {} // todo? nothing for now
