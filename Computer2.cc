#include "Computer2.h"

#include "Board.h"
#include "Computer.h"
#include "Team.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> Computer2::doGetMove() {
    cout << "debug 21" << endl;

    if (!homeTeam) {
        cout << "debug hometeam empty" << endl;
    }
    if (!oppTeam) {
        cout << "debug oppTeam empty" << endl;
    }

    cout << "debug 22" << endl;

    // prefer capturing
    vector<vector<bool>> enemyPos(8, vector<bool>(8, false));
    for (int i = 0; i < (int)oppTeam->getPieces().size(); i++) {
        pair<int, int> pos = oppTeam->getPieces().at(i)->getPosition();
        enemyPos[pos.first][pos.second] = true;
    }

    cout << "debug 23" << endl;

    for (int i = 0; i < (int)homeTeam->getPieces().size(); i++) {
        if (!homeTeam->getPieces().at(i)) {
            cout << "debug empty" << endl;
        }
        cout << "debug 24" << endl;
        const ChessPiece *myPiece = homeTeam->getPieces().at(i);
        cout << "debug 25" << endl;
        cout << myPiece->getType() << endl;
        myPiece->getPossibleMoves(*b);
        cout << "debug 26" << endl;
        for (int i = 0; i < (int)myPiece->getPossibleMoves(*b).size(); i++) {
            pair<int, int> myMove = myPiece->getPossibleMoves(*b)[i];
cout << "debug 27" << endl;
            if (enemyPos[myMove.first][myMove.second] == true) {
                return {myPiece->getPosition(), myMove};
            }
            cout << "debug 28" << endl;
        }
    }

    cout << "debug 29" << endl;

    // prefer checking
    for (int i = 0; i < (int)homeTeam->getPieces().size(); i++) {
        const ChessPiece *myPiece = homeTeam->getPieces().at(i);
        for (int i = 0; i < (int)myPiece->getPossibleMoves(*b).size(); i++) {
            pair<int, int> myMove = myPiece->getPossibleMoves(*b)[i];

            if (b->checkInCheck(myMove, oppTeam->getKing()->getPosition())) {
                return {myPiece->getPosition(), myMove};
            }
            cout << "debug 30" << endl;
        }
    }

    cout << "debug 31" << endl;
    return Computer1::getMove();
}

void Computer2::doSetup(Board *b, Team *homeTeam, Team *oppTeam) {
    this->b = b;
    this->homeTeam = homeTeam;
    this->oppTeam = oppTeam;
    Computer1::doSetup(b, homeTeam, oppTeam);
}

Computer2::Computer2() {}

pair<pair<int, int>, pair<int, int>> Computer2::getMove() {
    return Computer2::doGetMove();
}
