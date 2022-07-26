#include "Computer2.h"

#include "Board.h"
#include "Computer.h"
#include "Team.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> Computer2::doGetMove() {
    cout << "debug 21" << endl;
    pair<int, int> start;
    pair<int, int> dest = {-1, -1};

    bool escape = false;
    for (int i = 0; i < (int)homeTeam->getPieces().size(); i++) {
        const ChessPiece *cp = homeTeam->getPieces().at(i);
        for (int j = 0; j < (int)cp->getPossibleMoves(*b).size(); j++) {
            pair<int, int> tempMove = cp->getPossibleMoves(*b)[j];
            if (b->getChessPiece(tempMove.first, tempMove.second) != nullptr &&
                b->getChessPiece(tempMove.first, tempMove.second)->getColor() != homeTeam->getColor()) {
                start = cp->getPosition();
                dest = tempMove;
                escape = true;
                break;
            }
        }
        if (escape) {
            break;
        }
    }

    cout << "debug 22" << endl;
    if (dest.first == -1) {
        return Computer1::doGetMove();
    }

    return {start, dest};
}

void Computer2::doSetup(Board *b, Team *homeTeam, Team* oppTeam) {
    this->b = b;
    this->homeTeam = homeTeam;
    this->oppTeam = oppTeam;
}

Computer2::Computer2() {}
