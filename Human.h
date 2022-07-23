#ifndef __Human_h__
#define __Human_h__
#include "Player.h"
class Human : public Player {
  void doPlay() override;
  PlayerType doGetType() override;
  public:
  Human();
};
#endif
