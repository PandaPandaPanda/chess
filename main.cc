#include <iostream>
#include <string>

#include "Cell.h"
#include "Computer1.h"
#include "Computer2.h"
#include "Computer3.h"
#include "Computer4.h"
#include "Game.h"
#include "Human.h"
#include "Player.h"
#include "sdl_wrap.h"

using namespace std;

// where do we get the board and team from?
SDL_Runner r;

Player*
createPlayer(string player)
{
  if (player == "human") {
    return new Human{};
  } else if (player == "computer1") {
    return new Computer1{};
  } else if (player == "computer2") {
    return new Computer2{};
  } else if (player == "computer3") {
    return new Computer3{};
  } else if (player == "computer4") {
    return new Computer4{};
  } else {
    return nullptr;
  }
}

pair<int, int>
parseMove(string move)
{
  if (move.size() != 2) {
    return { -1, -1 };
  }

  int row = 7 - (move[1] - '1'); // extra -1 converting number to index
  int col = move[0] - 'a';

  if (row < 0 || row >= 8 || col < 0 || col >= 8) {
    return { -1, -1 };
  }

  return { row, col };
}

int
main()
{
  string cmd;
  Game game;
  Player* whitePlayer;
  Player* blackPlayer;
  cout << game; // print out board is working
  while (cin >> cmd) {
    if (cmd == "game") {
      string whiteType, blackType;
      cin >> whiteType >> blackType;
      whitePlayer = createPlayer(whiteType);
      blackPlayer = createPlayer(blackType);
      game.setPlayer(Color::Black, blackPlayer);
      game.setPlayer(Color::White, whitePlayer);
    } else if (cmd == "resign") {
      game.resign();
    } else if (cmd == "move") {
      string startStr, destStr;
      pair<int, int> start, dest;
      cin >> startStr >> destStr;
      while (cin) {
        start = parseMove(startStr);
        dest = parseMove(destStr);
        if (game.move(start, dest)) {
          cout << game;
          break;
        }
        cout << "Invalid start/dest move" << endl;
        cin >> startStr >> destStr;
      }
    } else if (cmd == "setup") {
      game.setup();
    } else {
      cout << "Invalid command: " << cmd << endl;
    }
  }
}
