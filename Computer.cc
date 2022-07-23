#include "Computer.h"

#include "Player.h"

using namespace std;

void Computer::setup(Board *b, Team *t) { doSetup(b, t); }

PlayerType Computer::doGetType() { return PlayerType::C; }