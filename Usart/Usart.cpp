#include "Usart.h"

Usart::Usart(UART_HandleTypeDef* huart)
{
	_huart = huart;
}

void Usart::begin(uint32_t baudRate)
{
	_huart->Init.BaudRate = baudRate;
	if (HAL_UART_Init(_huart) != HAL_OK);
}

void Usart::send(string s)
{
	char pData[s.length() + 1];
	strcpy(pData, s.c_str());
	uint32_t timeout = 1/float(_huart->Init.BaudRate)*s.length()*15*1000;
	HAL_UART_Transmit(_huart, (uint8_t*)(void*)pData, strlen(pData), timeout);
	HAL_Delay(1);
}
