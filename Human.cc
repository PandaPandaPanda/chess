#include "Human.h"

#include "Player.h"

using namespace std;

PlayerType Human::doGetType() { return PlayerType::H; }

// Skeleton for future updates on program structure and handling additional features
void Human::doPlay(Game *g) {}
char Human::doGetPromotionChoice() { return ' '; }

Human::Human() {}
