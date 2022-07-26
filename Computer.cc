#include "Computer.h"

#include "Player.h"

#include <chrono>
#include <random>

using namespace std;

PlayerType Computer::doGetType() { return PlayerType::C; }

Computer::Computer() {}

void Computer::setup(Board *b, Team *t) { doSetup(b, t); }

int Computer::getRandomNum(int upperBound) {
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
     
    // minstd_rand0 is a standard
    // linear_congruential_engine
    minstd_rand0 generator (seed);
     
    // generates the random number
    return generator() % upperBound;
}

