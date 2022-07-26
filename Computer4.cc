#include "Computer4.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Board.h"
#include "Team.h"

using namespace std;

// Avoids capturing, unless we could make a beneficial trade piece
pair<pair<int, int>, pair<int, int>> Computer4::doGetMove() {
    // think like ur enemy
    pair<pair<int, int>, pair<int, int>> move = c2.getMove();

    pair<int, int> oppDest = move.second;

    if (b->getChessPiece(oppDest.first, oppDest.second) &&
        b->getChessPiece(oppDest.first, oppDest.second)->getColor() == homeTeam->getColor()) {
        // Look for a trade
        pair<pair<int, int>, pair<int, int>> tradeMove = Computer2::getMove();

        int myGain = b->getChessPiece(tradeMove.second.first, tradeMove.second.second) ? b->getChessPiece(tradeMove.second.first, tradeMove.second.second)->getValue() : 0;
        int oppGain = b->getChessPiece(oppDest.first, oppDest.second) ? b->getChessPiece(oppDest.first, oppDest.second)->getValue() : 0;
        // fair trade
        if (myGain >= oppGain) {
            return tradeMove;
        }

        // try to escape
        vector<vector<bool>> table(8, vector<bool>(8, false));
        for (int i = 0; i < (int)oppTeam->getPieces().size(); i++) {
            if (oppTeam->getPieces().at(i)->getType() == ChessType::PAWN) {
                const Pawn * myPawn = dynamic_cast<const Pawn *>(oppTeam->getPieces().at(i));
                for (int j = 0; j < (int) myPawn->possibleAttacks(*b).size(); j++ ) {
                    pair<int, int> enemyMove = myPawn->possibleAttacks(*b)[j];
                    table[enemyMove.first][enemyMove.second] = true;
                }
            } else {
                for (int j = 0; j < (int)oppTeam->getPieces().at(i)->getPossibleMoves(*b).size(); j++) {
                    pair<int, int> enemyMove = oppTeam->getPieces().at(i)->getPossibleMoves(*b)[j];
                    table[enemyMove.first][enemyMove.second] = true;
                }
            }
        }
        const ChessPiece *myPiece = b->getChessPiece(oppDest.first, oppDest.second);
        for (int i = 0; i < (int)myPiece->getPossibleMoves(*b).size(); i++) {
            pair<int, int> myMove = myPiece->getPossibleMoves(*b)[i];
            if (table[myMove.first][myMove.second] == false) {
                return {oppDest, myMove};
            }
        }
    }

    return Computer2::getMove();
}

void Computer4::doSetup(Board *b, Team *homeTeam, Team *oppTeam) {
    this->b = b;
    this->homeTeam = homeTeam;
    this->oppTeam = oppTeam;
    c2.setup(b, oppTeam, homeTeam);
}

Computer4::Computer4() : c2{Computer2{}} {
    // todo
}

Computer4::~Computer4() {
    // todo
}

pair<pair<int, int>, pair<int, int>> Computer4::getMove() {
    return doGetMove();
}
