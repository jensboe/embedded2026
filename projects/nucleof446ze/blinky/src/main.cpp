/**
 * @file main.cpp
 * @brief  Simple blinky application for Nucleo-F446ZE using GPIO and DWT delay.

 *
 */

#include "gpio.hpp"
#include "utils.hpp"
#include <cstdio>
using namespace stm32::f4;
using LD_Green = GpioPin<GpioB, 0, GpioPinMode::Output>; //!< Green LED at PB0
using LD_Blue = GpioPin<GpioB, 7, GpioPinMode::Output>;	 //!< Blue LED at PB7
using LD_Red = GpioPin<GpioB, 14, GpioPinMode::Output>;	 //!< Red LED at PB14
using Delay = DelayImpl<16'000'000>;					 //!< Delay utility at 16 MHz
/**
 * @brief Main entry point for the blinky application.
 *
 * @return int
 */
int main(void)
{
	init_print();
	uint32_t loop_counter = 0;
	LD_Green::init();
	LD_Blue::init();
	LD_Red::init();

	while (1)
	{
		printf("Delay count: %lu\n", ++loop_counter);
		LD_Green::set();
		LD_Blue::set();
		LD_Red::set();
		Delay::ms(500);
		LD_Green::clear();
		LD_Blue::clear();
		LD_Red::clear();
		Delay::ms(500);
	}

	return 0;
}
