#include "Game.h"

#include <iostream>
#include <memory>

#include "Board.h"
#include "Cell.h"
#include "ChessPiece.h"
#include "Color.h"
#include "Computer.h"
#include "Exception.h"
#include "Player.h"
#include "Team.h"

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

  // check legal move
  for (auto possibleMove : startPiece->getPossibleMoves(b)) {
    if (possibleMove.first == dest.first &&
        possibleMove.second == dest.second) {
      return true;
    }
  }
  return false;
}

bool Game::isCheckMate() {
  Team* curTeam = turnColor == Color::Black ? &black : &white;
  Team* oppTeam = turnColor == Color::Black ? &white : &black;
  curTeam->getKing();
  vector<pair<int, int>> kingPossibleMoves =
      curTeam->getKing()->getPossibleMoves(b);
  for (int i = kingPossibleMoves.size() - 1; i >= 0; i--) {
    bool badMove = false;
    for (const ChessPiece* oppPiece : oppTeam->getPieces()) {
      for (pair<int, int> oppPossibleMoves : oppPiece->getPossibleMoves(b)) {
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
    : t{new TextDisplay()},
      b{Board(t)},
      black{Team(Color::Black, &b)},
      white{Team(Color::White, &b)},
      turnColor{Color::Black},
      endgame{false} {}

Game::~Game() { delete t; }

pair<bool, Color> Game::strToColor(string color) {
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
  if (c == Color::Black) {
    homeTeam = &black;
    black.setPlayer(p);
  } else if (c == Color::White) {
    homeTeam = &white;
    white.setPlayer(p);
  }

  if (p->getType() == PlayerType::C) {
    dynamic_cast<Computer*>(p)->setup(&b, homeTeam);
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

  return true;
}

void Game::resign() {
  endgame = true;
  winner =
      turnColor == Color::Black ? Color::White : Color::Black;  // opponent wins
}
ostream& operator<<(std::ostream& o, Game& g) {
  o << *g.t;
  return o;
};

bool Game::hasGameEnded() { return endgame; }
