#include "Game.h"
#include "Board.h"
#include "Color.h"
#include "Team.h"
#include "Exception.h"

#include <memory>

using namespace std;

bool Game::canMove(pair<int, int> start, pair<int, int> dest) {
    Color turnColor = turn % 2 ? Color::Black : Color::White;
    const ChessPiece *startPieace = b.getChessPieace(start.first, start.second);

    // check owning pieace at start
    if (!startPieace) {
        return false;
    }

    if (startPieace->getColor() != turnColor) {
        return false;
    }

    // check reachable dest
    const ChessPiece *destPieace = b.getChessPieace(dest.first, dest.second);
    if (destPieace && destPieace->getColor() == turnColor) {
        return false;
    }

    return true;
}

Game::Game() : b{Board()},
      t{TextDisplay()},
      turn{0},
      black{Team(Color::Black)},
      white{Team(Color::White)} {}

void Game::setup(Player *blackPlayer, Player *whitePlayer) {
    setPlayer(Color::Black, blackPlayer);
    setPlayer(Color::White, whitePlayer);
}

void Game::setPlayer(Color c, Player *p) {
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

    b.move(start, dest);
}

void Game::resign() {
    turn++;
}

