#include "ChessPiece.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

using namespace std;

vector<pair<int, int>> Queen::possibleMoves(const Board &b) const {
  const Color c = getColor();
  const pair<int, int> p = getPosition();
  int row = p.first, col = p.second;
  vector<pair<int, int>> moves1 = Rook{c, row, col}.getPossibleMoves(b);
  vector<pair<int, int>> moves2 = Bishop{c, row, col}.getPossibleMoves(b);
  moves1.insert(moves1.end(), moves2.begin(), moves2.end());
  return moves1;
}

bool Queen::canDoMove(const pair<int, int> dest, const Board &b) const {
  const Color c = getColor();
  const pair<int, int> p = getPosition();
  int row = p.first, col = p.second;
  return Rook{c, row, col}.canMove(dest, b) || Bishop{c, row, col}.canMove(dest, b);
}

int Queen::value() const {
  return 9;
}

char Queen::type() const {
  return 'Q';
}

Queen::Queen(Color c, int row, int col): ChessPiece{c, row, col} {}
