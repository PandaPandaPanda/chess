#ifndef __Computer2_h_
#define __Computer2_h_
#include "Computer.h"
class Computer2 : public Computer {
  void doPlay() override;
public:
  Computer2(Board, Team);
};
#endif
