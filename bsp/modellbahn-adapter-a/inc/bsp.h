/**
 * @file bsp.h
 * @brief Board support package for Modellbahn
 *
 */

#pragma once

#include "nucleo-f446ze.h"
#include "units.hpp"

namespace bsp
{
	namespace modellbahn
	{
		template <utils::quantity::Hz_t target_system_clock>
		struct adapter_a
		{
			using base = bsp::nucleo_f446ze<target_system_clock>;

			using LD_red =
				stm32::f4::GpioPin<stm32::f4::GpioC, 9, stm32::f4::GpioPinMode::Output>; //!< Green LED at PB0
			using LD_yellow =
				stm32::f4::GpioPin<stm32::f4::GpioG, 2, stm32::f4::GpioPinMode::Output>; //!< Green LED at PB0
			using LD_green =
				stm32::f4::GpioPin<stm32::f4::GpioG, 3, stm32::f4::GpioPinMode::Output>; //!< Green LED at PB0
			static inline void init() noexcept
			{
				base::init();
				LD_red::init();
				LD_yellow::init();
				LD_green::init();
			}
		};
	} // namespace modellbahn
} // namespace bsp
