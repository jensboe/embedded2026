/**
 * @file utils.hpp
 * @brief Utility implementations for STM32F4 series (delay + ITM print setup).
 *
 * Provides a DWT-based blocking delay implementation and
 * a minimal ITM/SWO character output backend.
 */

#pragma once

#include <cstdint>

#include "clock.hpp"
#include "mcal.hpp"

#include "stm32f4xx.h"

#include <mp-units/systems/si.h>

namespace stm32
{
	// common STM32 utilities may live here later
}

namespace stm32::f4
{
	using frequency_hz_t = mp_units::quantity<mp_units::si::hertz, std::uint32_t>;

	/**
	 * @brief Shorthand for microsecond duration.
	 *
	 */
	using microseconds_t = mp_units::quantity<mp_units::si::micro<mp_units::si::second>, std::uint32_t>;

	/**
	 * @brief Blocking delay using the Cortex-M DWT cycle counter.
	 *
	 * @tparam CPU_FREQUENCY_HZ Core clock frequency.
	 */
	template <frequency_hz_t CPU_FREQUENCY_HZ>
	struct DelayImpl
	{
		static_assert(CPU_FREQUENCY_HZ >= (1 * mp_units::si::unit_symbols::MHz),
					  "CPU_FREQUENCY_HZ must be >= 1 MHz for µs resolution.");

		/**
		 * @brief Enable the DWT cycle counter.
		 */
		static inline void enable_dwt() noexcept
		{
			Register::set(CoreDebug->DEMCR, CoreDebug_DEMCR_TRCENA_Msk);
			Register::set(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
		}

		/**
		 * @brief Busy-wait for a given duration.
		 *
		 * @param duration Delay time in microseconds.
		 */
		static inline void blocking(microseconds_t duration) noexcept
		{
			enable_dwt();

			const uint32_t ticks = duration.numerical_value_in(mp_units::si::micro<mp_units::si::second>) *
								   (CPU_FREQUENCY_HZ.numerical_value_in(mp_units::si::hertz) / 1'000'000);

			const std::uint32_t start = Register::read(DWT->CYCCNT);

			while ((Register::read(DWT->CYCCNT) - start) < ticks)
			{
				// busy wait
			}
		}
	};

	/**
	 * @brief Initialize ITM/SWO output for debug printing.
	 */
	inline void init_print() noexcept
	{
		Register::write<DBGMCU_CR_TRACE_IOEN, DBGMCU_CR_TRACE_IOEN_Msk>(DBGMCU->CR);
	}

} // namespace stm32::f4

extern "C"
{
	/**
	 * @brief Low-level character output hook for printf().
	 *
	 * Redirects output to ITM stimulus port 0.
	 */
	inline int __io_putchar(int ch) noexcept
	{
		ITM_SendChar(static_cast<std::uint32_t>(ch));
		return 0;
	}
}
