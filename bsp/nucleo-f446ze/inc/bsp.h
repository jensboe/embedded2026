/**
 * @file bsp.h
 * @brief Board support package for Nucleo-F446ZE
 */

#pragma once
#include "units.hpp"

#include "f4.hpp"

namespace bsp
{
	/**
	 * @brief Nucleo-F446ZE peripheral definitions.
	 *
	 * @tparam target_system_clock Requested system clock frequency
	 */
	template <utils::quantity::Hz_t target_system_clock>
	struct nucleo_f446ze
	{
		using LD_Green = stm32::f4::GpioPin<stm32::f4::GpioB, 0, stm32::f4::GpioPinMode::Output>; //!< Green LED at PB0
		using LD_Blue = stm32::f4::GpioPin<stm32::f4::GpioB, 7, stm32::f4::GpioPinMode::Output>;  //!< Blue LED at PB7
		using LD_Red = stm32::f4::GpioPin<stm32::f4::GpioB, 14, stm32::f4::GpioPinMode::Output>;  //!< Red LED at PB14
		using B1 =
			stm32::f4::GpioPin<stm32::f4::GpioC, 13, stm32::f4::GpioPinMode::Input>; //!< Blue user button at PC13

		/**
		 * @brief Supply voltage in mV.
		 *
		 */
		static constexpr utils::quantity::mv_t supply_voltage = 3300 * utils::unit::mV;

		/**
		 * @brief Clock tree configuration.
		 *
		 */
		using clock = stm32::f4::clock_tree<target_system_clock, {8 * utils::unit::MHz, mcal::clock::sources::clock}>;

		using Delay = stm32::f4::DelayImpl<target_system_clock>; //!< System clock based delay utility

		/**
		 * @brief Initialize the board peripherals.
		 *
		 */
		static inline void init() noexcept
		{
			// Configure Flash latency according to RM0390, Table 5
			if constexpr (supply_voltage > 2700 * utils::unit::mV)
			{
				using namespace stm32::f4;

				if constexpr (target_system_clock < 30 * utils::unit::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_0WS;
				else if constexpr (target_system_clock < 60 * utils::unit::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_1WS;
				else if constexpr (target_system_clock < 90 * utils::unit::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_2WS;
				else if constexpr (target_system_clock < 120 * utils::unit::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
				else if constexpr (target_system_clock < 150 * utils::unit::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
				else if constexpr (target_system_clock < 180 * utils::unit::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
			}

			// Initialize clock tree and peripherals
			clock::init();
			stm32::f4::init_print();
			LD_Green::init();
			LD_Blue::init();
			LD_Red::init();
			B1::init();
		}
	};
} // namespace bsp
