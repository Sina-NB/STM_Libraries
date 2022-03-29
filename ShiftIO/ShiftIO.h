/*
Name: Sina Nabigol
Date: 3/29/2022
Version: 1.0
Discription: ShiftIn/Out serial data
 */

#ifndef INC_SHIFTIO_H_
#define INC_SHIFTIO_H_

#include "main.h"
#include "Delay_us.h"

#define LSB_FIRST 0
#define MSB_FIRST 1

class ShiftIO
{
public:
    void begin (GPIO_TypeDef *ClkGPIO, uint16_t ClkPin, GPIO_TypeDef *DataGPIO, uint16_t DataPin, uint8_t BitOrder);
    uint8_t shiftIn();
    void shiftOut(uint8_t Data);

private:
	GPIO_TypeDef* clk_gpio;
    uint16_t clk_pin;
    GPIO_TypeDef* data_gpio;
    uint16_t data_pin;
    uint8_t bit_order;
};

#endif /* INC_SHIFTIO_H_ */
