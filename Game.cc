#include "Game.h"

#include <iostream>
#include <memory>

#include "Board.h"
#include "Cell.h"
#include "ChessPiece.h"
#include "Color.h"
#include "Computer.h"
#include "Exception.h"
#include "King.h"
#include "Pawn.h"
#include "Player.h"
#include "Team.h"
#include "sdl_wrap.h"

using namespace std;

const int BOARDSIZE = 8;

// pair<row, col>
bool Game::canMove(pair<int, int> start, pair<int, int> dest) {
    const ChessPiece* startPiece = b.getChessPiece(start.first, start.second);
    // isValid start&end
    if (start.first < 0 || start.second >= BOARDSIZE || dest.first < 0 ||
        dest.second >= BOARDSIZE) {
        return false;
    }

    // check owning piece at start
    if (!startPiece) {
        return false;
    }

    if (startPiece->getColor() != turnColor) {
        return false;
    }

    // check reachable dest
    const ChessPiece* destPiece = b.getChessPiece(dest.first, dest.second);
    if (destPiece && destPiece->getColor() == turnColor) {
        return false;
    }

    if (!startPiece->canMove(dest, b)) {
        return false;
    }

    return true;
}

bool Game::isCheckMate() {
    Color oppColor = turnColor == Color::Black ? Color::White : Color::Black;
    Team* curTeam = turnColor == Color::Black ? &black : &white;
    Team* oppTeam = turnColor == Color::Black ? &white : &black;

    // 1) The king is in check
    if (!b.checkInCheck(oppColor, oppTeam->getKing())) {
        return false;
    } else {
        cout << (oppColor == Color::Black? "Black":"White") << " is in check." << endl;
    }

    // 2) There is no move that the king can make that takes it out of check.
    vector<pair<int, int>> kingPossibleMoves =
        oppTeam->getKing()->getPossibleMoves(b);
    for (int i = kingPossibleMoves.size() - 1; i > 0; i--) {
        bool badMove = false;
        for (const ChessPiece* curPiece : curTeam->getPieces()) {
            for (pair<int, int> curPossibleMoves : curPiece->getPossibleMoves(b)) {
                if (curPossibleMoves == kingPossibleMoves[i]) {
                    badMove = true;
                    break;
                }
            }
            if (badMove) {
                break;
            }
        }

        if (badMove) {
            kingPossibleMoves.pop_back();
        } else {
            return false;
        }
    }

    const pair<const ChessPiece*, int> pair = oneAttackingPiece(oppTeam->getKing());
    const ChessPiece* attackingPiece = pair.first;
    const int count = pair.second;
    if (count == 0) {
        cout << "This shouldn't happen" << endl;
        return false;
    }
    if (count == 1) {
        // 3) It is not possible to capture the attacking piece (impossible if there is more than one attacking piece).
        if (canCaptureAttacking(attackingPiece)) {
            return false;
        }

        // 4) It is not possible to interpose a piece between the king and the attacking piece (impossible if there is more than one attacking piece, impossible if the attacking piece is a knight).
        if (canBlockCheck(attackingPiece, oppTeam->getKing()) && attackingPiece->getType() != ChessType::KNIGHT) {
            return false;
        }
    }
    // count > 1, so checkmate is guaranteed

    return true;
}

pair<const ChessPiece*, int> Game::oneAttackingPiece(const ChessPiece* king) {
    int count = 0;
    Team* enemyTeam = king->getColor() == Color::White ? &black : &white;
    const ChessPiece* attackingPiece = nullptr;
    for (const auto enemy : enemyTeam->getPieces()) {
        if (enemy->canMove(king->getPosition(), b)) {
            ++count;
            if (attackingPiece != nullptr) {
                return {nullptr, count};  // found two attacking pieces
            }
            attackingPiece = enemy;
        }
    }
    return {attackingPiece, count};
}

bool Game::canCaptureAttacking(const ChessPiece* attackingPiece) {
    Team* attackedTeam = attackingPiece->getColor() == Color::Black ? &white : &black;
    for (const auto p : attackedTeam->getPieces()) {
        if (p->canMove(attackingPiece->getPosition(), b)) {
            return true;
        }
    }
    return false;
}

bool Game::canBlockCheck(const ChessPiece* attackingPiece, const ChessPiece* king) {
    ChessType t = attackingPiece->getType();
    if (t != ChessType::BISHOP && t != ChessType::ROOK && t != ChessType::QUEEN) {
        return false;
    }
    Team* kingTeam = king->getColor() == Color::Black ? &black : &white;
    vector<pair<int, int>> blockablePositions;
    int dr = 0;
    int dc = 0;
    pair<int, int> atckPos = attackingPiece->getPosition();
    const pair<int, int> kingPos = king->getPosition();
    if (kingPos.first < atckPos.first) {
        dr = -1;
    } else if (atckPos.first < kingPos.first) {
        dr = 1;
    }
    if (kingPos.second < atckPos.second) {
        dc = -1;
    } else if (atckPos.second < kingPos.second) {
        dc = 1;
    }
    while (atckPos != kingPos) {
        atckPos.first += dr;
        atckPos.second += dc;
        blockablePositions.emplace_back(atckPos);
    }
    for (const auto blockablePosition : blockablePositions) {
        for (const auto friendly : kingTeam->getPieces()) {
            if (friendly->getType() != ChessType::KING && friendly->canMove(blockablePosition, b)) {
                return true;
            }
        }
    }
    return false;
}

bool Game::knightAttackingKing(const ChessPiece* king) {
    Team* enemyTeam = king->getColor() == Color::White ? &black : &white;
    for (const auto enemy : enemyTeam->getPieces()) {
        if (enemy->getType() == ChessType::KNIGHT && enemy->canMove(king->getPosition(), b)) {
            return true;
        }
    }
    return false;
}

bool Game::isStaleMate() {
    Team* team = turnColor == Color::Black ? &black : &white;
    if (((King*)team->getKing())->inCheck(b)) {
        return false;
    }
    for (const ChessPiece* p : team->getPieces()) {
        if (p->getPossibleMoves(b).size() > 0) {
            return false;
        }
    }
    return true;
}

void Game::invalidateEnPassant() {
    Team* team = turnColor == Color::Black ? &black : &white;
    for (auto p : team->getPieces()) {
        if (p->getType() == ChessType::PAWN) {
            ((Pawn*)p)->invalidateEnPassantCapturable();
        }
    }
}

Game::Game()
    : t{new TextDisplay()}, scr{new Screen{640, 640}}, b{Board(t, scr)}, black{Team(Color::Black, &b)}, white{Team(Color::White, &b)}, turnColor{Color::White}, steps{0}, endgame{false} {
}

Game::~Game() {
    delete t;
    delete scr;
}

pair<bool, Color>
Game::strToColor(string color) {
    Color output = Color::White;
    if (color == "Black" || color == "black" || color == "b" || color == "B") {
        output = Color::Black;
    } else if (color == "White" || color == "white" || color == "w" ||
               color == "W") {
        output = Color::White;
    } else {
        cout << "invalid color" << endl;
        return make_pair(false, output);
    }
    return make_pair(true, output);
}

void Game::setup() {
    string cmd;
    while (true) {
        cin >> cmd;
        if (cmd == "+") {
            //+ [B/W/black/white] [Piece] [a-h][1-8]
            string color;
            char t;
            string pos;
            cin >> color >> t >> pos;
            pair<bool, Color> output = strToColor(color);
            if (output.first) {
                turnColor = output.second;
                b.addPiece(output.second, t, pos);
            } else {
                cout << "invalid color" << endl;
            }
            cout << *this;
        } else if (cmd == "-") {
            //- [a-h][1-8]
            string pos;
            cin >> pos;
            b.removePiece(pos);
            cout << *this;
        } else if (cmd == "=") {
            string color;
            cin >> color;
            pair<bool, Color> output = strToColor(color);
            if (output.first) {
                turnColor = output.second;
            } else {
                cout << "invalid color" << endl;
            }
            // todo
        } else if (cmd == "done") {
            if (b.verify()) {
                // todo: add all pieces on the board to their respective teams post
                // setup
                break;
            } else {
                cout << "The state of the board is not valid. Make sure that" << endl;
                cout << "the board contains exactly one white king and exactly" << endl;
                cout << "one black king; that no pawns are on the first or last"
                     << endl;
                cout << "row of the board; and that neither king is in check." << endl;
            }
        } else {
            cout << "Invalid setup command: " << cmd << endl;
        }
    }
}

void Game::setPlayer(Color c, Player* p) {
    Team* homeTeam;
    Team* oppTeam;
    if (c == Color::Black) {
        homeTeam = &black;
        oppTeam = &white;
        black.setPlayer(p);
    } else if (c == Color::White) {
        homeTeam = &white;
        oppTeam = &black;
        white.setPlayer(p);
    }

    if (p->getType() == PlayerType::C) {
        dynamic_cast<Computer*>(p)->setup(&b, homeTeam, oppTeam);
    };

    if (c == Color::Black) {
        black.setPlayer(p);
    } else if (c == Color::White) {
        white.setPlayer(p);
    }
}

bool Game::move(std::pair<int, int> start, std::pair<int, int> dest) {
    if (!canMove(start, dest)) {
        return false;
    }

    if (!b.getChessPiece(start.first, start.second)->canMove(dest, b)) {
        return false;
    }

    const ChessPiece* p = b.getChessPiece(dest.first, dest.second);
    if (p) {  // normal capturing
        // capturing king
        if (p->getType() == ChessType::KING) {
            endgame = true;
            winner = turnColor;
            if (turnColor == Color::Black) {
                winner = Color::Black;
                cout << "Black wins!" << endl;
            } else {
                winner = Color::White;
                cout << "White wins!" << endl;
            }
            return true;
        }
        if (turnColor == Color::White) {
            black.removePiece(p);
        } else {
            white.removePiece(p);
        }
    } else if (b.getChessPiece(start.first, start.second)->getType() == ChessType::PAWN && dest.second != start.second) {  // en passant capturing
        if (turnColor == Color::White) {
            black.removePiece(b.getChessPiece(dest.first + 1, dest.second));
        } else {
            white.removePiece(b.getChessPiece(dest.first - 1, dest.second));
        }
    }
    if (b.getChessPiece(start.first, start.second)->getType() == ChessType::KING) {  // check for castling
        if (start.second + 2 == dest.second) {
            b.move({start.first, 7}, {start.first, start.second + 1});
        } else if (start.second - 2 == dest.second) {
            b.move({start.first, 0}, {start.first, start.second - 1});
        }
    }

    bool promote = false;
    ChessType ct;

    if (b.getChessPiece(start.first, start.second)->getType() == ChessType::PAWN && (dest.first == 0 || dest.first == 7)) {  // promotion
        char t;
        if (turnColor == Color::Black && black.getPlayer()->getType() == PlayerType::C) {
            t = black.getPlayer()->getPromotionChoice();
        } else if (turnColor == Color::White && white.getPlayer()->getType() == PlayerType::C) {
            t = white.getPlayer()->getPromotionChoice();
        } else {
            cin >> t;
        }
        // promote to what

        switch (t) {
            case 'Q':
                ct = ChessType::QUEEN;
                promote = true;
                break;
            case 'R':
                ct = ChessType::ROOK;
                promote = true;
                break;
            case 'B':
                ct = ChessType::BISHOP;
                promote = true;
                break;
            case 'N':
                ct = ChessType::KNIGHT;
                promote = true;
                break;
            default:
                cout << "Promoted type can only be one of Q/R/B/N." << endl;
                return false;
        }
    }

    b.move(start, dest);

    if (promote) {
        if (turnColor == Color::Black) {
            black.promotePawn((Pawn*)b.getChessPiece(dest.first, dest.second), ct);
        } else {
            white.promotePawn((Pawn*)b.getChessPiece(dest.first, dest.second), ct);
        }
    }

    if (isCheckMate()) {
        endgame = true;
        winner = turnColor;  // player wins
        cout << "Checkmate! ";
        cout << (turnColor == Color::Black ? "Black" : "White") << " wins!";
        cout << endl;
    }

    if (isStaleMate()) {
        endgame = true;
        winner = 'D';  // Draw
        cout << "Stalemate!" << endl;
    }

    invalidateEnPassant();

    turnColor = turnColor == Color::Black ? Color::White : Color::Black;
    steps++;

    return true;
}

void Game::resign() {
    endgame = true;

    // opponent wins
    if (turnColor == Color::Black) {
        winner = Color::White;
        cout << "White wins!" << endl;
    } else {
        winner = Color::Black;
        cout << "Black wins!" << endl;
    }
}
ostream&
operator<<(std::ostream& o, Game& g) {
    o << *g.t;
    g.scr->update();
    return o;
};

bool Game::hasGameEnded() {
    return endgame;
}

int Game::getSteps() {
    return steps;
}

Color Game::getTurnColor() {
    return turnColor;
}

char Game::getWinner() {
    return winner;
}
