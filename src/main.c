#include <stdio.h>
#include "drivers/ethernet/eth_instructions.h"
#include "drivers/ethernet/eth_control_registers.h"

int main() {
  write_control_register(ECON1, 0x3);
  write_control_register(MAA)
  return 0;
}
