#include "Computer1.h"

#include <algorithm>

#include "Board.h"
#include "Computer.h"
#include "Game.h"
#include "Team.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> Computer1::doGetMove() {
    const ChessPiece *cp = nullptr;
    if (homeTeam->getPieces().size() == 1) {
        cp = homeTeam->getPieces().at(0);
    } else {
        do {
            homeTeam->getPieces();
            cp = homeTeam->getPieces().at(getRandomNum(homeTeam->getPieces().size() - 1));
        } while (cp->getPossibleMoves(*b).size() <= 0);
    }

    pair<int, int> dest;
    if (cp->getPossibleMoves(*b).size() == 1) {
        dest = cp->getPossibleMoves(*b)[0];
    } else {
        dest = cp->getPossibleMoves(*b).at(getRandomNum(cp->getPossibleMoves(*b).size() - 1));
    }

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
