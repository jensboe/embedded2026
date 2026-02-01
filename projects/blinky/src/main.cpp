/**
 * @file main.cpp
 * @brief  Simple blinky application for Nucleo-F446ZE using GPIO and DWT delay.

 *
 */

#include "bsp.h"
#include <cstdio>
using namespace stm32::f4;

using Delay = DelayImpl<>; //!< Configure delay utility with System clock
/**
 * @brief Main entry point for the blinky application.
 *
 * @return int
 */
int main(void)
{
	bsp::init();
	init_print();
	uint32_t loop_counter = 0;

	while (1)
	{
		printf("Delay count: %lu\n", ++loop_counter);
		bsp::LD_Green::set();
		bsp::LD_Red::set();
		Delay::ms(500);
		bsp::LD_Green::clear();
		bsp::LD_Red::clear();
		Delay::ms(500);
		if (bsp::B1::read())
		{
			bsp::LD_Blue::set();
		}
		else
		{
			bsp::LD_Blue::clear();
		}
	}

	return 0;
}
