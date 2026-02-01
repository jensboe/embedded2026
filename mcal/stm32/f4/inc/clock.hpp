/**
 * @file clock.hpp
 * @brief Implementation of the clock tree
 *
 */
#pragma once
#include "stm32f4xx.h"

namespace stm32::f4
{
	/**
	 * @brief Contains all relevant data for clock speed.
	 *
	 *
	 *
	 */
	struct Clock
	{
		static constexpr uint32_t HSI_frequency_hz = 16'000'000; //!< The internal HSI runs at 16 MHz
		/**
		 * @brief The System clock frequency
		 *
		 * Since no change is implemented the System Clock frequency is always 16 MHz.
		 *
		 */
		static constexpr uint32_t SystemClock_hz = HSI_frequency_hz;

		static void init()
		{
			SystemCoreClockUpdate();
		}
	};
} // namespace stm32::f4
