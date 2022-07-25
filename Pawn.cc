#include "Pawn.h"

#include "Board.h"
#include "ChessPiece.h"

using namespace std;

int Pawn::moveDirection() const {
  if (getColor() == Color::Black) {
    return 1;
  }
  return -1;
}

vector<pair<int, int>> Pawn::possibleMoves(const Board &b) const {
  vector<pair<int, int>> moves;
  const Color myColor = getColor();
  int dr = moveDirection();
  const pair<int, int> myPos = getPosition();
  const pair<int, int> forwards = {myPos.first + dr, myPos.second};
  const pair<int, int> doubleForwards = {myPos.first + dr + dr, myPos.second};
  const pair<int, int> attack1 = {myPos.first + dr, myPos.second + 1};
  const pair<int, int> attack2 = {myPos.first + dr, myPos.second - 1};
  if (inBounds(forwards)) {
    const ChessPiece *p = b.getChessPiece(forwards.first, forwards.second);
    if (p == nullptr) {
      moves.emplace_back(forwards);
    }
  }
  if (inBounds(doubleForwards)) {
    const ChessPiece *p = b.getChessPiece(forwards.first, forwards.second);
    const ChessPiece *q = b.getChessPiece(doubleForwards.first, doubleForwards.second);
    if (p == nullptr && q == nullptr && !moved()) {
      moves.emplace_back(doubleForwards);
    }
  }
  if (inBounds(attack1)) {
    const ChessPiece *p = b.getChessPiece(attack1.first, attack1.second);
    if (p != nullptr && p->getColor() != myColor) {
      moves.emplace_back(attack2);
    }
    // todo en passant
  }
  if (inBounds(attack2)) {
    const ChessPiece *p = b.getChessPiece(attack2.first, attack2.second);
    if (p != nullptr && p->getColor() != myColor) {
      moves.emplace_back(attack2);
    }
    // todo en passant
  }
  return moves;
}

bool Pawn::canDoMove(const pair<int, int> dest, const Board &b) const {
  const Color myColor = getColor();
  int dr = moveDirection();
  const pair<int, int> myPos = getPosition();
  const pair<int, int> forwards = {myPos.first + dr, myPos.second};
  const pair<int, int> doubleForwards = {myPos.first + dr + dr, myPos.second};
  const pair<int, int> attack1 = {myPos.first + dr, myPos.second + 1};
  const pair<int, int> attack2 = {myPos.first + dr, myPos.second - 1};
  const ChessPiece *p = b.getChessPiece(dest.first, dest.second);
  if (dest == forwards) {
    if (p == nullptr) { // ok
      return true;
    } else { // blocked
      return false;
    }
  } else if (dest == doubleForwards && !moved()) {
    return b.getChessPiece(forwards.first, forwards.second) == nullptr && p == nullptr;
  } else if (dest == attack1 || dest == attack2) {
    if (p == nullptr) { // can't attack nothing
      return false;
    } else {
      if (p->getColor() == myColor) { // can't attack own piece
        return false;
      } else { // ok
        return true;
      }
    }
  } else {
    // todo en passant
  }
  return false; // invalid, dest can only be forwards, attack1, or attack2
}

int Pawn::value() const {
  return 1;
}

ChessType Pawn::type() const {
  return ChessType::PAWN;
}

Pawn::Pawn(Color c, int row, int col): ChessPiece{c, row, col} {}
