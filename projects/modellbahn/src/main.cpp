/**
 * @file main.cpp
 * @brief Simple blinky application for Nucleo-F446ZE using GPIO and DWT delay.
 */

#include "bsp.h"
#include "mcal.hpp"
#include "utils.hpp"
#include <cstdio>

/**
 * @brief Use the Nucleo F446ZE board with 100 MHz system clock.
 */
using board = bsp::modellbahn::adapter_a<100 * utils::unit::MHz>;

/**
 * @brief Main entry point.
 */
int main() noexcept
{
	// Initialize board: clocks, GPIOs, delay, ITM
	board::init();

	std::uint32_t loop_counter = 0;

	// Print system clock frequency via ITM/printf
	printf("HSI:    %9lu Hz\n", board::base::clock::HSI_frequency.numerical_value_in(utils::unit::Hz));
	printf("HSE:    %9lu Hz\n", board::base::clock::HSE_frequency.numerical_value_in(utils::unit::Hz));
	printf("root:   %9lu Hz\n", board::base::clock::root_frequency().numerical_value_in(utils::unit::Hz));

	printf("SysClk: %9lu Hz\n", board::base::clock::get_system_clock());

	while (true)
	{
		printf("Delay count: %lu\n", ++loop_counter);

		// Toggle Green and Red LEDs
		board::base::LD_Green::set();
		board::base::LD_Red::set();
		board::LD_red::clear();
		board::LD_yellow::clear();
		board::LD_green::clear();
		board::base::Delay::blocking(500 * utils::unit::ms);
		board::base::LD_Green::clear();
		board::base::LD_Red::clear();
		board::LD_red::set();
		board::LD_yellow::set();
		board::LD_green::set();
		board::base::Delay::blocking(500 * utils::unit::ms);

		// Read user button (B1) and control Blue LED
		if (board::base::B1::read())
		{
			board::base::LD_Blue::set();
		}
		else
		{
			board::base::LD_Blue::clear();
		}
	}

	// Never reached
	return 0;
}
