#include <iomanip>
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

SDL_Runner r;

Player*
createPlayer(string player) {
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
parseMove(string move) {
    if (move.size() != 2) {
        return {-1, -1};
    }

    int row = 7 - (move[1] - '1');  // extra -1 converting number to index
    int col = move[0] - 'a';

    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        return {-1, -1};
    }

    return {row, col};
}

int main() {
    string cmd;
    double whiteScore = 0;
    double blackScore = 0;
    Game* game = nullptr;
    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;
    while (!cin.eof()) {
        if (game && game->hasGameEnded()) {
            if (game->getWinner() == 'D') {
                cout << "Draw" << endl;
                whiteScore += 0.5;
                blackScore += 0.5;
            } else {
                if (game->getWinner() == 'W') {
                    whiteScore += 1;
                } else {
                    blackScore += 1;
                }
            }
        }

        cin >> cmd;
        if (cmd == "exit") {
            break;
        }

        if (cin.eof()) {
            break;
        }

        if (!game && cmd != "game") {
            cout << "Game has not been initialized" << cmd << endl;
            continue;
        }

        if (game != nullptr && game->hasGameEnded() && cmd != "game") {
            cout << "Game has ended. Start a new game." << endl;
            continue;
        }

        if (game && !(game->hasGameEnded())) {
            if (game->getTurnColor() == Color::White && whitePlayer->getType() == PlayerType::C) {
                if (cmd == "move") {
                    whitePlayer->play(game);
                    continue;
                }
                if (cmd == "resign") {
                    game->resign();
                    continue;
                }
                cout << "Enter move to use the computer" << endl;
                continue;
            }
            if (game->getTurnColor() == Color::Black && blackPlayer->getType() == PlayerType::C) {
                if (cmd == "move") {
                    blackPlayer->play(game);
                    continue;
                }
                if (cmd == "resign") {
                    game->resign();
                    continue;
                }
                cout << "Enter move to use the computer" << endl;
                continue;
            }
        }

        if (cmd == "game") {
            string whiteType, blackType;
            cin >> whiteType;
            cin >> blackType;

            if (game != nullptr) {
                delete game;
            }
            if (whitePlayer != nullptr) {
                delete whitePlayer;
            }
            if (blackPlayer != nullptr) {
                delete blackPlayer;
            }

            game = new Game{};
            whitePlayer = createPlayer(whiteType);
            blackPlayer = createPlayer(blackType);
            game->setPlayer(Color::Black, blackPlayer);
            game->setPlayer(Color::White, whitePlayer);

            cout << *game;  // print out board is working
            continue;
        }

        if (game->getSteps() > 0 && cmd == "setup") {
            cout << "Game is already started, can no longer setup" << endl;
            continue;
        }

        if (cmd == "setup") {
            game->setup();
            continue;
        }

        if (cmd == "resign") {
            game->resign();
            continue;
        }

        if (cmd == "move") {
            string startStr, destStr;
            pair<int, int> start, dest;
            cin >> startStr >> destStr;
            while (cin) {
                start = parseMove(startStr);
                dest = parseMove(destStr);
                if (game->move(start, dest)) {
                    cout << *game;
                    break;
                }
                cout << "Invalid start/dest move, please enter two valid coordinates "
                        "in form [a-h][1-8]"
                     << endl;
                cin >> startStr >> destStr;
            }
            continue;
        }

        cout << "Invalid command: " << cmd << endl;
    }

    cout << fixed;
    cout << setprecision(1);
    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;

    if (game) {
        delete game;
    }
    if (whitePlayer) {
        delete whitePlayer;
    }
    if (blackPlayer) {
        delete blackPlayer;
    }
}
