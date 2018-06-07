#include "defines.h"
#include "serial.h"
#include "lib.h"

int main(void)
{
  serial_init(SERIAL_DEFAULT_DEVICE);

  puts("Hello World! Again! And Again!\n");

  while (1)
    ;

  return 0;
}
