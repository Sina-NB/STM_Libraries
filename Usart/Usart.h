/*
Name: Sina Nabigol
Date: 3/28/2022
Version: 1.0
Discription: Class based library for usart
*/

#ifndef INC_USART_H_
#define INC_USART_H_

#include "main.h"
#include "string.h"
#include <string>
using namespace std;

class Usart
{
public:
	Usart(UART_HandleTypeDef* huart);
	void begin(uint32_t baudRate);
	void send(string s);

private:
	UART_HandleTypeDef* _huart;
};

#endif /* INC_USART_H_ */
