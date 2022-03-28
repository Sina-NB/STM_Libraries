#include "I2CLiquidCrystal.h"

I2CLiquidCrystal::I2CLiquidCrystal(I2C_HandleTypeDef* hi2c, uint8_t Address, uint8_t LCDType)
{
	_hi2c = hi2c;
	_Address = Address;
	_LCDType = LCDType;
}

void I2CLiquidCrystal::send_cmd (char cmd)
{
  	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (_hi2c, _Address,(uint8_t *) data_t, 4, 100);
}

void I2CLiquidCrystal::send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (_hi2c, _Address,(uint8_t *) data_t, 4, 100);
}

void I2CLiquidCrystal::init (void)
{
	// 4 bit initialization
	HAL_Delay(50);  // wait for >40ms
	send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	send_cmd (0x30);
	HAL_Delay(10);
	send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // display initialization
	send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void I2CLiquidCrystal::clear (void)
{
	send_cmd (0x00);
	for (int i=0; i<100; i++)
	{
		send_data (' ');
	}
}

void I2CLiquidCrystal::puts (string s)
{
	uint8_t i = 0;
	while (i<s.length()){
		send_data (s[i]);
		i++;
	}
}

void I2CLiquidCrystal::put (char character)
{
	send_data (character);
}

void I2CLiquidCrystal::set_cursor (uint8_t row, uint8_t column)
{
	char address;

	if(_LCDType == LCD20x4)
	switch(row)
	{
		case 0:
			address = 0x80 | (0x00 + column);
			break;
		case 1:
			address = 0x80 | (0x40 + column);
			break;
		case 2:
			address = 0x80 | (0x14 + column);
			break;
		case 3:
			address = 0x80 | (0x54 + column);
			break;
		default:
			address = 0x80;
			break;
	}
	else if(_LCDType == LCD16x2)
	switch(row)
	{
		case 0:
			address = 0x80 | (0x00 + column);
			break;
		case 1:
			address = 0x80 | (0x40 + column);
			break;
		default:
			address = 0x80;
			break;
	}

	send_cmd(address);

}
