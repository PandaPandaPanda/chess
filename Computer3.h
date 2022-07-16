#ifndef __Computer3_h_
#define __Computer3_h_
#include "Computer.h"
class Computer3 : public Computer {
  void doPlay() override;
public:
  Computer3(Board, Team);
};
#endif
