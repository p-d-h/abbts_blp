#ifndef _HAL_IN_H_
#define _HAL_IN_H_

#include <Arduino.h>

class HAL_IN {
  public:
    HAL_IN(void);

    u_int8_t bFpgaButton;
    u_int8_t bClk1Hz;
    u_int8_t bClk5Hz;
    u_int8_t bClk10Hz;
    


};

# endif
