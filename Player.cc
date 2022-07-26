#include "Player.h"

using namespace std;

Player::Player() {
    // todo
}

Player::~Player() {
    // todo
}

void Player::play(Game *g) {
    doPlay(g);
}

PlayerType Player::getType() {
    return doGetType();
}

char Player::getPromotionChoice() {
    return doGetPromotionChoice();
}
