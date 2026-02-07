/**
 * @file main.cpp
 * @brief Simple blinky application for Nucleo-F446ZE using GPIO and DWT delay.
 */

#include "mcal.hpp"
#include "nucleo-f446ze.h"
#include "utils.hpp"
#include <cstdio>

/**
 * @brief Use the Nucleo F446ZE board with 100 MHz system clock.
 */
using board = bsp::nucleo_f446ze<100 * utils::unit::MHz>;

/**
 * @brief Main entry point.
 */
int main() noexcept
{
	// Initialize board: clocks, GPIOs, delay, ITM
	board::init();

	std::uint32_t loop_counter = 0;

	// Print system clock frequency via ITM/printf
	printf("HSI:    %9lu Hz\n", board::clock::HSI_frequency.numerical_value_in(utils::unit::Hz));
	printf("HSE:    %9lu Hz\n", board::clock::HSE_frequency.numerical_value_in(utils::unit::Hz));
	printf("root:   %9lu Hz\n", board::clock::root_frequency().numerical_value_in(utils::unit::Hz));

	printf("SysClk: %9lu Hz\n", board::clock::get_system_clock());

	while (true)
	{
		printf("Delay count: %lu\n", ++loop_counter);

		// Toggle Green and Red LEDs
		board::LD_Green::set();
		board::LD_Red::set();
		board::Delay::blocking(500 * utils::unit::ms);

		board::LD_Green::clear();
		board::LD_Red::clear();
		board::Delay::blocking(500 * utils::unit::ms);

		// Read user button (B1) and control Blue LED
		if (board::B1::read())
		{
			board::LD_Blue::set();
		}
		else
		{
			board::LD_Blue::clear();
		}
	}

	// Never reached
	return 0;
}
