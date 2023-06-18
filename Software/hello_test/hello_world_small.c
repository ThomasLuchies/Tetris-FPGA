#include <system.h>

#define switches (volatile int *) 0x9010
  #define leds     (int *)          0x9000

  void main()
  {
     while(1)
     {
        *leds = *switches;
     }
  }
