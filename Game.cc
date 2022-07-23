#include "Game.h"

#include <memory>

#include "Board.h"
#include "Color.h"
#include "Computer.h"
#include "Exception.h"
#include "Player.h"
#include "Team.h"

using namespace std;

const int BOARDSIZE = 8;

bool Game::canMove(pair<int, int> start, pair<int, int> dest) {
  const ChessPiece *startPiece = b.getChessPiece(start.first, start.second);

  // isValid start&end
  if (start.first < 0 || start.second >= BOARDSIZE || dest.first < 0 ||
      dest.second >= BOARDSIZE) {
    return false;
  }

  // check owning pieace at start
  if (!startPiece) {
    return false;
  }

  if (startPiece->getColor() != turnColor) {
    return false;
  }

  // check reachable dest
  const ChessPiece *destPiece = b.getChessPiece(dest.first, dest.second);
  if (destPiece && destPiece->getColor() == turnColor) {
    return false;
  }

  if (!startPiece->canMove(dest, b)) {
    return false;
  }

  return true;
}

bool Game::isCheckMate() {
  Team *curTeam = turnColor == Color::Black ? &black : &white;
  Team *oppTeam = turnColor == Color::Black ? &white : &black;
  vector<pair<int, int>> kingPossibleMoves =
      curTeam->getKing()->getPossibleMoves(b);

  for (int i = kingPossibleMoves.size() - 1; i >= 0; i--) {
    bool badMove = false;
    for (ChessPiece *oppPieace : oppTeam->getPieaces()) {
      for (pair<int, int> oppPossibleMoves : oppPieace->getPossibleMoves(b)) {
        if (oppPossibleMoves == kingPossibleMoves[i]) {
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

  return true;
}

Game::Game()
    : b{Board()},
      t{TextDisplay()},
      turnColor{Color::Black},
      black{Team(Color::Black)},
      white{Team(Color::White)},
      endgame{false} {}

void Game::setup(Player *blackPlayer, Player *whitePlayer) {
  setPlayer(Color::Black, blackPlayer);
  setPlayer(Color::White, whitePlayer);
}

void Game::setPlayer(Color c, Player *p) {
  Team *homeTeam;
  if (c == Color::Black) {
    homeTeam = &black;
    black.setPlayer(p);
  } else if (c == Color::White) {
    homeTeam = &white;
    white.setPlayer(p);
  }

  if (p->getType() == PlayerType::C) {
    dynamic_cast<Computer *>(p)->setup(&b, homeTeam);
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

  b.move(start, dest);

  if (isCheckMate()) {
    endgame = true;
    winner = turnColor;  // player wins
  }

  turnColor = turnColor == Color::Black ? Color::White : Color::Black;
}

void Game::resign() {
  endgame = true;
  winner =
      turnColor == Color::Black ? Color::White : Color::Black;  // opponent wins
}

bool Game::hasGameEnded() { return endgame; }
