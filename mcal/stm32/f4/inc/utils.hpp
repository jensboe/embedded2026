/**
 * @file utils.hpp
 * @brief Utility implementations for STM32F4 series (delay + ITM print setup).
 *
 * This header provides a DWT‑based delay implementation and a minimal ITM‑based
 * character output function for debugging on STM32F4 microcontrollers.
 */

#pragma once

#include "mcal.hpp"
#include "stm32f4xx.h"

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
	/**
	 * @brief Delay implementation using the Cortex‑M DWT cycle counter.
	 *
	 * This class provides millisecond and microsecond delays by reading the
	 * DWT->CYCCNT register. The DWT unit must be enabled before use.
	 *
	 * @tparam CPU_FREQUENCY_HZ  Core clock frequency in Hertz.
	 */
	template <uint32_t CPU_FREQUENCY_HZ = 16'000'000>
	struct DelayImpl
	{
		/**
		 * @brief Enable the DWT cycle counter.
		 *
		 * This function enables tracing in the DEMCR register and activates
		 * the CYCCNT counter in the DWT unit. It must be called before any
		 * delay operation that relies on DWT->CYCCNT.
		 */
		static inline void enable_dwt()
		{
			CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
			DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
		}

		/**
		 * @brief Busy‑wait delay in milliseconds.
		 *
		 * @param duration  Number of milliseconds to wait.
		 *
		 * The function computes the required number of CPU cycles and spins
		 * until the DWT cycle counter has advanced accordingly.
		 */
		static void ms(uint32_t duration)
		{
			enable_dwt();
			const uint32_t ticks = duration * (CPU_FREQUENCY_HZ / 1'000);
			const uint32_t start = DWT->CYCCNT;

			while ((DWT->CYCCNT - start) < ticks)
			{
			}
		}

		/**
		 * @brief Busy‑wait delay in microseconds.
		 *
		 * @param duration  Number of microseconds to wait.
		 *
		 * Works identically to ms(), but with microsecond resolution.
		 */
		static void µs(uint32_t duration)
		{
			enable_dwt();
			const uint32_t ticks = duration * (CPU_FREQUENCY_HZ / 1'000'000);
			const uint32_t start = DWT->CYCCNT;

			while ((DWT->CYCCNT - start) < ticks)
			{
			}
		}
	};

	static_assert(mcal::concepts::Delay<DelayImpl<>>);

	/**
	 * @brief Initialize ITM/SWO output for debug printing.
	 *
	 * This function enables the trace I/O pins in the DBGMCU peripheral.
	 * It must be called before using ITM_SendChar() or __io_putchar().
	 */
	void init_print()
	{
		DBGMCU->CR &= DBGMCU_CR_TRACE_MODE_Msk;
		DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;
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
