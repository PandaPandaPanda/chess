#ifndef __Computer1_h_
#define __Computer1_h_
#include "Computer.h"
class Computer1 : public Computer {
  void doPlay() override;
public:
  Computer1(Board, Team);
};
#endif
