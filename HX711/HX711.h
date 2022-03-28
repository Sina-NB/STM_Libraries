/*
Name: Sina Nabigol
Date: 3/28/2022
Version: 1.0
Discription: HX711 library(scale application)
*/

#ifndef HX711_H
#define HX711_H

#include "main.h"
#include "Delay_us.h"

class HX711
{
	private:
		GPIO_TypeDef* clk_gpio;
        uint16_t clk_pin; 
        GPIO_TypeDef* data_gpio; 
        uint16_t data_pin;
		uint8_t GAIN;		// amplification factor
		int64_t OFFSET = 0;	// used for tare weight
		float SCALE = 1.0;	// used to return weight in grams, kg, ounces, whatever

		uint8_t shiftIn(uint8_t bitOrder);

	public:

		// Initialize library with data output pin, clock input pin and gain factor.
		// Channel selection is made by passing the appropriate gain:
		// - With a gain factor of 64 or 128, channel A is selected
		// - With a gain factor of 32, channel B is selected
		// The library default is "128" (Channel A).
		void begin(GPIO_TypeDef *clk_g, uint16_t clk_p, GPIO_TypeDef *data_g, uint16_t data_p, uint8_t gain= 128);

		// Check if HX711 is ready
		// from the datasheet: When output data is not ready for retrieval, digital output pin DOUT is high. Serial clock
		// input PD_SCK should be low. When DOUT goes to low, it indicates data is ready for retrieval.
		bool is_ready();

		// Wait for the HX711 to become ready
		void wait_ready(uint32_t delay_ms = 0);

		// set the gain factor; takes effect only after a call to read()
		// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
		// depending on the parameter, the channel is also set to either A or B
		void set_gain(uint8_t gain = 128);

		// waits for the chip to be ready and returns a reading
		int32_t read();

		// returns an average reading; times = how many times to read
		int32_t read_average(uint8_t times = 10);

		// returns (read_average() - OFFSET), that is the current value without the tare weight; times = how many readings to do
		double get_value(uint8_t times = 1);

		// returns get_value() divided by SCALE, that is the raw value divided by a value obtained via calibration
		// times = how many readings to do
		float get_units(uint8_t times = 1);

		// set the OFFSET value for tare weight; times = how many times to read the tare value
		void tare(uint8_t times = 10);

		// set the SCALE value; this value is used to convert the raw data to "human readable" data (measure units)
		void set_scale(float scale = 1.f);

		// get the current SCALE
		float get_scale();

		// set OFFSET, the value that's subtracted from the actual reading (tare weight)
		void set_offset(int32_t offset = 0);

		// get the current OFFSET
		int32_t get_offset();

		// puts the chip into power down mode
		void power_down();

		// wakes up the chip after power down mode
		void power_up();
};

#endif /* HX711_H */
