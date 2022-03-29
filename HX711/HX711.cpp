#include "HX711.h"

uint8_t HX711::shiftIn(uint8_t bitOrder) {
    uint8_t value = 0;
    uint8_t i;
	
	HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
    for(i = 0; i < 8; ++i) {
        HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_SET);
        DWT_Delay_us(1);
        if(bitOrder == 0)
            value |= HAL_GPIO_ReadPin(data_gpio, data_pin) << i;
        else
            value |= HAL_GPIO_ReadPin(data_gpio, data_pin) << (7 - i);
        HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
        DWT_Delay_us(1);
    }
    return value;
}

void HX711::begin(GPIO_TypeDef *clk_g, uint16_t clk_p, GPIO_TypeDef *data_g, uint16_t data_p, uint8_t gain) {
	clk_gpio = clk_g;
    clk_pin = clk_p; 
    data_gpio = data_g; 
    data_pin = data_p;

	set_gain(gain);
}

bool HX711::is_ready() {
	return HAL_GPIO_ReadPin(data_gpio, data_pin) == GPIO_PIN_RESET;
}

void HX711::set_gain(uint8_t gain) {
	switch (gain) {
		case 128:		// channel A, gain factor 128
			GAIN = 1;
			break;
		case 64:		// channel A, gain factor 64
			GAIN = 3;
			break;
		case 32:		// channel B, gain factor 32
			GAIN = 2;
			break;
	}

}

int32_t HX711::read() {

	// Wait for the chip to become ready.
	wait_ready();

	// Define structures for reading data into.
	uint32_t value = 0;
	uint8_t data[3] = { 0 };
	uint8_t filler = 0x00;

	// Disable interrupts.
	__disable_irq();

	// Pulse the clock pin 24 times to read the data.
	data[2] = shiftIn(1);
	data[1] = shiftIn(1);
	data[0] = shiftIn(1);

	// Set the channel and the gain factor for the next reading using the clock pin.
	for (uint8_t i = 0; i < GAIN; i++) {
		HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
	}

	// Enable interrupts again.
	__enable_irq();

	// Replicate the most significant bit to pad out a 32-bit signed integer
	if (data[2] & 0x80) {
		filler = 0xFF;
	} else {
		filler = 0x00;
	}

	// Construct a 32-bit signed integer
	value = ( static_cast<uint32_t>(filler) << 24
			| static_cast<uint32_t>(data[2]) << 16
			| static_cast<uint32_t>(data[1]) << 8
			| static_cast<uint32_t>(data[0]) );

	return static_cast<int32_t>(value);
}

void HX711::wait_ready(uint32_t delay_ms) {
	// Wait for the chip to become ready.
	// This is a blocking implementation and will
	// halt the sketch until a load cell is connected.
	while (!is_ready()) {
		HAL_Delay(delay_ms);
	}
}

int32_t HX711::read_average(uint8_t times) {
	long sum = 0;
	for (uint8_t i = 0; i < times; i++) {
		sum += read();
		HAL_Delay(0);
	}
	return sum / times;
}

double HX711::get_value(uint8_t times) {
	return read_average(times) - OFFSET;
}

float HX711::get_units(uint8_t times) {
	return get_value(times) / SCALE;
}

void HX711::tare(uint8_t times) {
	double sum = read_average(times);
	set_offset(sum);
}

void HX711::set_scale(float scale) {
	SCALE = scale;
}

float HX711::get_scale() {
	return SCALE;
}

void HX711::set_offset(int32_t offset) {
	OFFSET = offset;
}

int32_t HX711::get_offset() {
	return OFFSET;
}

void HX711::power_down() {
	HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_SET);
}

void HX711::power_up() {
	HAL_GPIO_WritePin(clk_gpio, clk_pin, GPIO_PIN_RESET);
}
