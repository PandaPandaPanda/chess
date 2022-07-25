#include "Knight.h"

#include "Board.h"
#include "ChessPiece.h"

using namespace std;

const std::vector<std::pair<int, int>> Knight::moveVectors 
  = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, 
     {2, 1}, {2, -1}, {1, -2}, {-1, -2}};

vector<pair<int, int>> Knight::possibleMoves(const Board &b) const {
  vector<pair<int, int>> moves;
  const pair<int, int> myPos = getPosition();
  const Color myColor = getColor();
  for (const auto& v: moveVectors) {
    const pair<int, int> pos = {myPos.first + v.first, myPos.second + v.second};
    if (inBounds(pos)) {
      const ChessPiece *p = b.getChessPiece(pos.first, pos.second);
      if (p == nullptr || p->getColor() != myColor) {
        moves.emplace_back(pos);
      }
    }
  }
  return moves;
}

bool Knight::canDoMove(const pair<int, int> dest, const Board &b) const {
  const ChessPiece *p = b.getChessPiece(dest.first, dest.second);
  if (p != nullptr && p->getColor() == getColor()) { // attacking own piece
    return false;
  }

  const pair<int, int> myPos = getPosition();
  for (const auto& v: moveVectors) {
    const pair<int, int> pos = {myPos.first + v.first, myPos.second + v.second};
    if (pos == dest) {
      return true;
    }
  }
  return false;
}

int Knight::value() const {
  return 3;
}

ChessType Knight::type() const {
  return ChessType::KNIGHT;
}

void Knight::doMovePiece(const pair<int, int> newPos) {
  // no op
}

Knight::Knight(Color c, int row, int col): ChessPiece{c, row, col} {}
