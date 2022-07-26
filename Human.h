#ifndef __Human_h__
#define __Human_h__
#include "Player.h"

enum PlayerType;

class Human : public Player {
  void doPlay(Game *g) override;
  PlayerType doGetType() override;
  char doGetPromotionChoice() override;
public:
  Human();
};
#endif
