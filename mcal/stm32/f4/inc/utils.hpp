#pragma once
#include "concept/delay.hpp"
#include "concept/gpio.hpp"
#include "stm32f4xx.h"
namespace mcal::stm32::f4
{
	template <uint32_t CPU_FREQUENCY_HZ = 16'000'000>
	struct DelayImpl
	{
		static inline void enable_dwt()
		{
			CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
			DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
		}
		static void ms(uint32_t duration)
		{
			enable_dwt();
			const uint32_t ticks = duration * (CPU_FREQUENCY_HZ / 1'000);
			const uint32_t start = DWT->CYCCNT;

			while ((DWT->CYCCNT - start) < ticks)
			{
			}
		}
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

	void init_print()
	{
		DBGMCU->CR &= DBGMCU_CR_TRACE_MODE_Msk;
		DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;
	}

} // namespace mcal::stm32::f4

extern "C"
{
	int __io_putchar(int ch)
	{
		ITM_SendChar(ch);
		return 0;
	}
}
