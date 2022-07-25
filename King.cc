#include "King.h"

#include "Board.h"
#include "ChessPiece.h"

using namespace std;

const std::vector<std::pair<int, int>> King::moveVectors 
  = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
     {0, 1}, {1, -1}, {1, 0}, {1, -1}};

bool King::enemyCanAttack(const std::pair<int, int> pos, const Board &b) const {
  const Color myColor = getColor();
  // todo maybe find a better way to iterate the Board (iterator?)
  for (int r = 0; r < 8; ++r) {
    for (int c = 0; c < 8; ++c) {
      const ChessPiece *p = b.getChessPiece(r, c);
      if (p != nullptr && p->getColor() != myColor) {
        if (p->canMove(pos, b)) {
          return true;
        }
      }
    }
  }
  return false;
}

vector<pair<int, int>> King::possibleMoves(const Board &b) const {
  vector<pair<int, int>> moves;
  const Color myColor = getColor();
  const pair<int, int> myPos = getPosition();
  for (const auto &v : moveVectors) {
    const pair<int, int> pos = {myPos.first + v.first, myPos.second + v.second};
    if (inBounds(pos)) {
      const ChessPiece *p = b.getChessPiece(pos.first, pos.second);
      if (p == nullptr && !enemyCanAttack(pos, b)) {
        moves.emplace_back(pos);
      } else {
        if (p->getColor() != myColor) { // attacking own piece
          // technically not correct, we would need to check if taking this piece
          // would put king in check (todo)
          // ChessPiece::canMove is not sufficient, we need ChessPiece::defending
          moves.emplace_back(pos);
        }
      }
    }
  }
  // todo castling
  return moves;
}

bool King::canDoMove(const pair<int, int> dest, const Board &b) const {
  const Color myColor = getColor();
  const pair<int, int> myPos = getPosition();
  for (const auto &v : moveVectors) {
    const pair<int, int> pos = {myPos.first + v.first, myPos.second + v.second};
    if (dest == pos) {
      const ChessPiece *p = b.getChessPiece(dest.first, dest.second);
      if (p == nullptr) {
        return !enemyCanAttack(dest, b);
      } else {
        if (p->getColor() == myColor) { // attacking own piece
          return false;
        } else {
          // technically not correct, we would need to check if taking this piece
          // would put king in check (todo)
          // ChessPiece::canMove is not sufficient, we need ChessPiece::defending
          return true;
        }
      }
    }
  }
  // todo castling
  return false;
}

int King::value() const {
  return 999;
}

ChessType King::type() const {
  return ChessType::KING;
}
  
void King::doMovePiece(const pair<int, int> newPos) {
  // no op
}

King::King(Color c, int row, int col): ChessPiece{c, row, col} {}

bool King::inCheck(const Board &b) const {
  const Color myColor = getColor();
  // todo maybe find a better way to iterate the Board (iterator?)
  for (int r = 0; r < 8; ++r) {
    for (int c = 0; c < 8; ++c) {
      const ChessPiece *p = b.getChessPiece(r, c);
      if (p != nullptr && p->getColor() != myColor) {
        if (p->canMove(getPosition(), b)) {
          return true;
        }
      }
    }
  }
  return false;
}
