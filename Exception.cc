#include "Exception.h"

#include <string>

using namespace std;

GameMoveError::GameMoveError(string message) : message{message} {}

const string &GameMoveError::what() const {
    return message;
}
