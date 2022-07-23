#include <iostream>
#include <string>
#include "Game.h"
#include "Player.h"
#include "Human.h"
#include "Computer1.h"
#include "Computer2.h"
#include "Computer3.h"
#include "Computer4.h"

using namespace std;

// where do we get the board and team from?
Player *createPlayer(string player, const Board &b, const Team &t) {
  if (player == "human") {
    return new Human{};
  } else if (player == "computer1") {
    return new Computer1{b, t};
  } else if (player == "computer2") {
    return new Computer2{b, t};
  } else if (player == "computer3") {
    return new Computer3{b, t};
  } else if (player == "computer4") {
    return new Computer4{b, t};
  } else {
    return nullptr;
  }
}

int main() {
  string cmd;
  Game game;
  while (cin >> cmd) {
    if (cmd == "game") {
      string whiteplayer, blackplayer;
      cin >> whiteplayer >> blackplayer;
      // Player *whitePlayer = createPlayer(whiteplayer, ); // where to get board and team
      // Player *blackPlayer = createPlayer(blackplayer, );
      // game.setPlayers(blackPlayer, whitePlayer);
    } else if (cmd == "resign") {
      game.resign();
    } else if (cmd == "move") {
      // game.move(); // todo, not sure how to do this
    } else if (cmd == "setup") {
      game.setup();
    } else {
      cout << "Invalid command: " << cmd << endl;
    }

  }
}
