#include "Computer3.h"
#include "ChessPiece.h"

#include "Board.h"
#include "Team.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> Computer3::doGetMove() {
    // think like ur enemy
    pair<pair<int, int>, pair<int, int>> move = c2.getMove();

    pair<int, int> oppStart = move.first;
    pair<int, int> oppDest = move.second;

    if (b->getChessPiece(oppDest.first, oppDest.second) &&
        b->getChessPiece(oppDest.first, oppDest.second)->getColor() == homeTeam->getColor()) {
        // try to escape
        vector<vector<bool>> table(8, vector<bool>(8, false));
        for (int i = 0; i < (int)oppTeam->getPieces().size(); i++) {
            for (int j = 0; j < (int)oppTeam->getPieces().at(i)->getPossibleMoves(*b).size(); j++) {
                pair<int, int> enemyMove = oppTeam->getPieces().at(i)->getPossibleMoves(*b)[j];
                table[enemyMove.first][enemyMove.second] = true;
            }
        }
        const ChessPiece * myPiece = b->getChessPiece(oppDest.first, oppDest.second);
        for (int i = 0; i < (int)myPiece->getPossibleMoves(*b).size() ; i++) {
            pair<int, int> myMove =  myPiece->getPossibleMoves(*b)[i];
            if (table[myMove.first][myMove.second] == false) {
                return {oppDest, myMove};
            }
        }
    }
    return Computer2::getMove();
}

void Computer3::doSetup(Board *b, Team *homeTeam, Team *oppTeam) {
    this->b = b;
    this->homeTeam = homeTeam;
    this->oppTeam = oppTeam;
    c2.setup(b, oppTeam, homeTeam);
}

Computer3::Computer3() : c2{Computer2{}} {}

Computer3::~Computer3() {}

pair<pair<int, int>, pair<int, int>> Computer3::getMove() {
  return Computer3::doGetMove();
}
