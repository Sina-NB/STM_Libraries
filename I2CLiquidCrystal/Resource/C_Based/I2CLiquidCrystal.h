#ifndef INC_I2CLIQUIDCRYSTAL_H_
#define INC_I2CLIQUIDCRYSTAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void lcd_send_cmd (char cmd);  // send command to lcd
void lcd_send_data (char data);  // send data to lcd
void lcd_init (void);   // initialize lcd
void lcd_clear (void);  // clear lcd
void lcd_puts (char *str);  // send string to lcd
void lcd_put (char character); // send character to lcd
void lcd_set_cursor (uint8_t row, uint8_t column); // set cursor position

#ifdef __cplusplus
}
#endif

#endif /* INC_I2CLIQUIDCRYSTAL_H_ */
