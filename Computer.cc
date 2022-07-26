#include "Computer.h"

#include <chrono>
#include <random>

#include "Player.h"

using namespace std;

PlayerType
Computer::doGetType()
{
  return PlayerType::C;
}

void
Computer::doPlay(Game* g)
{
  pair<pair<int, int>, pair<int, int>> move = doGetMove();

  cout << "move from " << (char)(move.first.second + 'a')
       << (char)(8 - move.first.first + '0') << " to "
       << (char)(move.second.second + 'a')
       << (char)(8 - move.second.first + '0') << endl;
  g->move(move.first, move.second);

  cout << *g;
}

Computer::Computer() {}

void
Computer::setup(Board* b, Team* homeTeam, Team* oppTeam)
{
  doSetup(b, homeTeam, oppTeam);
}

pair<pair<int, int>, pair<int, int>>
Computer::getMove()
{
  return doGetMove();
}

int
Computer::getRandomNum(int upperBound)
{
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();

  // minstd_rand0 is a standard
  // linear_congruential_engine
  minstd_rand0 generator(seed);

  // generates the random number
  return generator() % upperBound;
}

char
Computer::doGetPromotionChoice()
{
  return 'Q';
}
