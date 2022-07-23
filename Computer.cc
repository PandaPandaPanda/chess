#include "Computer.h"

#include "Player.h"

using namespace std;

PlayerType Computer::doGetType() { return PlayerType::C; }

Computer::Computer() {
  // todo
}

void Computer::setup(Board *b, Team *t) { doSetup(b, t); }
