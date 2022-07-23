#ifndef __Computer4_h_
#define __Computer4_h_
#include "Computer.h"
class Computer4 : public Computer {
  void doPlay() override;
  void doSetup(Board *, Team *) override;
public:
  Computer4();
};
#endif
