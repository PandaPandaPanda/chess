#include "Computer1.h"
#include "Computer.h"

#include "Game.h"
#include "Board.h"
#include "Team.h"

#include <algorithm>

using namespace std;

void Computer1::doPlay(Game *g) {
  const ChessPiece *cp = nullptr;

  do {
    cp = t->getPieces().at(getRandomNum(t->getPieces().size()-1));
  } while(cp->getPossibleMoves(*b).size() <= 0);

  pair<int, int> move;
  if (cp->getPossibleMoves(*b).size() == 1) {
    move = cp->getPossibleMoves(*b)[0];
  } else {
    move = cp->getPossibleMoves(*b).at(getRandomNum(cp->getPossibleMoves(*b).size()-1));
  }
  
  cout << "move from " << (char)(cp->getPosition().second + 'a') << (char)(8 - cp->getPosition().first + '0') << " to "  << (char)(move.second + 'a') << (char)(8 - move.first + '0') << endl;
  g->move(cp->getPosition(), move);
  
  cout << *g;
}

void Computer1::doSetup(Board *b, Team *t) {
  this->b = b;
  this->t = t;
}

Computer1::Computer1() {

}
