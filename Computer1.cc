#include "Computer1.h"

#include <algorithm>

#include "Board.h"
#include "Computer.h"
#include "Game.h"
#include "Team.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> Computer1::doGetMove() {
    const ChessPiece *cp = nullptr;
    cout << "debug 11" << endl;
    if (homeTeam->getPieces().size() == 1) {
        cout << "debug 111" << endl;
        cp = homeTeam->getPieces().at(0);
    } else {
        cout << "debug 112" << endl;
        do {
            cout << "debug 1121" << endl;
            homeTeam->getPieces();
            cout << "debug 1122" << endl;
            cp = homeTeam->getPieces().at(getRandomNum(homeTeam->getPieces().size() - 1));
            cout << "debug 1123" << endl;
            cout << "debug " <<cp->getType() << endl;
            cout << "debug 1124" << endl;
        } while (cp->getPossibleMoves(*b).size() <= 0);
    }

    cout << "debug 12" << endl;
    pair<int, int> dest;
    if (cp->getPossibleMoves(*b).size() == 1) {
        dest = cp->getPossibleMoves(*b)[0];
    } else {
        dest = cp->getPossibleMoves(*b).at(getRandomNum(cp->getPossibleMoves(*b).size() - 1));
    }
    cout << "debug 13" << endl;

    return {cp->getPosition(), dest};
}

void Computer1::doSetup(Board *b, Team *homeTeam, Team *oppTeam) {
    this->b = b;
    this->homeTeam = homeTeam;
    this->oppTeam = oppTeam;
}

Computer1::Computer1() {
}

pair<pair<int, int>, pair<int, int>> Computer1::getMove() {
    return Computer1::doGetMove();
}
