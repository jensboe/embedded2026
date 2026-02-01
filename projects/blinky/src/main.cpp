/**
 * @file main.cpp
 * @brief  Simple blinky application for Nucleo-F446ZE using GPIO and DWT delay.

 *
 */

#include "bsp.h"
#include <cstdio>
using namespace stm32::f4;

using board = bsp::nucleo_f446ze<100'000'000>;
/**
 * @brief Main entry point for the blinky application.
 *
 * @return int
 */
int main(void)
{
	board::init();

	uint32_t loop_counter = 0;

	while (1)
	{
		printf("Delay count: %lu\n", ++loop_counter);
		board::LD_Green::set();
		board::LD_Red::set();
		board::Delay::ms(1000);
		board::LD_Green::clear();
		board::LD_Red::clear();
		board::Delay::ms(1000);
		if (board::B1::read())
		{
			board::LD_Blue::set();
		}
		else
		{
			board::LD_Blue::clear();
		}
	}

	return 0;
}
