#include "Team.h"

#include "Board.h"
#include "ChessPiece.h"
#include "Color.h"
#include "Pawn.h"

using namespace std;

Team::Team(Color c, Board *b) : c{c}, b{b} {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      const ChessPiece *tempPiece = b->getChessPiece(i, j);
      if (tempPiece && tempPiece->getColor() == c) {
        this->pieces.push_back(tempPiece);
      }
    }
  }
}

const ChessPiece *Team::getKing() {
  for (int i = 0; i < (int)pieces.size(); i++) {
    if (pieces[i]->getType() == ChessType::KING) {
      return pieces[i];
    }
  }
  return nullptr;  // shouldn't happen
}

const vector<const ChessPiece *> Team::getPieces() { return pieces; }

void Team::setPlayer(Player *p) { this->p = p; }

void Team::removePiece(ChessPiece *cp) {
  for (int i = 0; i < (int)pieces.size(); i++) {
    if (pieces[i]->getType() == cp->getType() &&
        pieces[i]->getPosition() == cp->getPosition()) {
      b->removePiece(pieces[i]->getPosition().first,
                     pieces[i]->getPosition().second);
      pieces.erase(pieces.begin() + i);
      return;
    }
  }
}

void Team::promotePawn(Pawn *cp, ChessType t) {
  for (int i = 0; i < (int)pieces.size(); i++) {
    if (pieces[i] && pieces[i]->getType() == ChessType::PAWN &&
        pieces[i]->getPosition() == cp->getPosition()) {
      Color color = cp->getColor();
      int r = pieces[i]->getPosition().first;
      int c = pieces[i]->getPosition().second;

      b->removePiece(r, c);
      pieces.erase(pieces.begin() + i);

      b->addPiece(color, t, r, c);
      pieces.push_back(b->getChessPiece(r, c));

      return;
    }
  }
}
