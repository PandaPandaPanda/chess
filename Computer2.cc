#include "Computer2.h"

#include "Board.h"
#include "Computer.h"
#include "Team.h"

using namespace std;

void Computer2::doPlay(Game *g) {
    cout << "debug 21" << endl;
    pair<int, int> start;
    pair<int, int> dest = {-1, -1};

    bool escape = false;
    for (int i = 0; i < (int)t->getPieces().size(); i++) {
        const ChessPiece *cp = t->getPieces().at(i);
        for (int j = 0; j < (int)cp->getPossibleMoves(*b).size(); j++) {
            pair<int, int> tempMove = cp->getPossibleMoves(*b)[j];
            if (b->getChessPiece(tempMove.first, tempMove.second) != nullptr &&
                b->getChessPiece(tempMove.first, tempMove.second)->getColor() != g->getTurnColor()) {
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
        Computer1::doPlay(g);
        return;
    }

    cout << "debug 23" << endl;
    cout << "dest from " << (char)(start.second + 'a') << (char)(8 - start.first + '0') << " to " << (char)(dest.second + 'a') << (char)(8 - dest.first + '0') << endl;
    g->move(start, dest);
    cout << "debug 24" << endl;
    cout << *g;
}

void Computer2::doSetup(Board *b, Team *t) {
    this->b = b;
    this->t = t;
}

Computer2::Computer2() {
    // todo
}
