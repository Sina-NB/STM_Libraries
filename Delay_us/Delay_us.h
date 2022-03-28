/*
Name: Sina Nabigol
Date: 3/28/2022
Version: 1.0
Discription: Implement a microsecond delay by DWT unit
*/
#ifndef INC_DELAY_US_H_
#define INC_DELAY_US_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

//Call this function at the beginning of the code
uint32_t DWT_Delay_Init(void);

void DWT_Delay_us(volatile uint32_t au32_microseconds);

#ifdef __cplusplus
}
#endif

#endif /* INC_DELAY_US_H_ */
