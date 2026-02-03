/**
 * @file utils.hpp
 * @brief Utility implementations for STM32F4 series (delay + ITM print setup).
 *
 * This header provides a DWT‑based delay implementation and a minimal ITM‑based
 * character output function for debugging on STM32F4 microcontrollers.
 */

#pragma once

#include "clock.hpp"
#include "mcal.hpp"
#include "stm32f4xx.h"
#include <mp-units/systems/si/units.h>
/**
 * @brief Home of STM32 microcontroller specific implementations.
 *
 */
namespace stm32
{

}
/**
 * @brief Home of STM32F4 series specific implementations.
 *
 */
namespace stm32::f4
{
	using namespace mp_units;
	/**
	 * @brief Delay implementation using the Cortex‑M DWT cycle counter.
	 *
	 * This class provides millisecond and microsecond delays by reading the
	 * DWT->CYCCNT register. The DWT unit must be enabled before use.
	 *
	 * @tparam CPU_FREQUENCY_HZ  Core clock frequency in Hertz.
	 */
	template <uint32_t CPU_FREQUENCY_HZ>
	struct DelayImpl
	{
		static_assert(CPU_FREQUENCY_HZ >= 1'000'000,
					  "CPU_FREQUENCY_HZ must be greater than 1 MHz to ensure working us delay.");
		/**
		 * @brief Enable the DWT cycle counter.
		 *
		 * This function enables tracing in the DEMCR register and activates
		 * the CYCCNT counter in the DWT unit. It must be called before any
		 * delay operation that relies on DWT->CYCCNT.
		 */
		static inline void enable_dwt()
		{
			Register::set(CoreDebug->DEMCR, CoreDebug_DEMCR_TRCENA_Msk);
			Register::set(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
		}

		static void blocking(quantity<si::micro<si::second>, u_int32_t> duration)
		{
			enable_dwt();
			const uint32_t ticks = duration.numerical_value_in(si::micro<si::second>) * (CPU_FREQUENCY_HZ / 1'000'000);
			const uint32_t start = Register::read(DWT->CYCCNT);

			while ((Register::read(DWT->CYCCNT) - start) < ticks)
			{
			}
		}
	};

	/**
	 * @brief Initialize ITM/SWO output for debug printing.
	 *
	 * This function enables the trace I/O pins in the DBGMCU peripheral.
	 * It must be called before using ITM_SendChar() or __io_putchar().
	 */
	void init_print()
	{
		Register::write<DBGMCU_CR_TRACE_IOEN, DBGMCU_CR_TRACE_IOEN_Msk>(DBGMCU->CR);
	}

} // namespace stm32::f4

extern "C"
{
	/**
	 * @brief Low‑level character output for printf redirection.
	 *
	 * This function redirects character output to the ITM stimulus port 0.
	 * It is used by newlib/newlib‑nano when printf() is called.
	 *
	 * @param ch  Character to output.
	 * @return Always returns 0.
	 */
	int __io_putchar(int ch)
	{
		ITM_SendChar(ch);
		return 0;
	}
}
