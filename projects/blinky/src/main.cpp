/**
 * @file main.cpp
 * @brief Simple blinky application for Nucleo-F446ZE using GPIO and DWT delay.
 */

#include "bsp.h"
#include <cstdio>

#include <mp-units/systems/si.h>

namespace units = mp_units::si::unit_symbols;

/**
 * @brief Use the Nucleo F446ZE board with 100 MHz system clock.
 */
using board = bsp::nucleo_f446ze<100 * units::MHz>;

/**
 * @brief Main entry point.
 */
int main() noexcept
{
	// Initialize board: clocks, GPIOs, delay, ITM
	board::init();

	std::uint32_t loop_counter = 0;

	// Print system clock frequency via ITM/printf
	printf("HSI:    %9lu Hz\n", board::clock::HSI_frequency_hz.numerical_value_in(mp_units::si::hertz));
	printf("HSE:    %9lu Hz\n", board::clock::HSE_frequency_hz.numerical_value_in(mp_units::si::hertz));
	printf("root:   %9lu Hz\n", board::clock::root_frequency_hz().numerical_value_in(mp_units::si::hertz));

	printf("SysClk: %9lu Hz\n", board::clock::get_system_clock());

	while (true)
	{
		printf("Delay count: %lu\n", ++loop_counter);

		// Toggle Green and Red LEDs
		board::LD_Green::set();
		board::LD_Red::set();
		board::Delay::blocking(500 * units::ms);

		board::LD_Green::clear();
		board::LD_Red::clear();
		board::Delay::blocking(500 * units::ms);

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
