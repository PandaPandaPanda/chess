#include "King.h"

#include "Board.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Rook.h"

using namespace std;

const std::vector<std::pair<int, int>> King::moveVectors 
  = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
     {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool King::enemyCanAttack(const std::pair<int, int> pos, const Board &b) const {
  const Color myColor = getColor();
  for (int r = 0; r < 8; ++r) {
    for (int c = 0; c < 8; ++c) {
      const ChessPiece *p = b.getChessPiece(r, c);
      if (p != nullptr && p->getColor() != myColor) {
        if (p->getType() == ChessType::KING) {
          for (const auto v : King::moveVectors) {
            const pair<int, int> enemyKingPos = p->getPosition();
            const pair<int, int> attackedPos = {enemyKingPos.first + v.first, enemyKingPos.second + v.second};
            // cout << "debug enemycanattack " << attackedPos.first << " " << attackedPos.second << endl;
            if (pos == attackedPos) {
              return true;
            }
          }
        } else if (p->getType() == ChessType::PAWN) {
          const Pawn *pawn = reinterpret_cast<const Pawn *>(p);
          for (const auto attack : pawn->possibleAttacks(b)) {
            if (pos == attack) {
              return true;
            }
          }
        } else if (p->canMove(pos, b)) {
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
  // cout << "debug king 0" << endl;
  for (const auto &v : moveVectors) {
    const pair<int, int> pos = {myPos.first + v.first, myPos.second + v.second};
    // cout << "debug king 0.1" << endl;
    if (inBounds(pos)) {
      const ChessPiece *p = b.getChessPiece(pos.first, pos.second);
      // cout << "debug king 0.2" << endl;
      if (p == nullptr && !enemyCanAttack(pos, b)) {
        // cout << "debug king 0.3" << endl;
        moves.emplace_back(pos);
      } else {
        // cout << "debug king 0.4" << endl;
        if (p == nullptr) {
          // cout << "debug king 0.5" << endl;
          continue;
        }
        if (p->getColor() != myColor) { // attacking own piece
          // technically not correct, we would need to check if taking this piece
          // would put king in check (todo)
          // ChessPiece::canMove is not sufficient, we need ChessPiece::defending
          moves.emplace_back(pos);
        }
      }
    }
  }
  // cout << "debug king 1" << endl;
  const pair<int, int> castleLeft = {myPos.first, myPos.second - 2};
  const pair<int, int> castleRight = {myPos.first, myPos.second + 2};
  if (canDoMove(castleLeft, b)) {
    moves.emplace_back(castleLeft);
  } else if (canDoMove(castleRight, b)) {
    moves.emplace_back(castleRight);
  }
  // cout << "debug king 2" << endl;
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
          return true;
        }
      }
    }
  }
  // castling
  if (!moved()) {
    const pair<int, int> castleLeft = {myPos.first, myPos.second - 2};
    const pair<int, int> castleRight = {myPos.first, myPos.second + 2};
    if (dest == castleLeft) {
      const pair<int, int> rookPos = {myPos.first, 0};
      const ChessPiece *r = b.getChessPiece(rookPos.first, rookPos.second);
      if (r == nullptr) {
        return false; // rook not there
      }
      if (r->getType() == ChessType::ROOK) {
        if (r->moved()) {
          return false;
        }
        if (inCheck(b)) {
          return false;
        } 
        if (b.getChessPiece(myPos.first, myPos.second - 1) != nullptr) {
          return false;
        }
        if (b.getChessPiece(myPos.first, myPos.second - 2) != nullptr) {
          return false;
        }
        if (enemyCanMove({myPos.first, myPos.second - 1}, b)) {
          return false;
        }
        if (enemyCanMove({myPos.first, myPos.second - 2}, b)) {
          return false;
        }
        return true;
      } else {
        return false; // not a rook
      }
    } else if (dest == castleRight) {
      const pair<int, int> rookPos = {myPos.first, 7};
      const ChessPiece *r = b.getChessPiece(rookPos.first, rookPos.second);
      if (r == nullptr) {
        return false; // rook not there
      }
      if (r->getType() == ChessType::ROOK) {
        if (r->moved()) {
          return false;
        }
        if (inCheck(b)) {
          return false;
        } 
        if (b.getChessPiece(myPos.first, myPos.second + 1) != nullptr) {
          return false;
        }
        if (b.getChessPiece(myPos.first, myPos.second + 2) != nullptr) {
          return false;
        }
        if (enemyCanMove({myPos.first, myPos.second + 1}, b)) {
          return false;
        }
        if (enemyCanMove({myPos.first, myPos.second + 2}, b)) {
          return false;
        }
        return true;
      } else {
        return false; // not a rook
      }
    }
  }
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

bool King::enemyCanMove(const std::pair<int, int> pos, const Board &b) const {
  const Color myColor = getColor();
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

King::King(Color c, int row, int col): ChessPiece{c, row, col} {}

bool King::inCheck(const Board &b) const {
  return enemyCanMove(getPosition(), b);
}
