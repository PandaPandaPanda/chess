#include "Rook.h"

#include "Board.h"

using namespace std;

vector<pair<int, int>> Rook::possibleMoves(const Board &b) const {
  vector<pair<int, int>> moves;

  // check all four straight directions
  // N
  possibleMovesDirection(b, -1, 0, moves);
  // E
  possibleMovesDirection(b, 0, 1, moves);
  // S
  possibleMovesDirection(b, 1, 0, moves);
  // W
  possibleMovesDirection(b, 0, -1, moves);

  return moves;
}

bool Rook::canDoMove(const pair<int, int> dest, const Board &b) const {
  pair<int, int> pos = getPosition();
  if (pos.first != dest.first && pos.second != dest.second) {
    return false;
  }

  // figure out the straight direction we are moving
  int dr = 0;
  int dc = 0;
  if (dest.first > pos.first) {
    dr = 1;
  } else if (dest.first < pos.first) {
    dr = -1;
  }
  if (dest.second > pos.second) {
    dc = 1;
  } else if (dest.second < pos.second) {
    dc = -1;
  }

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

int Rook::value() const {
  return 5;
}

ChessType Rook::type() const {
  return ChessType::ROOK;
}

Rook::Rook(Color c, int row, int col): ChessPiece{c, row, col} {}
