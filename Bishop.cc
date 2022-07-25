#include <vector>
#include "Board.h"
#include "Bishop.h"
#include "ChessPiece.h"

using namespace std;

vector<pair<int, int>> Bishop::possibleMoves(const Board &b) const {
  vector<pair<int, int>> moves;

  // check all four diagonal directions
  // NE
  possibleMovesDirection(b, -1, 1, moves);
  // NW
  possibleMovesDirection(b, -1, -1, moves);
  // SW
  possibleMovesDirection(b, 1, -1, moves);
  // SE
  possibleMovesDirection(b, 1, 1, moves);

  return moves;
}

bool Bishop::canDoMove(const pair<int, int> dest, const Board &b) const {
  pair<int, int> pos = getPosition();
  if (abs(dest.first - pos.first) != abs(dest.second - pos.second)) {
    return false;
  }

  // figure out the diagonal direction we are moving
  int dr = dest.first > pos.first ? 1 : -1;
  int dc = dest.second > pos.second ? 1 : -1;

  // check board along that direction
  const Color myColor = getColor();
  pos.first += dr;
  pos.second += dc;
  while (inBounds(pos)) {
    const ChessPiece *p = b.getChessPiece(pos.first, pos.second);
    if (p == nullptr) { // nothing there
      if (pos == dest) { // trying to move to empty Cell
        return true; 
      }
    } else {
      if (myColor == p->getColor()) { // blocked by own piece or trying to take own piece
        return false;
      } else { // blocked by enemy piece or tring to take enemy piece
        if (pos == dest) { // trying to take enemy piece
          return true;
        } else { // blocked by enemy piece
          return false;
        }
      }
    }
    pos.first += dr;
    pos.second += dc;
  }

  return false;
}

int Bishop::value() const {
  return 3;
}

ChessType Bishop::type() const {
  return ChessType::BISHOP;
}

void Bishop::doMovePiece(const pair<int, int> newPos) {
  // no op
}

Bishop::Bishop(Color c, int row, int col): ChessPiece{c, row, col} {}
