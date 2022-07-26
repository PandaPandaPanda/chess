#include "Computer4.h"

#include "Board.h"
#include "Team.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> Computer4::doGetMove() {
  return {{}, {}};
}

void Computer4::doSetup(Board *b, Team *homeTeam, Team *oppTeam) {
  // todo
}

Computer4::Computer4() {
  // todo
}

Computer4::~Computer4() {
  // todo
}

pair<pair<int, int>, pair<int, int>> Computer4::getMove() {
  return doGetMove();
}
