#include "Computer2.h"

#include "Board.h"
#include "Computer.h"
#include "Team.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> Computer2::doGetMove() {

    // prefer capturing
    int value = 0;
    pair<pair<int, int>, pair<int, int>> res;
    vector<vector<int>> enemyPos(8, vector<int>(8, 0));
    for (int i = 0; i < (int)oppTeam->getPieces().size(); i++) {
        pair<int, int> pos = oppTeam->getPieces().at(i)->getPosition();
        enemyPos[pos.first][pos.second] = oppTeam->getPieces().at(i)->getValue();
    }


    for (int i = 0; i < (int)homeTeam->getPieces().size(); i++) {
        const ChessPiece *myPiece = homeTeam->getPieces().at(i);
        myPiece->getPossibleMoves(*b);
        for (int i = 0; i < (int)myPiece->getPossibleMoves(*b).size(); i++) {
            pair<int, int> myMove = myPiece->getPossibleMoves(*b)[i];
            if (enemyPos[myMove.first][myMove.second] != 0) {
                if (enemyPos[myMove.first][myMove.second] > value) {
                    value = enemyPos[myMove.first][myMove.second];
                    res = {myPiece->getPosition(), myMove};
                }
            }
        }
    }
    if (value > 0) {
        return res;
    }

    // prefer checking
    for (int i = 0; i < (int)homeTeam->getPieces().size(); i++) {
        const ChessPiece *myPiece = homeTeam->getPieces().at(i);
        for (int i = 0; i < (int)myPiece->getPossibleMoves(*b).size(); i++) {
            pair<int, int> myMove = myPiece->getPossibleMoves(*b)[i];

            if (b->checkInCheck(myMove, oppTeam->getKing()->getPosition())) {
                return {myPiece->getPosition(), myMove};
            }
        }
    }

    return Computer1::getMove();
}

void Computer2::doSetup(Board *b, Team *homeTeam, Team *oppTeam) {
    this->b = b;
    this->homeTeam = homeTeam;
    this->oppTeam = oppTeam;
}

Computer2::Computer2() {}

pair<pair<int, int>, pair<int, int>> Computer2::getMove() {
    return Computer2::doGetMove();
}
