#include "ShiftIO.h"

void ShiftIO::begin(GPIO_TypeDef *ClkGPIO, uint16_t ClkPin, GPIO_TypeDef *DataGPIO, uint16_t DataPin, uint8_t BitOrder)
{
	clk_gpio = ClkGPIO;
    clk_pin = ClkPin;
    data_gpio = DataGPIO;
    data_pin = DataPin;
    bit_order = BitOrder;
}

uint8_t ShiftIO::shiftIn()
{
    uint8_t value = 0;
    uint8_t i;

    HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
    for(i = 0; i < 8; ++i) {
        HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_SET);
        DWT_Delay_us(1);
        if(bit_order == LSB_FIRST)
            value |= HAL_GPIO_ReadPin(data_gpio, data_pin) << i;
        else
            value |= HAL_GPIO_ReadPin(data_gpio, data_pin) << (7 - i);
        HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
        DWT_Delay_us(1);
    }
    return value;
}

void ShiftIO::shiftOut(uint8_t Data)
{
    uint8_t i;

    HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
    for (i = 0; i < 8; i++)  {
          if (bit_order == LSB_FIRST)
        	  HAL_GPIO_WritePin(data_gpio, data_pin, GPIO_PinState(!!(Data & (1 << i))));
          else
        	  HAL_GPIO_WritePin(data_gpio, data_pin, GPIO_PinState(!!(Data & (1 << (7 - i)))));
          DWT_Delay_us(1);
          HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_SET);
          DWT_Delay_us(1);
          HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
    }
}

