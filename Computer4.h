#ifndef __Computer4_h_
#define __Computer4_h_
#include "Computer.h"
class Computer4 : public Computer {
  void doPlay() override;
public:
  Computer4(Board, Team);
};
#endif
