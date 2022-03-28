/*
Name: Sina Nabigol
Date: 3/28/2022
Version: 1.0
Discription: LiquidCrystal by I2C interface
 */

#ifndef INC_I2CLIQUIDCRYSTAL_H_
#define INC_I2CLIQUIDCRYSTAL_H_

#include "main.h"
#include "string.h"
#include <string>
using namespace std;

#define LCD20x4 0
#define LCD16x2 1

class I2CLiquidCrystal
{
public:
    void begin (I2C_HandleTypeDef* hi2c, uint8_t Address, uint8_t LCDType); // initial setting
    void send_cmd (char cmd);  // send command to lcd
    void send_data (char data);  // send data to lcd
    void init (void);   // initialize lcd
    void clear (void);  // clear lcd
    void puts (string s);  // send string to lcd
    void put (char character); // send character to lcd
    void set_cursor (uint8_t row, uint8_t column); // set cursor position

private:
	I2C_HandleTypeDef* _hi2c;
    uint8_t _Address;
    uint8_t _LCDType;
};

#endif /* INC_I2CLIQUIDCRYSTAL_H_ */
