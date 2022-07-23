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

using namespace std;

// where do we get the board and team from?
Player *createPlayer(string player) {
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

int main() {
  string cmd;
  Game game;
  Player *whitePlayer;
  Player *blackPlayer;
  while (cin >> cmd) {
    if (cmd == "game") {
      string whiteType, blackType;
      cin >> whiteType >> blackType;
      whitePlayer = createPlayer(whiteType); 
      blackPlayer = createPlayer(blackType); 
    } else if (cmd == "resign") {
      game.resign();
    } else if (cmd == "move") {
      // game.move(); // todo, not sure how to do this
    } else if (cmd == "setup") {
      game.setup(blackPlayer, whitePlayer);
    } else {
      cout << "Invalid command: " << cmd << endl;
    }
  }
}
